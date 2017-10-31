/*
 * microcontroller.hpp
 *
 *  Created on: Oct 30, 2017
 *      Author: Ehud Frank
 */

#ifndef INC_MICROCONTROLLER_HPP_
#define INC_MICROCONTROLLER_HPP_

#include "uart.hpp"

class mcu {
public:
	led_blinker b1, b2, b3, b4;
	uart_port uart;
	mcu() :
			b1("led1", 100, LED_1),
			b2("led2", 200, LED_2),
			b3("led3", 300, LED_3),
			b4("led4", 400, LED_4),
			uart(RX_PIN_NUMBER, TX_PIN_NUMBER)
	{
	}
};



#endif /* INC_MICROCONTROLLER_HPP_ */
