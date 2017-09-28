/*
 * mcal_reg.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_MCAL_HPP_
#define INC_MCAL_HPP_
//#define UNIT_TEST

#include <cstdint>

namespace mcal
{
	constexpr std::uint32_t bit_0 = 1UL << 0;
	constexpr std::uint32_t bit_1 = 1UL << 1;
	constexpr std::uint32_t bit_2 = 1UL << 2;
	constexpr std::uint32_t bit_3 = 1UL << 3;
	constexpr std::uint32_t bit_4 = 1UL << 4;
	constexpr std::uint32_t bit_5 = 1UL << 5;
	constexpr std::uint32_t bit_6 = 1UL << 6;
	constexpr std::uint32_t bit_7 = 1UL << 7;
	constexpr std::uint32_t bit_8 = 1UL << 8;
	constexpr std::uint32_t bit_9 = 1UL << 9;
	constexpr std::uint32_t bit_10 = 1UL << 10;
	constexpr std::uint32_t bit_11 = 1UL << 11;
	constexpr std::uint32_t bit_12 = 1UL << 12;
	constexpr std::uint32_t bit_13 = 1UL << 13;
	constexpr std::uint32_t bit_14 = 1UL << 14;
	constexpr std::uint32_t bit_15 = 1UL << 15;
	constexpr std::uint32_t bit_16 = 1UL << 16;
	constexpr std::uint32_t bit_17 = 1UL << 17;
	constexpr std::uint32_t bit_18 = 1UL << 18;
	constexpr std::uint32_t bit_19 = 1UL << 19;
	constexpr std::uint32_t bit_20 = 1UL << 20;
	constexpr std::uint32_t bit_21 = 1UL << 21;
	constexpr std::uint32_t bit_22 = 1UL << 22;
	constexpr std::uint32_t bit_23 = 1UL << 23;
	constexpr std::uint32_t bit_24 = 1UL << 24;
	constexpr std::uint32_t bit_25 = 1UL << 25;
	constexpr std::uint32_t bit_26 = 1UL << 26;
	constexpr std::uint32_t bit_27 = 1UL << 27;
	constexpr std::uint32_t bit_28 = 1UL << 28;
	constexpr std::uint32_t bit_29 = 1UL << 29;
	constexpr std::uint32_t bit_30 = 1UL << 30;
	constexpr std::uint32_t bit_31 = 1UL << 31;

	namespace reg
	{
		inline volatile std::uint32_t* REG_PTR(uint32_t base_addr, const std::uint32_t reg)
		{
#ifdef UNIT_TEST
			return nullptr;// (reinterpret_cast<volatile std::uint32_t*>(0x79000 + reg));
#else
			return (reinterpret_cast<volatile std::uint32_t*>(base_addr + reg));
#endif

		}

		namespace gpio
		{
			constexpr std::uint32_t base_addr = UINT32_C(0x50000000);

			constexpr std::uint32_t out = UINT32_C(0x504);
			constexpr std::uint32_t dir = UINT32_C(0x514);
			constexpr std::uint32_t pin_config[32] = {
														UINT32_C(0x700), UINT32_C(0x704), UINT32_C(0x708), UINT32_C(0x70C),
														UINT32_C(0x710), UINT32_C(0x714), UINT32_C(0x718), UINT32_C(0x71C),
														UINT32_C(0x720), UINT32_C(0x724), UINT32_C(0x728), UINT32_C(0x72C),
														UINT32_C(0x730), UINT32_C(0x734), UINT32_C(0x738), UINT32_C(0x73C),
														UINT32_C(0x740), UINT32_C(0x744), UINT32_C(0x748), UINT32_C(0x74C),
														UINT32_C(0x750), UINT32_C(0x754), UINT32_C(0x758), UINT32_C(0x75C),
														UINT32_C(0x760), UINT32_C(0x764), UINT32_C(0x768), UINT32_C(0x76C),
														UINT32_C(0x770), UINT32_C(0x774), UINT32_C(0x778), UINT32_C(0x77C)
													 };

			constexpr std::uint32_t not_used = UINT32_C(0xFFFFFFFF);
		}

		namespace pwm
		{
			constexpr std::uint32_t base_addr[3] =	{
														UINT32_C(0x4001C000),
														UINT32_C(0x40021000),
														UINT32_C(0x40022000)
													};

			constexpr std::uint32_t seq_stop = UINT32_C(0x4);
			constexpr std::uint32_t seq_start[2] = { UINT32_C(0x8),UINT32_C(0xC) };

			constexpr std::uint32_t sig_short = UINT32_C(0x200);
			constexpr std::uint32_t inten = UINT32_C(0x300);
			constexpr std::uint32_t intenset = UINT32_C(0x304);
			constexpr std::uint32_t intenclr = UINT32_C(0x308);
			constexpr std::uint32_t enable = UINT32_C(0x500);
			constexpr std::uint32_t mode = UINT32_C(0x504);
			constexpr std::uint32_t countertop = UINT32_C(0x508);
			constexpr std::uint32_t prescalar = UINT32_C(0x50C);
			constexpr std::uint32_t decoder = UINT32_C(0x510);
			constexpr std::uint32_t loop = UINT32_C(0x514);

			constexpr std::uint32_t seq_ptr[2] = { UINT32_C(0x520), UINT32_C(0x540) };
			constexpr std::uint32_t seq_cnt[2] = { UINT32_C(0x524), UINT32_C(0x544) };
			constexpr std::uint32_t seq_refresh[2] = { UINT32_C(0x528), UINT32_C(0x548) };
			constexpr std::uint32_t seq_enddelay[2] = { UINT32_C(0x52C), UINT32_C(0x54C) };

			constexpr std::uint32_t psel_out[4] = 	{ 	UINT32_C(0x560), UINT32_C(0x564),
														UINT32_C(0x568), UINT32_C(0x56C) };
		}

		namespace uart
		{
			/*
			 * Base address Peripheral Instance Description Configuration
			 */
			constexpr std::uint32_t base_addr = UINT32_C(0x40002000);
			/* Register Offset Description */
			constexpr std::uint32_t task_start_rx = UINT32_C(0x000);
			constexpr std::uint32_t task_stop_rx = UINT32_C(0x004);
			constexpr std::uint32_t task_start_tx = UINT32_C(0x008);
			constexpr std::uint32_t task_stop_tx = UINT32_C(0x00C);
			constexpr std::uint32_t task_suspend = UINT32_C(0x01C);

			constexpr std::uint32_t event_cts = UINT32_C(0x100);
			constexpr std::uint32_t event_ncts = UINT32_C(0x104);
			constexpr std::uint32_t event_rxdrdy = UINT32_C(0x108);
			constexpr std::uint32_t event_txdrdy = UINT32_C(0x11C);
			constexpr std::uint32_t event_error = UINT32_C(0x124);
			constexpr std::uint32_t event_rxto = UINT32_C(0x144);	//Receiver timeout

			constexpr std::uint32_t sig_short = UINT32_C(0x200);
			constexpr std::uint32_t intenset= UINT32_C(0x304);
			constexpr std::uint32_t intenclr= UINT32_C(0x308);
			constexpr std::uint32_t errorsrc= UINT32_C(0x480);		//  Error source
			constexpr std::uint32_t enable = UINT32_C(0x500);
			constexpr std::uint32_t pselrts = UINT32_C(0x508);
			constexpr std::uint32_t pseltxd = UINT32_C(0x50C);
			constexpr std::uint32_t pselcts = UINT32_C(0x510);
			constexpr std::uint32_t pselrxd = UINT32_C(0x514);
			constexpr std::uint32_t rxd = UINT32_C(0x518);
			constexpr std::uint32_t txd = UINT32_C(0x51C);
			constexpr std::uint32_t baudrate = UINT32_C(0x524);
			constexpr std::uint32_t config = UINT32_C(0x56C);
		}
	}
	namespace board
	{
		constexpr std::uint32_t led1_pin = 17;
		constexpr std::uint32_t led2_pin = 18;
		constexpr std::uint32_t led3_pin = 19;
		constexpr std::uint32_t led4_pin = 20;

		constexpr std::uint32_t uart_rx_pin = 8;
		constexpr std::uint32_t uart_tx_pin = 6;
	}
}


#endif /* INC_MCAL_HPP_ */
