/*
 * uart_drv.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: Ehud Frank
 */

#include "uart.hpp"

//static members
uart_port* uart_port::obj;

extern "C" void UART0_IRQHandler(void) {
	nrf_drv_common_irq_disable(nrf_drv_get_IRQn((void *) NRF_UART0));
	if (uart_port::obj) {
		// RX
		if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXDRDY)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
			uint8_t byte = uart_port::obj->read_byte();
			if (byte == '\r' || byte == '\n') {
				if (!(uart_port::obj->rx_buffer.empty())) {
					uart_port::obj->clbck_task_smphr.GiveFromISR(NULL);
				}
			} else {
				uart_port::obj->rx_buffer.in(byte);
			}
			uart_port::obj->write_byte(byte);
		}
		// TX
		else if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_TXDRDY)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
			if (!(uart_port::obj->tx_buffer.empty())) {
				uart_port::obj->m_tx_busy = true;
				uart_port::obj->write_byte(uart_port::obj->tx_buffer.out());
			} else {
				uart_port::obj->m_tx_busy = false;
			}
		}
		// Check for errors
		else if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_ERROR)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
		} else if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXTO)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
		}
	}

	nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *) NRF_UART0), 1);
}

uart_port::uart_port(const uint32_t rx_pin, const uint32_t tx_pin) :
		m_rx_pin(rx_pin), m_tx_pin(tx_pin) {
	//	apply_config
	nrf_gpio_pin_set(m_rx_pin);
	nrf_gpio_cfg_output(m_tx_pin);
	nrf_gpio_cfg_input(m_rx_pin, NRF_GPIO_PIN_NOPULL);
	nrf_uart_txrx_pins_set(NRF_UART0, m_tx_pin, m_rx_pin);

	obj = nullptr;
	m_tx_busy = false;
}

bool uart_port::open(uint32_t baud_rate) {
	// check if there is an object assigned to port (is open already?)
	if (obj == nullptr) {
		m_baud_rate = (nrf_uart_baudrate_t)baud_rate;
		init();
		return true;
	}
	return false;
}

bool uart_port::close(void) {
	// check if there is an object assigned to port (is open already?)
	if (obj != nullptr) {

		nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
		nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
		nrf_uart_int_disable(NRF_UART0,
				NRF_UART_INT_MASK_TXDRDY | NRF_UART_INT_MASK_RXTO);
		nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *) NRF_UART0), 1);
		nrf_uart_disable(NRF_UART0);
		// cancel the assignment of this object to the ISR (also indicate that port is open)
		obj = nullptr;

		return true;
	}
	return false;
}

void uart_port::write(const uint8_t* buff, uint8_t length) {
	for (int i = 0; i < length; i++) {
		tx_buffer.in(buff[i]);
	}
	if (!m_tx_busy) {
		m_tx_busy = true;
		write_byte(tx_buffer.out());
	}
}

uint8_t uart_port::read(void) {
	return (rx_buffer.out());
}
bool uart_port::is_empty(void) {

	return (rx_buffer.empty());
}

void uart_port::init(void) {
	m_tx_busy = false;

	rx_buffer.clear();
	tx_buffer.clear();

	nrf_uart_baudrate_set(NRF_UART0, m_baud_rate);
	nrf_uart_configure(NRF_UART0, NRF_UART_PARITY_EXCLUDED,
			NRF_UART_HWFC_DISABLED);
	nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
	nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
	nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
	nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
	nrf_uart_int_enable(NRF_UART0,
			NRF_UART_INT_MASK_TXDRDY | NRF_UART_INT_MASK_RXTO
					| NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
	nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *) NRF_UART0), 1);

	nrf_uart_enable(NRF_UART0);

	nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTTX);
	nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);
	// assign this object to the ISR (also indicate that port is open)
	obj = this;
}

