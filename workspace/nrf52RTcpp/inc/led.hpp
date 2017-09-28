/*
 * led.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_LED_HPP_
#define INC_LED_HPP_

#include <cstdint>
#include "mcal.hpp"
#include "pwm.hpp"

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

//template<typename pin_type, const pin_type pin>
//class led_template
//{
//public:
//	//led_template class constructor
//	led_template()
//	{
//		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << pin);
//		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_dir) |= (UINT32_C(1) << pin);
//	}
//	static void on()
//	{
//		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) &= (~(UINT32_C(1) << pin));
//	}
//	static void off(void)
//	{
//		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << pin);
//	}
//	static void toggle(void)
//	{
//		*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) ^= (UINT32_C(1) << pin);
//	}
//};

// Polymorphism
class led_base
{
public:
	virtual void toggle() = 0;	//pure abstract member function
	virtual ~led_base() { }	// virtual distructor

	//Interface for querying the LED state
	bool state_is_on() const {return is_on; }

protected:
	bool is_on;
	// A protected default constructor
	led_base() : is_on(false) { }

private:
	// private non-implemented copy assignment copy constructor
	led_base(const led_base&) = delete;
	// private non-implemented copy assignment operator
	const led_base& operator=(const led_base&) = delete;
};

class led_port : public led_base
{
public:
	typedef std::uint32_t pin_t;

	led_port(const pin_t pin);
	virtual ~led_port() { }

	virtual void toggle(void);
private:
	pin_t m_pin;
};

class led_pwm : public led_base
{
public:
	explicit led_pwm(ns_pwm::simple_pwm * p, ns_pwm::pwm_channel_t ch)
	: m_pwm(p), m_ch(ch)
	{ m_duty = 0U; };
	virtual ~led_pwm() { }
	// Toggle LED with the pwm signal
	virtual void toggle(void);
	// This LED class also supports dimming
	void dimming(const std::uint16_t duty);
private:
	ns_pwm::simple_pwm * m_pwm;
	ns_pwm::pwm_channel_t m_ch;
	std::uint16_t m_duty;
};

void led_toggler(led_base* led);

#endif /* INC_LED_HPP_ */
