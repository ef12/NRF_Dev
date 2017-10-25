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
#include "thread.hpp"
#include "ticks.hpp"
#include "utilities.hpp"
// board header
#include "boards.h"
// Hal headers
#include "nrf_uart.h"
#include "nrf_drv_common.h"

#define UART_TX_BUF_SIZE		256		/**< UART TX buffer size. */
#define UART_RX_BUF_SIZE		256		/**< UART RX buffer size. */
extern "C" void UART0_IRQHandler(void) __attribute((interrupt));

using namespace cpp_freertos;
using namespace std;

class com_base {
public:
	typedef circ_buff<uint8_t, 128U> uart_buff_t;

	virtual ~com_base() {
	}
	virtual bool open(uint8_t id, uint32_t baud_rate) = 0;
	virtual bool close(void) = 0;
	virtual void write(const uint8_t* buff, uint8_t length) = 0;
	virtual uint8_t read(void) = 0;
	virtual bool is_empty(void) = 0;
protected:
	com_base(void) {
		m_rx_rdy = false;
	}
	bool m_rx_rdy;
private:
	/* non copy */
	com_base(const com_base&) = delete;
	const com_base& operator =(const com_base&) = delete;
};

/**
 *  freeRTOS C++ uart_tasker .
 *
 *  This is a subclass of Thread and com_serial.
 *
 */
class com_serial;
class uart_parser: public Thread {
public:
	uart_parser(UBaseType_t priority, com_serial * slave);
	BinarySemaphore packet_ready;
protected:
	virtual void Run();
private:
	com_serial * m_slave;
	static uart_parser* interruptOwner;

	uint8_t byte = 0;

	friend
	void ::UART0_IRQHandler(void) __attribute((interrupt));
};

class com_serial: public com_base {
public:
	com_serial(const uint32_t rx_pin, const uint32_t tx_pin);
	virtual bool open(uint8_t id, uint32_t baud_rate);
	virtual bool close(void);
	virtual void write(const uint8_t* buff, uint8_t length);
	void write_byte(uint8_t byte) {
		nrf_uart_txd_set(NRF_UART0, byte);
	}
	uint8_t read(void);
	uint8_t read_byte(void) {
		return (nrf_uart_rxd_get(NRF_UART0));
	}
	virtual bool is_empty(void);
protected:

private:
	const uint32_t m_rx_pin, m_tx_pin;
	uart_buff_t rx_buffer, tx_buffer;

	static bool m_open;
	static com_serial* interruptOwner;
	bool m_tx_busy;
	friend
	void ::UART0_IRQHandler(void) __attribute((interrupt));
};

#endif /* INC_UART_HPP_ */
