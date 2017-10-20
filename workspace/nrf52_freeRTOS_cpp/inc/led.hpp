/*
 * led.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_LED_HPP_
#define INC_LED_HPP_

#include <cstdint>
#include "bsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/**
 *  C++ exceptions are used by default when constructors fail.
 *  If you do not want this behavior, define the following in your makefile
 *  or project. Note that in most / all cases when a constructor fails,
 *  it's a fatal error. In the cases when you've defined this, the new
 *  default behavior will be to issue a configASSERT() instead.
 */
#ifndef CPP_FREERTOS_NO_EXCEPTIONS
#include <exception>
#include <string>
#include <cstdio>
#ifdef CPP_FREERTOS_NO_CPP_STRINGS
#error "FreeRTOS-Addons require C++ Strings if you are using exceptions"
#endif
#endif

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
