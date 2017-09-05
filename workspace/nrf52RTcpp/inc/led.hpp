/*
 * led.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_LED_HPP_
#define INC_LED_HPP_

#include <cstdint>
#include "mcal_reg.hpp"
#include "nrf_gpio.h"

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



#endif /* INC_LED_HPP_ */
