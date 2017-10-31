/*
 * comm_protocols.hpp
 *
 *  Created on: Oct 30, 2017
 *      Author: Ehud Frank
 */

#ifndef INC_COMM_PROTOCOLS_HPP_
#define INC_COMM_PROTOCOLS_HPP_

#include "microcontroller.hpp"
#include "comm_ports.hpp"

class protocol_base {
public:
	protocol_base(port_base* port);
	virtual void run() = 0;
	virtual ~protocol_base() {
	}
protected:
	char data[128];
	void get_data(void);
private:
	port_base* m_port;
};

class protocol_A: public protocol_base {
public:
	protocol_A(mcu* mcu, port_base* port);
	virtual void run();
private:
	mcu* m_mcu;
};

class protocol_B: public protocol_base {
public:
	protocol_B(mcu* mcu, port_base* port);
	virtual void run();
private:
	mcu* m_mcu;
};




#endif /* INC_COMM_PROTOCOLS_HPP_ */
