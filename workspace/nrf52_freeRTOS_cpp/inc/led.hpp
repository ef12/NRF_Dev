/*
 * led.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: Ehud Frank
 */

#ifndef INC_LED_HPP_
#define INC_LED_HPP_

#include "bsp.h"

#include "timer.hpp"

using namespace cpp_freertos;

class led {
public:
	//led class constructor
	led(const std::uint32_t pin);
	void toggle(void) const;
	void on(void) const;
	void off(void) const;
private:
	const uint32_t m_pin;
};

class led_blinker: public Timer, public led {
public:
	led_blinker(const char * const TimerName, TickType_t PeriodInTicks,
			const std::uint32_t pin, bool Periodic = true);
	led_blinker(TickType_t PeriodInTicks, const std::uint32_t pin,
			bool Periodic = true);
private:
	virtual void Run();
};

#define TASK_DELAY			500	/**< Task delay. Delays a LED0 task for 500 ms */

#endif /* INC_LED_HPP_ */
