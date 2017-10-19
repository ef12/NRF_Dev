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
		bool Periodic, led* p_led) :
		Timer(TimerName, PeriodInTicks, Periodic) {
	m_led = p_led;
}

led_blinker::led_blinker(TickType_t PeriodInTicks, bool Periodic, led* p_led) :
		Timer(PeriodInTicks, Periodic) {
	m_led = p_led;
}

void led_blinker::Run() {
	m_led->toggle();
}

