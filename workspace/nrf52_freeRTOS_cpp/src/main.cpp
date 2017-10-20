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
#include <iostream>

#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "nrf_uart.h"

#include "sdk_errors.h"
#include "app_error.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "led.hpp"
#include "uart.hpp"

#include "thread.hpp"
#include "tasklet.hpp"
#include "ticks.hpp"

#if LEDS_NUMBER <= 2
#error "Board is not equipped with enough amount of LEDs"
#endif

using namespace cpp_freertos;
using namespace std;

class Task: public Thread {

public:

	Task(string name, int i, int delayInSeconds) :
			Thread(name, 100, 1), id(i), DelayInSeconds(delayInSeconds) {
		//
		//  Now that construction is completed, we
		//  can safely start the thread.
		//
		Start();
	}
	;

protected:

	virtual void Run() {
		static int i = 0;
		TickType_t ticks = Ticks::TicksToMs(DelayInSeconds);
		int lid = id;
		while (true) {
			if (ticks) {
				if (lid == 1) {
					app_uart_put('1');
				}
				if (lid == 2) {
					app_uart_put('2');
				}
				Delay(ticks / portTICK_RATE_MS);
			}
		}
	}
	;

private:
	int id;
	int DelayInSeconds;
};

led_blinker led1Blinker("led1", 1000, LED_1, 1), led2Blinker("led2", 400, LED_2,
		1), led3Blinker("led3", 600, LED_3, 1);

int main(void) {
	ret_code_t err_code;
	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);

	uart_init();

	/* Initialize clock driver for better time accuracy in FREERTOS */

	led1Blinker.Start(0);
	led2Blinker.Start(0);
	led3Blinker.Start(0);

	Task Task_1("T_1", 1, 250);
	Task Task_2("T_2", 2, 1000);

	/* Activate deep sleep mode */
//	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	/* Start the scheduler so the created tasks start executing. */
//	vTaskStartScheduler();
//	cout << "Testing FreeRTOS C++ wrappers" << endl;
//	cout << "Tasklets" << endl;
	Thread::StartScheduler();

	while (true) {

	}
}

void vAssertCalled(unsigned long ulLine, const char * const pcFileName) {
//	printf("ASSERT: %s : %d\n", pcFileName, (int) ulLine);
	while (1)
		;
}

unsigned long ulGetRunTimeCounterValue(void) {
	return 0;
}

void vConfigureTimerForRunTimeStats(void) {
	return;
}

extern "C" void vApplicationMallocFailedHook(void);
void vApplicationMallocFailedHook(void) {
	while (1)
		;
}
/**
 *@}
 **/
