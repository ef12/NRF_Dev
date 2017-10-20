/*
 * led.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#include "led.hpp"

using namespace cpp_freertos;

led::led(const std::uint32_t pin) :
		m_pin(pin) {
	nrf_gpio_cfg_output(m_pin);
}

void led::off(void) const {
	nrf_gpio_pin_clear(m_pin);
}

void led::toggle(void) const {
	nrf_gpio_pin_toggle(m_pin);
}

led_blinker::led_blinker(const char * const TimerName, TickType_t PeriodInTicks,
		const std::uint32_t pin, bool Periodic) :
		Timer(TimerName, PeriodInTicks, Periodic), led(pin) {
}

led_blinker::led_blinker(TickType_t PeriodInTicks, const std::uint32_t pin,
		bool Periodic) :
		Timer(PeriodInTicks, Periodic), led(pin) {
}

void led_blinker::Run() {
	toggle();
}

