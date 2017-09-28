/*
 * timers.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: user
 */

#ifndef SRC_TIMERS_HPP_
#define SRC_TIMERS_HPP_

#include "nrf52.h"

extern "C"
void SysTick_Handler(void) __attribute((interrupt));

namespace ns_timers
{
	typedef enum
	{
		ticks_1ms,
		ticks_10ms,
		ticks_100ms,
		ticks_secs
	}ticks_res_t;

	class sys_tick
	{
	public:
		sys_tick(void);
		void save_ticks(void);
		bool timer_expired(uint32_t time);
	private:
		static uint16_t g_ticks;
		uint16_t m_ticks_rec;
		friend
		void ::SysTick_Handler(void) __attribute((interrupt));
	};
}


#endif /* SRC_TIMERS_HPP_ */
