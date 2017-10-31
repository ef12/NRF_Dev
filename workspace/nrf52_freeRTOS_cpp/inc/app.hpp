/*
 * app.hpp
 *
 *  Created on: Oct 27, 2017
 *      Author: Ehud Frank
 */

#ifndef INC_APP_HPP_
#define INC_APP_HPP_

#include "led.hpp"
#include "uart.hpp"

#include "comm_ports.hpp"

// freeRTOS C++
#include "thread.hpp"

class application {
public:
	void init(void);
	void run(void);
};



#endif /* INC_APP_HPP_ */
