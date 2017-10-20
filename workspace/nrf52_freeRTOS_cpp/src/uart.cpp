/*
 * uart.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: user
 */
#include "uart.hpp"

Queue uart_queue(0xFF, sizeof(uint8_t));
BinarySemaphore rx_semaphore, tx_semaphore;

//uint8_t rx_buff[UART_RX_BUF_SIZE];
//uint8_t tx_buff[UART_RX_BUF_SIZE];
//uint8_t cr;

uart_task::uart_task(string name, int i, UBaseType_t priority, int ms_delay) :
		Thread(name, 100, priority), id(i), m_ms_delay(ms_delay) {
//  Now that construction is completed, we start the thread.
	Start();
}

void uart_task::Run() {
	/* Declare the variable that will hold the values received from the queue. */
	uint8_t rx_char;
	portBASE_TYPE xStatus;
	while (true) {
		rx_semaphore.Take(portMAX_DELAY);
		if (!uart_queue.IsEmpty()) {
			uart_queue.DequeueFromISR(&rx_char, NULL);
			tx_semaphore.Give();
			app_uart_put(rx_char);
		}
	}
}

const app_uart_comm_params_t comm_params = { RX_PIN_NUMBER, TX_PIN_NUMBER,
UART_PIN_DISCONNECTED, UART_PIN_DISCONNECTED, APP_UART_FLOW_CONTROL_ENABLED,
		false, NRF_UART_BAUDRATE_115200 };
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
			rx_semaphore.GiveFromISR(NULL);
		} else {
			uart_queue.EnqueueFromISR(&cr, NULL);
			app_uart_put(cr);
		}
		break;
	case APP_UART_TX_EMPTY:
		if (tx_semaphore.TakeFromISR(NULL)) {
			rx_semaphore.GiveFromISR(NULL);
		}

		break;
	default:
		break;
	}
}

void uart_init(void) {
	ret_code_t err_code;

	static uart_task Task_1("T_1", 1, 1, 250);

	APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
			uart_handle, APP_IRQ_PRIORITY_LOWEST, err_code);

	APP_ERROR_CHECK(err_code);
}
}

