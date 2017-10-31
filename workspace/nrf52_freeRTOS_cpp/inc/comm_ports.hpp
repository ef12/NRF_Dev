/*
 * nrf_modules.hpp
 *
 *  Created on: Oct 26, 2017
 *      Author: Ehud Frank
 */

#ifndef INC_port_base_HPP_
#define INC_port_base_HPP_

#include "string.h"
// board header
#include "boards.h"
#include "led.hpp"

#include "nrf_drv_common.h"
#include "utilities.hpp"

// freeRTOS C++
#include "thread.hpp"


using namespace cpp_freertos;

class port_base {
public:
	typedef circ_buff<uint8_t, 128U> uart_buff_t;

	virtual ~port_base() {
	}
	virtual bool close(void) = 0;
	virtual void write(const uint8_t* buff, uint8_t length) = 0;
	virtual uint8_t read(void) = 0;
	virtual bool is_empty(void) = 0;
	BinarySemaphore clbck_task_smphr;
protected:
	port_base(void) {
	}
private:
	/* non copy */
	port_base(const port_base&) = delete;
	const port_base& operator =(const port_base&) = delete;
};

class serial_port_base: public port_base {
public:
	virtual bool open(uint32_t baud_rate) = 0;
};

class buss_port_base: public port_base {
public:
	virtual bool open(uint8_t buss, uint8_t device, uint32_t baud_rate) = 0;
};


#endif /* INC_port_base_HPP_ */
