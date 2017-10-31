/*
 * tasks.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: Ehud Frank
 */

#include "tasks.hpp"

//static members
comm_tasker* comm_tasker::obj;

comm_tasker::comm_tasker(UBaseType_t priority, port_base* port,
		protocol_base* protocol) :
		Thread("RX_UART", 128, priority), m_port(port), m_protocol(protocol) {
//  Now that construction is completed, we start the thread.
	obj = this;
	Start();
}

void comm_tasker::Run() {
	while (true) {
		m_port->clbck_task_smphr.Take(portMAX_DELAY);
		m_protocol->run();
	}
}
