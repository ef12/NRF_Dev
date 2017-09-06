/*
 * led.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_LED_HPP_
#define INC_LED_HPP_

#include <mcal.hpp>
#include <cstdint>

class led
{
public:
	//led class constructor
	led(const std::uint32_t pin);
	void toggle(void) const;
	void on(void) const;
	void off(void) const;
private:
	const uint32_t m_pin;
};

template<typename pin_type, const pin_type pin>
class led_template
{
public:
	//led_template class constructor
	led_template()
	{
		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << pin);
		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_dir) |= (UINT32_C(1) << pin);
	}
	static void on()
	{
		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) &= (~(UINT32_C(1) << pin));
	}
	static void off(void)
	{
		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << pin);
	}
	static void toggle(void)
	{
		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) ^= (UINT32_C(1) << pin);
	}
};

#endif /* INC_LED_HPP_ */
