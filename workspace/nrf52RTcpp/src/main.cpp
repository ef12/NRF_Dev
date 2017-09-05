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

#include "mcal_reg.hpp"
#include <stdbool.h>
#include <stdint.h>
#include "led.hpp"
#include "nrf_delay.h"
#include "boards.h"

/**
 * @brief Function for application main entry.
 */
int main(void)
{
	uint8_t button_state[BUTTONS_NUMBER][2];
	led * leds[4];
	// Configure board LEDs.
	led led1(board::led1_pin);
	leds[0] = &led1;
	led led2(board::led2_pin);
	leds[1] = &led2;
	led led3(board::led3_pin);
	leds[2] = &led3;
	led led4(board::led4_pin);
	leds[3] = &led4;
    // Turn on the LEDs
	for(std::uint8_t i = 0; i < board::num_of_leds; i++) {
		leds[i]->on();
		nrf_delay_ms(200);
	}
    // Configure board Buttons.
    bsp_board_buttons_init();
    // Turn off the LEDs
    for(std::uint8_t i = 0; i < board::num_of_leds; i++) {
    		leds[i]->off();
    		nrf_delay_ms(200);
    	}
    // Forever loop
    while (true) {
    	// Scan the buttons state
        for (std::uint8_t i = 0; i < BUTTONS_NUMBER; i++) {
        		button_state[i][0] = button_state[i][1];
        		button_state[i][1] = bsp_board_button_state_get(i);
        		// Toggle LED if button was pressed (rising edge event)
        		if(button_state[i][0] < button_state[i][1]) {
        			leds[i]->toggle();
        		}
		}
        // wait for 100ms for de-bouncing
        nrf_delay_ms(100);
    }
}

/**
 *@}
 **/
