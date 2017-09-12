/*
 * mcal_reg.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_MCAL_HPP_
#define INC_MCAL_HPP_

#include <cstdint>

namespace mcal
{
	namespace reg
	{
		// GPIO		(0x50000000)
		constexpr std::uint32_t gpio_base_addr = UINT32_C(0x50000000);
		constexpr std::uint32_t gpio_out = UINT32_C(gpio_base_addr + 0x504);
		constexpr std::uint32_t gpio_dir = UINT32_C(gpio_base_addr + 0x514);
		// PWM0		(0x400C100)
		constexpr std::uint32_t pwm0_base_addr = UINT32_C(0x4001C000);
		constexpr std::uint32_t pwm0_seq_stop = UINT32_C(pwm0_base_addr + 0x4);
		constexpr std::uint32_t pwm0_seq0_start = UINT32_C(pwm0_base_addr + 0x8);
		constexpr std::uint32_t pwm0_seq1_start = UINT32_C(pwm0_base_addr + 0xC);

		constexpr std::uint32_t pwm0_short = UINT32_C(pwm0_base_addr + 0x200);
		constexpr std::uint32_t pwm0_inten = UINT32_C(pwm0_base_addr + 0x300);
		constexpr std::uint32_t pwm0_intenset = UINT32_C(pwm0_base_addr + 0x304);
		constexpr std::uint32_t pwm0_intenclr = UINT32_C(pwm0_base_addr + 0x308);
		constexpr std::uint32_t pwm0_enable = UINT32_C(pwm0_base_addr + 0x500);
		constexpr std::uint32_t pwm0_mode = UINT32_C(pwm0_base_addr + 0x504);
		constexpr std::uint32_t pwm0_countertop = UINT32_C(pwm0_base_addr + 0x508);
		constexpr std::uint32_t pwm0_prescalar = UINT32_C(pwm0_base_addr + 0x50C);
		constexpr std::uint32_t pwm0_decoder = UINT32_C(pwm0_base_addr + 0x510);
		constexpr std::uint32_t pwm0_loop = UINT32_C(pwm0_base_addr + 0x514);

		constexpr std::uint32_t pwm0_seq0_ptr = UINT32_C(pwm0_base_addr + 0x520);
		constexpr std::uint32_t pwm0_seq0_cnt = UINT32_C(pwm0_base_addr + 0x524);
		constexpr std::uint32_t pwm0_seq0_refresh = UINT32_C(pwm0_base_addr + 0x528);
		constexpr std::uint32_t pwm0_seq0_enddelay = UINT32_C(pwm0_base_addr + 0x52C);

		constexpr std::uint32_t pwm0_seq1_ptr = UINT32_C(pwm0_base_addr + 0x540);
		constexpr std::uint32_t pwm0_seq1_cnt = UINT32_C(pwm0_base_addr + 0x544);
		constexpr std::uint32_t pwm0_seq1_refresh = UINT32_C(pwm0_base_addr + 0x548);
		constexpr std::uint32_t pwm0_seq1_enddelay = UINT32_C(pwm0_base_addr + 0x54C);

		constexpr std::uint32_t pwm0_psel_out0 = UINT32_C(pwm0_base_addr + 0x560);
		constexpr std::uint32_t pwm0_psel_out1 = UINT32_C(pwm0_base_addr + 0x564);
		constexpr std::uint32_t pwm0_psel_out2 = UINT32_C(pwm0_base_addr + 0x568);
		constexpr std::uint32_t pwm0_psel_out3 = UINT32_C(pwm0_base_addr + 0x56C);
	}
	namespace board
	{
		constexpr std::uint32_t led1_pin = 17;
	}
}


#endif /* INC_MCAL_HPP_ */
