/*
 * serial.cpp
 *
 *  Created on: Sep 18, 2017
 *      Author: user
 */

#include "comms.hpp"

// re-declaration of static members
using namespace mcal::reg;
using namespace ns_uart;

bool com_serial::m_open;
com_serial* com_serial::interruptOwner;

void UARTE0_UART0_IRQHandler(void)
{
	/* ISR */
	// Disable ARM interrupt controller
	NVIC_DisableIRQ(UARTE0_UART0_IRQn);
	// check if rx
	if( *REG_PTR(uart::base_addr,uart::event_rxdrdy) != UINT32_C(0) ) {
		*REG_PTR(uart::base_addr,uart::event_rxdrdy) = 0UL;
		if(com_serial::interruptOwner != nullptr) {
			com_serial* p = com_serial::interruptOwner;
			uint8_t byte = *REG_PTR(uart::base_addr,uart::rxd);
			p->write(&byte,1);
			if(byte != '\r') {
				if(byte == '\n')
					p->m_rx_rdy = true;
				else
					p->m_rx_c_buff.in(byte);
			}
		}
		*REG_PTR(uart::base_addr,uart::task_start_rx) = UINT32_C(1);
	}
	// check if tx
	if( *REG_PTR(uart::base_addr,uart::event_txdrdy) != UINT32_C(0) ) {
		if(com_serial::interruptOwner != nullptr) {
			if(!com_serial::interruptOwner->m_tx_c_buff.empty()) {
				com_serial::interruptOwner->tx_byte();
			} else {
				// disable tx interrupt
				*REG_PTR(uart::base_addr,uart::event_txdrdy) = UINT32_C(0x0);
				*REG_PTR(uart::base_addr,uart::intenclr) |= com_serial::interruptOwner->event_txdrdy;
				com_serial::interruptOwner->m_tx_busy = false;
			}
		}
	}
	// Enable ARM interrupt controller
	NVIC_EnableIRQ(UARTE0_UART0_IRQn);
}

com_serial::com_serial(const uint32_t rx_pin, const uint32_t tx_pin, baudrate_t baud)
: m_rx_pin(rx_pin), m_tx_pin(tx_pin), m_baud(baud)
{
	/* configure the rx pin */
	*REG_PTR(gpio::base_addr,gpio::dir) &= ( ~(UINT32_C(1) << m_rx_pin) );
	*REG_PTR(uart::base_addr,uart::pselrxd) = m_rx_pin;
	/* configure the tx pin */
	*REG_PTR(gpio::base_addr,gpio::out) |= (UINT32_C(1) << m_tx_pin);
	*REG_PTR(gpio::base_addr,gpio::dir) |= (UINT32_C(1) << m_tx_pin);
	*REG_PTR(uart::base_addr,uart::pseltxd) = m_tx_pin;
	m_tx_busy = false;
	m_rx_rdy = false;
}

bool com_serial::open(void)
{
	if(!m_open) {

		m_rx_c_buff.clear();
		m_tx_c_buff.clear();
		m_tx_busy = false;
		interruptOwner = this;

		// clear all interrupts
		*REG_PTR(uart::base_addr,uart::event_cts) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_error) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_ncts) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_rxdrdy) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_txdrdy) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_rxto) = UINT32_C(0x0);
		// set the baud rate
		*REG_PTR(uart::base_addr,uart::baudrate) = m_baud;
		// enable interrupts
		*REG_PTR(uart::base_addr,uart::intenset) |=
				(event_rxdrdy | event_txdrdy | event_error | event_rxto);
		// Enable ARM interrupt controller
		NVIC_EnableIRQ(UARTE0_UART0_IRQn);
		// enable the uart module
		*REG_PTR(uart::base_addr,uart::enable) = UINT32_C(0x4);

		m_open = true;
		*REG_PTR(uart::base_addr,uart::task_start_rx) = UINT32_C(1);
		return true;
	}
	return false;
}

bool com_serial::close(void)
{
	if(m_open) {
		m_open = false;
		interruptOwner = nullptr;
		// clear all interrupts
		*REG_PTR(uart::base_addr,uart::event_cts) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_error) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_ncts) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_rxdrdy) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_txdrdy) = UINT32_C(0x0);
		*REG_PTR(uart::base_addr,uart::event_rxto) = UINT32_C(0x0);
		// disable ARM interrupt controller
		NVIC_DisableIRQ(UARTE0_UART0_IRQn);
		// disable interrupts
		*REG_PTR(uart::base_addr,uart::intenclr) |=
				(event_rxdrdy | event_txdrdy | event_error | event_rxto);
		// disable the uart module
		*REG_PTR(uart::base_addr,uart::enable) = UINT32_C(0x0);
		return true;
	}
	return false;
}

void com_serial::write(const uint8_t* buff, uint8_t length)
{
	if(m_open) {
		// disable tx interrupt
		*REG_PTR(uart::base_addr,uart::intenclr) |= event_txdrdy;

		bool reload = m_tx_c_buff.empty();
		for(uint8_t i = 0; i < length; i++) {
			m_tx_c_buff.in(buff[i]);
		}
		if(!reload) {
			tx_byte();
		}

		// enable tx interrupt
		*REG_PTR(uart::base_addr,uart::intenset) |= event_txdrdy;
	}
}

void com_serial::write(const char* buff, uint8_t length)
{
	if(m_open) {
		// disable tx interrupt
		*REG_PTR(uart::base_addr,uart::intenclr) |= event_txdrdy;

		bool reload = m_tx_c_buff.empty();
		for(uint8_t i = 0; i < length; i++) {
			m_tx_c_buff.in(buff[i]);
		}
		if(reload) {
			tx_byte();
		}

		// enable tx interrupt
		*REG_PTR(uart::base_addr,uart::intenset) |= event_txdrdy;
	}
}
void com_serial::write(const int var, const uint8_t length)
{
	if(m_open) {
		// disable tx interrupt
		*REG_PTR(uart::base_addr,uart::intenclr) |= event_txdrdy;
		char buff[length] = {0};
		int L = sprintf(buff,"%d",var);

		bool reload = m_tx_c_buff.empty();
		for(uint8_t i = 0; i < L; i++) {
			m_tx_c_buff.in(buff[i]);
		}
		if(!reload) {
			tx_byte();
		}

		// enable tx interrupt
		*REG_PTR(uart::base_addr,uart::intenset) |= event_txdrdy;
	}
}
uint8_t com_serial::read(uint8_t* buff)
{
	uint8_t count = 0;
	if(m_open) {
		// disable rx interrupt
		*REG_PTR(uart::base_addr,uart::intenclr) |= event_rxdrdy;

		uint8_t size = m_rx_c_buff.size();
		for(int i = 0; i < size; i++) {
			buff[i] = m_tx_c_buff.out();
			count++;
		}
		*REG_PTR(uart::base_addr,uart::event_rxdrdy) = 0UL;
		// enable rx interrupt
		*REG_PTR(uart::base_addr,uart::intenset) |= event_rxdrdy;
		m_rx_rdy = false;
	}

	return count;
}

bool com_serial::is_end_rx(void)
{
	return m_rx_rdy;
}

