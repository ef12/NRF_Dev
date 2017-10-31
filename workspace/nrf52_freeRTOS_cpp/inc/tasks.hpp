/*
 * tasks.hpp
 *
 *  Created on: Oct 30, 2017
 *      Author: Ehud Frank
 */

#ifndef INC_TASKS_HPP_
#define INC_TASKS_HPP_

#include "comm_ports.hpp"
#include "comm_protocols.hpp"
#include "thread.hpp"

class comm_tasker: public Thread {
public:
	comm_tasker(UBaseType_t priority, port_base* port, protocol_base* protocol);
protected:
	virtual void Run();
private:
	static comm_tasker* obj;
	port_base* m_port;
	protocol_base* m_protocol;
};



#endif /* INC_TASKS_HPP_ */
