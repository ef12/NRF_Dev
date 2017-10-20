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

using namespace cpp_freertos;
using namespace std;

class uart_task: public Thread {
public:
	uart_task(string name, int i, UBaseType_t priority,int ms_delay);

protected:
	virtual void Run();

private:
	int id;
	int m_ms_delay;
};

#define UART_TX_BUF_SIZE		256		/**< UART TX buffer size. */
#define UART_RX_BUF_SIZE		256		/**< UART RX buffer size. */
extern "C" {
void uart_handle(app_uart_evt_t * p_event);
void uart_init(void);
}

#endif /* INC_UART_HPP_ */
