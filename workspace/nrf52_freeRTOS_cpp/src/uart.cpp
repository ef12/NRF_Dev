/*
 * uart.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: user
 */
#include "uart.hpp"

const app_uart_comm_params_t comm_params = { RX_PIN_NUMBER, TX_PIN_NUMBER,
UART_PIN_DISCONNECTED, UART_PIN_DISCONNECTED, APP_UART_FLOW_CONTROL_ENABLED,
		false, NRF_UART_BAUDRATE_115200 };
extern "C" {
uint8_t rx_buff[UART_RX_BUF_SIZE];
uint8_t tx_buff[UART_RX_BUF_SIZE];

void uart_handle(app_uart_evt_t * p_event) {
	uint8_t cr;
	static uint8_t rx_index = 0;
	static uint8_t tx_index = 0;
	static uint8_t N = 0;

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
			app_uart_put('\r');
			app_uart_put('\n');
			if (rx_index) {
				memcpy(tx_buff, rx_buff, rx_index);
				app_uart_put(tx_buff[tx_index++]);
				N = rx_index;
			}
			rx_index = 0;
		} else {
			rx_buff[rx_index++] = cr;
			app_uart_put(cr);
		}
		break;
	case APP_UART_TX_EMPTY:
		if (tx_index > N) {
			tx_index = N = 0;
		} else if (tx_index) {
			app_uart_put(tx_buff[tx_index++]);
		}
		break;
	default:
		break;
	}
}

void uart_init(void) {
	ret_code_t err_code;

	APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
			uart_handle, APP_IRQ_PRIORITY_LOWEST, err_code);

	APP_ERROR_CHECK(err_code);
}
}

