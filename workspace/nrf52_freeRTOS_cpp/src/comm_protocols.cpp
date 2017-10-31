/*
 * comm_protocols.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: user
 */
#include "comm_protocols.hpp"

class mcu;
protocol_base::protocol_base(port_base* port) :
		m_port(port) {

}
void protocol_base::get_data(void) {
	int i = 0;
	while (!(m_port->is_empty())) {
		data[i++] = (char) m_port->read();
	}
}

protocol_A::protocol_A(mcu* mcu, port_base* port) :
		protocol_base(port), m_mcu(mcu) {
}

void protocol_A::run() {
	m_mcu->uart.write((uint8_t*) "\n", 1);
	get_data();
	if (!strcmp(data, "A-start")) {
		m_mcu->b1.Start(0);
		m_mcu->b2.Start(0);
	}
	if (!strcmp(data, "A-stop")) {
		m_mcu->b1.Stop(0);
		m_mcu->b2.Stop(0);
		m_mcu->b1.off();
		m_mcu->b2.off();
	}
	memset(data, 0, sizeof(data));
	m_mcu->uart.write((uint8_t*) "\r\n", (sizeof("\r\n") - 1));
}

protocol_B::protocol_B(mcu* mcu, port_base* port) :
		protocol_base(port), m_mcu(mcu) {

}
void protocol_B::run() {
	m_mcu->uart.write((uint8_t*) "\n", 1);
	get_data();
	if (!strcmp(data, "B-start")) {
		m_mcu->b3.Start(0);
		m_mcu->b4.Start(0);
	}
	if (!strcmp(data, "B-stop")) {
		m_mcu->b3.Stop(0);
		m_mcu->b4.Stop(0);
		m_mcu->b3.off();
		m_mcu->b4.off();
	}
	memset(data, 0, sizeof(data));
	m_mcu->uart.write((uint8_t*) "\r\n", (sizeof("\r\n") - 1));
}
