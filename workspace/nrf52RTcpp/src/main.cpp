/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */
#include <comms.hpp>
#include <cstdint>

#include "timers.hpp"
#include "mcal.hpp"
#include "led.hpp"
#include "pwm.hpp"

using namespace mcal;
using namespace mcal::reg;


using namespace ns_pwm;
using namespace ns_timers;
using namespace ns_uart;

int main(void)
{
#ifdef TEST
	uint16_t i = 0;
	//pwmInit();
	ns_pwm::simple_pwm pwm1(17);
	pwm1.init();
	while (true) {
		pwm1.set_duty(i++);
		if(i > 100)
			i=0;
		nrf_delay_ms(20);
};
#else
	// Configure board LEDs.
#ifdef TEMPLATE_LED
	// Create aled1 at pin 17
	const led_template<std::uint32_t, mcal::board::led1_pin> led1;
	// Forever loop
	while (true) {
		// Toggle LED1
		led1.toggle();
		// wait for 1sec
		nrf_delay_ms(1000);
	}
	/*
 * Cross ARM GNU Print Size arm-none-eabi-size --format=berkeley "nrf52RTcpp.elf"
		   text	   data	    bss	    dec	    hex	filename
		   2984	    112	     28	   3124	    c34	nrf52RTcpp.elf
     */
#else
// SysTick_Config(SystemCoreClock/1000);
	// Create a led object
	sys_tick led1_timer;
	sys_tick led2_timer;
	sys_tick uart_timer;
	com_serial serial(board::uart_rx_pin, board::uart_tx_pin, baud57600);

	led_port led1(board::led1_pin);
	const std::uint32_t pins_for_pwm[4] = {gpio::not_used, board::led2_pin, gpio::not_used, gpio::not_used};
	simple_pwm pwm_for_led(pins_for_pwm, pwm::base_addr[0]);
	pwm_for_led.init();
	led_pwm led2(&pwm_for_led, channel_2);
	serial.open();
	uint8_t i = 1;
	uint8_t rx_buff[64] = {0};
	__enable_irq();

	serial.write("welcome\r\n", sizeof("welcome\r\n")-1);
	// Forever loop
	while (true) {
		// wait for 1sec
		if(led1_timer.timer_expired(2000)) {
			led1_timer.save_ticks();
//			Toggle LED1
			led_toggler(&led1);
			// reduce the dimming of led 2
			led2.dimming(i++);
			if(i > pwm_max_count) { i = 0; }
		}
		if(led2_timer.timer_expired(1000)) {
			led2_timer.save_ticks();
//			 Toggle LED2
			led_toggler(&led2);
		}
		if(uart_timer.timer_expired(100)) {
			uart_timer.save_ticks();
			if(serial.is_end_rx()) {
				uint8_t L = serial.read(rx_buff);
				serial.write(rx_buff, L);
				serial.write("\r\n", sizeof("\r\n")-1);
			}
		}
	}

	/*
	 * Cross ARM GNU Print Size arm-none-eabi-size --format=berkeley "nrf52RTcpp.elf"
		 text	   data	    bss	    dec	    hex	filename
	 7292	    116	     32	   7440	   1d10	nrf52RTcpp.elf
	 */

#endif
#endif
}

/**
 *@}
 **/



