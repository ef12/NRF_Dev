/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @file
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example_freertos
 *
 * @brief Blinky FreeRTOS Example Application main file.
 *
 * This file contains the source code for a sample application using FreeRTOS to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_error.h"
#include "led.hpp"

//#define ENABLE_LOOPBACK_TEST  /**< if defined, then this example will be a loopback test, which means that TX should be connected to RX to get data loopback. */

#define MAX_TEST_DATA_BYTES     (15U)                /**< max number of test bytes to be used for tx and rx. */
#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 256                         /**< UART RX buffer size. */

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
#if LEDS_NUMBER <= 2
#error "Board is not equipped with enough amount of LEDs"
#endif

int main(void) {
	ret_code_t err_code;

	const app_uart_comm_params_t comm_params = {
	RX_PIN_NUMBER,
	TX_PIN_NUMBER,
	RTS_PIN_NUMBER,
	CTS_PIN_NUMBER, APP_UART_FLOW_CONTROL_ENABLED, false,
	UART_BAUDRATE_BAUDRATE_Baud115200 };

	APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
			uart_handle, APP_IRQ_PRIORITY_LOWEST, err_code);

	APP_ERROR_CHECK(err_code);
	static led led1(LED_1), led2(LED_2), led3(LED_3);
	static led_blinker led1Blinker("led1", 1000, 1, &led1), led2Blinker("led1",
			400, 1, &led2), led3Blinker("led1", 600, 1, &led3);
	/* Initialize clock driver for better time accuracy in FREERTOS */
	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);

	led1Blinker.Start(0);
	led2Blinker.Start(0);
	led3Blinker.Start(0);

	/* Activate deep sleep mode */
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	/* Start the scheduler so the created tasks start executing. */
	vTaskStartScheduler();

	while (true) {
//		uint8_t cr;
//		while (app_uart_get(&cr) != NRF_SUCCESS)
//						;
//		while (app_uart_put(cr) != NRF_SUCCESS)
//			;
//
//		if (cr == 'q' || cr == 'Q') {
//			printf(" \r\nExit!\r\n");
//
//			while (true) {
//				// Do nothing.
//			}
//		}
	}
}

/**
 *@}
 **/
