/*
 * uart.hpp
 *
 *  Created on: Oct 19, 2017
 *      Author: user
 */

#ifndef INC_UART_HPP_
#define INC_UART_HPP_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
// C++ freeRTOS headers
//#include "thread.hpp"
//#include "ticks.hpp"

#include "nrf_uart.h"

#include "comm_ports.hpp"
extern "C" void UART0_IRQHandler(void) __attribute((interrupt));

using namespace cpp_freertos;
using namespace std;

/**
 *  freeRTOS C++ uart_tasker .
 *
 *  This is a subclass of Thread and uart_port.
 *
 */

class uart_port: public serial_port_base {
public:
	typedef circ_buff<uint8_t, 128U> uart_buff_t;

	uart_port(const uint32_t rx_pin, const uint32_t tx_pin);
//	virtual ~uart_port();
	virtual bool open(uint32_t baud_rate);
	virtual bool close(void);
	virtual void write(const uint8_t* buff, uint8_t length);
	virtual uint8_t read(void);
	virtual bool is_empty(void);
protected:

private:
	const uint32_t m_rx_pin, m_tx_pin;
	uart_buff_t rx_buffer, tx_buffer;
	nrf_uart_baudrate_t m_baud_rate = NRF_UART_BAUDRATE_9600;

	static uart_port* obj;
	bool m_tx_busy;

	void init(void);
	uint8_t read_byte(void) {
		return (nrf_uart_rxd_get(NRF_UART0));
	}
	void write_byte(uint8_t byte) {
		nrf_uart_txd_set(NRF_UART0, byte);
	}
	friend
	void ::UART0_IRQHandler(void) __attribute((interrupt));

};

#endif /* INC_UART_HPP_ */
