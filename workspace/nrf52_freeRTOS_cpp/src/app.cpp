/*
 * app.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: Ehud Frank
 */
#include "nrf_drv_clock.h"
#include "tasks.hpp"
#include "comm_ports.hpp"
#include "comm_protocols.hpp"
#include "app.hpp"

mcu nrf52;
protocol_A protoc_a(&nrf52, &nrf52.uart);
protocol_B protoc_b(&nrf52, &nrf52.uart);
comm_tasker task_A(1, &nrf52.uart, &protoc_a);
comm_tasker task_B(1, &nrf52.uart, &protoc_b);

void application::init(void) {
	nrf_drv_clock_init();
	nrf52.uart.open(NRF_UART_BAUDRATE_115200);
}
void application::run(void) {
	Thread::StartScheduler();
	while (true) {
	}
}

void vAssertCalled(unsigned long ulLine, const char * const pcFileName) {
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



