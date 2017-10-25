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

extern "C" void UART0_IRQHandler(void) {
	nrf_drv_common_irq_disable(nrf_drv_get_IRQn((void *) NRF_UART0));
	if (com_serial::interruptOwner) {
		// RX
		if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXDRDY)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
//			app_uart_get(&cr);
//			if (cr == '\r') {
//				if (!(com_serial::interruptOwner->rx_buffer.empty())) {
//					uart_parser::interruptOwner->packet_ready.GiveFromISR(NULL);
//				}
//			} else {
//				com_serial::interruptOwner->rx_buffer.in(cr);
//			}
//			app_uart_put(cr);
//			break;
			uint8_t byte = com_serial::interruptOwner->read_byte();
			if (byte == '\r') {
				if (!(com_serial::interruptOwner->rx_buffer.empty())) {
					uart_parser::interruptOwner->packet_ready.GiveFromISR(NULL);
				}
			} else {
				com_serial::interruptOwner->rx_buffer.in(byte);
			}
			com_serial::interruptOwner->write_byte(byte);
			nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);
		}
		// TX
		else if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_TXDRDY)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
			if (!(com_serial::interruptOwner->tx_buffer.empty())) {
				com_serial::interruptOwner->m_tx_busy = true;
				nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTTX);
				com_serial::interruptOwner->write_byte(
						com_serial::interruptOwner->tx_buffer.out());
			} else {
				com_serial::interruptOwner->m_tx_busy = false;
			}
		}
		// Check for errors
		else if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_ERROR)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
		} else if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXTO)) {
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
//		} else {
//			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_CTS);
//			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_NCTS);
		}
	}

	nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *) NRF_UART0), 1);
}
//
//void uart_handle(app_uart_evt_t * p_event) {
//if (com_serial::interruptOwner != nullptr) {
//	uint8_t cr;
//	switch (p_event->evt_type) {
//	case APP_UART_COMMUNICATION_ERROR:
//		APP_ERROR_HANDLER(p_event->data.error_communication);
//		break;
//	case APP_UART_FIFO_ERROR:
//		APP_ERROR_HANDLER(p_event->data.error_code);
//		break;
//	case APP_UART_DATA_READY:
//		app_uart_get(&cr);
//		if (cr == '\r') {
//			if (!(com_serial::interruptOwner->rx_buffer.empty())) {
//				uart_parser::interruptOwner->packet_ready.GiveFromISR(NULL);
//			}
//		} else {
//			com_serial::interruptOwner->rx_buffer.in(cr);
//		}
//		app_uart_put(cr);
//		break;
//	case APP_UART_TX_EMPTY:
//		if (!(com_serial::interruptOwner->tx_buffer.empty())) {
//			app_uart_put(com_serial::interruptOwner->tx_buffer.out());
//		} else {
//			com_serial::interruptOwner->m_tx_busy = false;
//		}
//
//		break;
//	default:
//		break;
//	}
//}
//}

com_serial::com_serial(const uint32_t rx_pin, const uint32_t tx_pin) :
		m_rx_pin(rx_pin), m_tx_pin(tx_pin) {
	//	apply_config
	nrf_gpio_pin_set(m_rx_pin);
	nrf_gpio_cfg_output(m_tx_pin);
	nrf_gpio_cfg_input(m_rx_pin, NRF_GPIO_PIN_NOPULL);
	nrf_uart_txrx_pins_set(NRF_UART0, m_tx_pin, m_rx_pin);

	m_tx_busy = false;
	m_rx_rdy = false;
}

bool com_serial::open(uint8_t id, uint32_t baud_rate) {
	if (!m_open) {
		m_tx_busy = false;
		interruptOwner = this;
		rx_buffer.clear();
		tx_buffer.clear();

		nrf_uart_baudrate_set(NRF_UART0, (nrf_uart_baudrate_t) baud_rate);
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
		m_open = true;

		write((uint8_t*) "*", 1);

		return true;
	}
	return false;
}

bool com_serial::close(void) {
	if (m_open) {
		interruptOwner = nullptr;
		nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
		nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
		nrf_uart_int_disable(NRF_UART0,
				NRF_UART_INT_MASK_TXDRDY | NRF_UART_INT_MASK_RXTO);
		nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *) NRF_UART0), 1);
		nrf_uart_disable(NRF_UART0);
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
		write_byte(tx_buffer.out());
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

