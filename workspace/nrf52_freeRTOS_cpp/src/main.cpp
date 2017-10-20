// SDK headers
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "nrf_uart.h"
#include "sdk_errors.h"
#include "app_error.h"
// freeRTOS c++ headers
#include "thread.hpp"
// application headers
#include "led.hpp"
#include "uart.hpp"

#if LEDS_NUMBER <= 2
#error "Board is not equipped with enough amount of LEDs"
#endif

led_blinker led1Blinker("led1", 100, LED_1), led2Blinker("led2", 200, LED_2),
		led3Blinker("led3", 300, LED_3), led4Blinker("led4", 400, LED_4);

int main(void) {
	ret_code_t err_code;
	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);

	uart_init();

	led1Blinker.Start(0);
	led2Blinker.Start(0);
	led3Blinker.Start(0);
	led4Blinker.Start(0);

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
/**
 *@}
 **/
