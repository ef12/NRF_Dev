/*
 * mcal_reg.hpp
 *
 *  Created on: Sep 5, 2017
 *      Author: user
 */

#ifndef INC_MCAL_REG_HPP_
#define INC_MCAL_REG_HPP_

#ifdef __cplusplus
extern "C" {
#endif
#include <cstdint>
#include "nrf52.h"

namespace
{

}
namespace board
{
	constexpr std::uint8_t num_of_leds = 4;
	constexpr std::uint32_t led1_pin = 17;
	constexpr std::uint32_t led2_pin = 18;
	constexpr std::uint32_t led3_pin = 19;
	constexpr std::uint32_t led4_pin = 20;
	constexpr std::uint32_t led_pin[num_of_leds] = {
			led1_pin, led2_pin, led3_pin, led4_pin };
}


#ifdef __cplusplus
}
#endif

#endif /* INC_MCAL_REG_HPP_ */
