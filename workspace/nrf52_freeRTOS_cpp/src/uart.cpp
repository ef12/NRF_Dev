/*
 * uart.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: user
 */
#include "uart.hpp"
using namespace cpp_freertos;
//static members
bool com_serial::m_open;
com_serial* com_serial::interruptOwner;
uart_parser* uart_parser::interruptOwner;

extern "C"
void uart_handle(app_uart_evt_t * p_event) {
	if (com_serial::interruptOwner != nullptr) {
		uint8_t cr;
		switch (p_event->evt_type) {
		case APP_UART_COMMUNICATION_ERROR:
			APP_ERROR_HANDLER(p_event->data.error_communication);
			break;
		case APP_UART_FIFO_ERROR:
			APP_ERROR_HANDLER(p_event->data.error_code);
			break;
		case APP_UART_DATA_READY:
			app_uart_get(&cr);
			if (cr == '\r') {
				if (!(com_serial::interruptOwner->rx_buffer.empty())) {
					uart_parser::interruptOwner->packet_ready.GiveFromISR(NULL);
				}
			} else {
				com_serial::interruptOwner->rx_buffer.in(cr);
			}
			app_uart_put(cr);
			break;
		case APP_UART_TX_EMPTY:
			if (!(com_serial::interruptOwner->tx_buffer.empty())) {
				app_uart_put(com_serial::interruptOwner->tx_buffer.out());
			} else {
				com_serial::interruptOwner->m_tx_busy = false;
			}

			break;
		default:
			break;
		}
	}
}


com_serial::com_serial(const uint32_t rx_pin, const uint32_t tx_pin,
		const nrf_uart_baudrate_t baud) :
		m_comm_params( { rx_pin, tx_pin,
		UART_PIN_DISCONNECTED, UART_PIN_DISCONNECTED,
				APP_UART_FLOW_CONTROL_ENABLED, false, baud }) {
	m_tx_busy = false;
	m_rx_rdy = false;
}

bool com_serial::open(void) {
	if (!m_open) {

		m_tx_busy = false;
		interruptOwner = this;

		static ret_code_t err_code;

//		uart_task ;
		APP_UART_FIFO_INIT(&m_comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
				uart_handle, APP_IRQ_PRIORITY_LOWEST, err_code);

		APP_ERROR_CHECK(err_code);

		m_open = true;

		return true;
	}
	return false;
}

bool com_serial::close(void) {
	if (m_open) {
		interruptOwner = nullptr;
		m_open = false;

		return true;
	}
	return false;
}

void com_serial::write(const uint8_t* buff, uint8_t length) {
	for (int i = 0; i < length; i++) {
		tx_buffer.in(buff[i]);
	}
	if (!m_tx_busy) {
		m_tx_busy = true;
		app_uart_put(tx_buffer.out());
	}
}

uint8_t com_serial::read(void) {
	return (rx_buffer.out());
}
bool com_serial::is_empty(void) {

	return (rx_buffer.empty());
}

uart_parser::uart_parser(UBaseType_t priority, com_serial * serial) :
		Thread("RX_UART", 128, priority), m_slave(serial) {
//  Now that construction is completed, we start the thread.
	interruptOwner = this;
	Start();
}

void uart_parser::Run() {
	while (true) {
		packet_ready.Take(portMAX_DELAY);
		m_slave->write((uint8_t*) "\n", 1);
		while (!(m_slave->is_empty())) {
			byte = m_slave->read();
			m_slave->write(&byte, 1);
		}
		m_slave->write((uint8_t*) "\r\n", (sizeof("\r\n") - 1));
	}
}

