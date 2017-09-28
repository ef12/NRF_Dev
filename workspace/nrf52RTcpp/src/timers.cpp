/*
 * timers.cpp
 *
 *  Created on: Sep 18, 2017
 *      Author: user
 */
#include "timers.hpp"

using namespace ns_timers;

// static members redeclaration
uint16_t sys_tick::g_ticks;

void SysTick_Handler(void)
{
	sys_tick::g_ticks++;
}

sys_tick::sys_tick(void)
{
	m_ticks_rec = 0;
	SysTick_Config(SystemCoreClock/1000);
}

void sys_tick::save_ticks(void)
{
	m_ticks_rec = g_ticks;
}

bool sys_tick::timer_expired(uint32_t time)
{
	int32_t diff;
	// take a copy of g_ticks
	__disable_irq();
	uint16_t ticks = sys_tick::g_ticks;
	__enable_irq();

	diff = ticks - m_ticks_rec;
	if(diff >= 0) {
		return ( (ticks > (m_ticks_rec + time)) ? true:false);
	} else {
		return ( (ticks > (m_ticks_rec + time - 0xFFFF)) ? true:false);
	}
}
