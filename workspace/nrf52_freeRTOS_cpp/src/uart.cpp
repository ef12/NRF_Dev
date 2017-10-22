/*
 * uart.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: user
 */
#include "uart.hpp"
using namespace cpp_freertos;

bool com_serial::m_open;
com_serial* com_serial::interruptOwner;

uart_task::uart_task(string name, int i, UBaseType_t priority, int ms_delay,
		com_serial * uart) :
		Thread(name, 100, priority), id(i), m_ms_delay(ms_delay), m_uart(uart) {
//  Now that construction is completed, we start the thread.
	Start();
}

void uart_task::Run() {
	/* Declare the variable that will hold the values received from the queue. */
	uint8_t rx_char;
	portBASE_TYPE xStatus;
	while (true) {
		m_uart->rx_semaphore.Take(portMAX_DELAY);
		if (!m_uart->uart_queue.IsEmpty()) {
			m_uart->uart_queue.DequeueFromISR(&rx_char, NULL);
			m_uart->tx_semaphore.Give();
			app_uart_put(rx_char);
		}
	}
}

extern "C" {

void uart_handle(app_uart_evt_t * p_event) {

	switch (p_event->evt_type) {
	case APP_UART_COMMUNICATION_ERROR:
		APP_ERROR_HANDLER(p_event->data.error_communication);
		break;
	case APP_UART_FIFO_ERROR:
		APP_ERROR_HANDLER(p_event->data.error_code);
		break;
	case APP_UART_DATA_READY:
		uint8_t cr;
		app_uart_get(&cr);
		if (cr == '\r') {
			app_uart_put('\r');
			app_uart_put('\n');
			com_serial::interruptOwner->rx_semaphore.GiveFromISR(NULL);
		} else {
			com_serial::interruptOwner->uart_queue.EnqueueFromISR(&cr, NULL);
			app_uart_put(cr);
		}
		break;
	case APP_UART_TX_EMPTY:
		if (com_serial::interruptOwner->tx_semaphore.TakeFromISR(NULL)) {
			com_serial::interruptOwner->rx_semaphore.GiveFromISR(NULL);
		}

		break;
	default:
		break;
	}
}

//void uart_init(void) {
//	ret_code_t err_code;
//
//	static uart_task Task_1("T_1", 1, 1, 250);
//
//	APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
//			uart_handle, APP_IRQ_PRIORITY_LOWEST, err_code);
//
//	APP_ERROR_CHECK(err_code);
//}
}

com_serial::com_serial(const uint32_t rx_pin, const uint32_t tx_pin,
		const nrf_uart_baudrate_t baud) :
		m_comm_params( { rx_pin, tx_pin,
		UART_PIN_DISCONNECTED, UART_PIN_DISCONNECTED,
				APP_UART_FLOW_CONTROL_ENABLED, false, baud }), uart_queue(0xFF,
				sizeof(uint8_t)) {
	m_tx_busy = false;
	m_rx_rdy = false;
}

bool com_serial::open(void) {
	if (!m_open) {

		m_tx_busy = false;
		interruptOwner = this;

		static ret_code_t err_code;

		static uart_task Task_1("T_1", 1, 1, 250, this);

		APP_UART_FIFO_INIT(&m_comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
				uart_handle, APP_IRQ_PRIORITY_LOWEST, err_code);

		APP_ERROR_CHECK(err_code);

		m_open = true;

		return true;
	}
	return false;
}
