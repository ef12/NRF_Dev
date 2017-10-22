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

#include "pca10040.h"
#include "app_uart.h"
#include "nrf_uart.h"
#include "nrf_drv_uart.h"
#include "app_error.h"

#include "thread.hpp"
#include "ticks.hpp"
#include "queue.hpp"

#define UART_TX_BUF_SIZE		256		/**< UART TX buffer size. */
#define UART_RX_BUF_SIZE		256		/**< UART RX buffer size. */
extern "C" {
void uart_handle(app_uart_evt_t * p_event);
void uart_init(void);
}

using namespace cpp_freertos;
using namespace std;

class com_serial;
class com_base;

class uart_task: public Thread {
public:
	uart_task(string name, int i, UBaseType_t priority, int ms_delay,
			com_serial * uart);

protected:
	virtual void Run();

private:
	int id;
	int m_ms_delay;
	com_serial * m_uart;
};

class com_base {
public:
	virtual ~com_base() {
	}
	virtual bool open(void) = 0;
//	virtual bool close(void) = 0;
//	virtual void write(const uint8_t* buff, uint8_t length) = 0;
//	virtual uint8_t read(uint8_t* buff) = 0;
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

class com_serial: public com_base {
public:
	com_serial(const uint32_t rx_pin, const uint32_t tx_pin,
			const nrf_uart_baudrate_t baud);
	void init(void);
	virtual bool open(void);
//	virtual bool close(void);
//	virtual void write(const uint8_t* buff, uint8_t length);
//	virtual uint8_t read(uint8_t* buff);
	bool is_end_rx(void);
	virtual ~com_serial() {
	}
	Queue uart_queue;
	BinarySemaphore rx_semaphore, tx_semaphore;
protected:

private:
	const app_uart_comm_params_t m_comm_params;

	static bool m_open;
	static com_serial* interruptOwner;
	inline void tx_byte(void) {
		m_tx_busy = true;
	}
	bool m_tx_busy;

	friend
	void ::uart_handle(app_uart_evt_t * p_event);
};

#endif /* INC_UART_HPP_ */
