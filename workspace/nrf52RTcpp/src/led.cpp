/*
 * led.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#include "led.hpp"

led::led(const std::uint32_t pin) : m_pin(pin)
{
	nrf_gpio_pin_set(m_pin);
	nrf_gpio_cfg_output(m_pin);
}
void led::on(void) const
{
	nrf_gpio_pin_clear(m_pin);
}
void led::off(void) const
{
	nrf_gpio_pin_set(m_pin);
}
void led::toggle(void) const
{
	nrf_gpio_pin_toggle(m_pin);
}


