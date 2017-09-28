/*
 * led.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#include <mcal.hpp>
#include "led.hpp"

using namespace mcal::reg;

void led_toggler(led_base* led)
{
	// Use dynamic polymorphism to toggle a base class pointer
	led->toggle();
}

led::led(const std::uint32_t pin) : m_pin(pin)
{
	*REG_PTR(gpio::base_addr,gpio::out) |= (UINT32_C(1) << m_pin);
	*REG_PTR(gpio::base_addr,gpio::dir) |= (UINT32_C(1) << m_pin);
}
void led::on(void) const
{
	*REG_PTR(gpio::base_addr,gpio::out) &= (~(UINT32_C(1) << m_pin));
}
void led::off(void) const
{
	*REG_PTR(gpio::base_addr,gpio::out) |= (UINT32_C(1) << m_pin);
}
void led::toggle(void) const
{
	*REG_PTR(gpio::base_addr,gpio::out) ^= (UINT32_C(1) << m_pin);
}

// inheritance
led_port::led_port(const pin_t pin) : m_pin(pin)
{
	*REG_PTR(gpio::base_addr,gpio::out) |= (UINT32_C(1) << m_pin);
	*REG_PTR(gpio::base_addr,gpio::dir) |= (UINT32_C(1) << m_pin);
}

void led_port::toggle(void)
{
	*REG_PTR(gpio::base_addr,gpio::out) ^= (UINT32_C(1) << m_pin);
}

// Toggle LED with the pwm signal
void led_pwm::toggle(void)
{
	// Toggle the LED with the pwm signal
	is_on = (m_pwm->get_duty(m_ch) > 0U);
	m_pwm->set_duty(m_ch, is_on ? 0U : m_duty);
}
// This LED class also supports dimming
void led_pwm::dimming(const std::uint16_t duty)
{
	m_duty = duty;
//	m_pwm->set_duty(m_ch, m_duty);
}
