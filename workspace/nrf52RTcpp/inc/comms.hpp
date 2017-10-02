/*
 * serial.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: user
 */

#ifndef INC_COMMS_HPP_
#define INC_COMMS_HPP_

#include <vector>
#include <stdio.h>

#include "nrf52.h"
#include "mcal.hpp"
#include "utilities.hpp"

using namespace mcal::reg;

extern "C"
void UARTE0_UART0_IRQHandler(void) __attribute((interrupt));

namespace ns_uart
{
	typedef enum
	{
		no_baud,
		baud1200 = UINT32_C(0x0004F000),	//1200 baud (actual rate: 1205)
		baud2400 = UINT32_C(0x0009D000),	// 2400 baud (actual rate: 2396)
		baud4800 = UINT32_C(0x0013B000), 	// 4800 baud (actual rate: 4808)
		baud9600 = UINT32_C(0x00275000), 	// 9600 baud (actual rate: 9598)
		baud14400 = UINT32_C(0x003B0000), 	// 14400 baud (actual rate: 14414)
		baud19200 = UINT32_C(0x004EA000), 	// 19200 baud (actual rate: 19208)
		baud28800 = UINT32_C(0x0075F000), 	// 28800 baud (actual rate: 28829)
		baud38400 = UINT32_C(0x009D5000), 	// 38400 baud (actual rate: 38462)
		baud57600 = UINT32_C(0x00EBF000), 	// 57600 baud (actual rate: 57762)
		Baud76800 = UINT32_C(0x013A9000),	// 76800 baud (actual rate: 76923)
		Baud115200 = UINT32_C(0x01D7E000),	//  115200 baud (actual rate: 115942)
		Baud230400 = UINT32_C(0x03AFB000),	//  230400 baud (actual rate: 231884)
		Baud250000 = UINT32_C(0x04000000),	//  250000 baud
		Baud460800 = UINT32_C(0x075F7000),	//  460800 baud (actual rate: 470588)
		Baud921600 = UINT32_C(0x0EBED000),	//  921600 baud (actual rate: 941176)
		Baud1M = UINT32_C(0x10000000)		//  1Mega baud
	}baudrate_t;

	class com_base
	{
	public:
		virtual ~com_base() { }
		virtual bool open(void) = 0;
		virtual bool close(void) = 0;
		virtual void write(const uint8_t* buff, uint8_t length) = 0;
		virtual uint8_t read(uint8_t* buff) = 0;
	protected:
		com_base(void) { m_rx_rdy = false; }
		bool m_rx_rdy;
	private:
		/* non copy */
		com_base(const com_base&) = delete;
		const com_base& operator = (const com_base&) = delete;
	};

	class com_serial : public com_base
	{
	public:
		typedef circ_buff<uint8_t, 64U> uart_buff_t;

		com_serial(const uint32_t rx_pin, const uint32_t tx_pin, baudrate_t baud);
		void init(void);
		virtual bool open(void);
		virtual bool close(void);
		virtual void write(const uint8_t* buff, uint8_t length);
		void write(const char* buff, uint8_t length);
		void write(const int var, const uint8_t length);
		virtual uint8_t read(uint8_t* buff);
		bool is_end_rx(void);
		virtual ~com_serial() { }
	private:
		static constexpr uint32_t event_rxdrdy = mcal::bit_2;
		static constexpr uint32_t event_txdrdy = mcal::bit_7;
		static constexpr uint32_t event_error = mcal::bit_9;
		static constexpr uint32_t event_rxto = mcal::bit_17;

		const uint32_t m_rx_pin;
		const uint32_t m_tx_pin;
		const baudrate_t m_baud;

		static bool m_open;
		static com_serial* interruptOwner;
		uart_buff_t m_rx_c_buff;
		uart_buff_t m_tx_c_buff;
		inline void tx_byte(void)
		{
			*REG_PTR(uart::base_addr,uart::task_start_tx) = UINT32_C(1);
			*REG_PTR(uart::base_addr,uart::event_txdrdy) = UINT32_C(0x0);
			m_tx_busy = true;
			*REG_PTR(uart::base_addr,uart::txd) = m_tx_c_buff.out();
		}
		bool m_tx_busy;

		friend
		void ::UARTE0_UART0_IRQHandler(void) __attribute((interrupt));
	};
}
#endif /* INC_COMMS_HPP_ */
