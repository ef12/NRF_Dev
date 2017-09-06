/*
 * led.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#include <mcal.hpp>
#include "led.hpp"

led::led(const std::uint32_t pin) : m_pin(pin)
{
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << m_pin);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_dir) |= (UINT32_C(1) << m_pin);
//	nrf_gpio_pin_set(m_pin);
//	nrf_gpio_cfg_output(m_pin);
}
void led::on(void) const
{
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) &= (~(UINT32_C(1) << m_pin));
//	nrf_gpio_pin_clear(m_pin);
}
void led::off(void) const
{
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << m_pin);
//	nrf_gpio_pin_set(m_pin);
}
void led::toggle(void) const
{
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) ^= (UINT32_C(1) << m_pin);
//	nrf_gpio_pin_toggle(m_pin);
}


