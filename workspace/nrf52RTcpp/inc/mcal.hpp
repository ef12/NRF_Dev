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
//		typedef struct {                                    /*!< GPIO Structure                                                        */
//			volatile uint32_t  RESERVED0[321];
//			volatile uint32_t  OUT;                               /*!< Write GPIO port                                                       */
//			volatile uint32_t  OUTSET;                            /*!< Set individual bits in GPIO port                                      */
//			volatile uint32_t  OUTCLR;                            /*!< Clear individual bits in GPIO port                                    */
//			volatile uint32_t  IN;                                /*!< Read GPIO port                                                        */
//			volatile uint32_t  DIR;                               /*!< Direction of GPIO pins                                                */
//			volatile uint32_t  DIRSET;                            /*!< DIR set register                                                      */
//			volatile uint32_t  DIRCLR;                            /*!< DIR clear register                                                    */
//			volatile uint32_t  LATCH;                             /*!< Latch register indicating what GPIO pins that have met the criteria
//																 set in the PIN_CNF[n].SENSE registers                                 */
//			volatile uint32_t  DETECTMODE;                        /*!< Select between default DETECT signal behaviour and LDETECT mode       */
//			volatile uint32_t  RESERVED1[118];
//			volatile uint32_t  PIN_CNF[32];                       /*!< Description collection[0]: Configuration of GPIO pins                 */
//		} nrf_gpio_t;

//		#define GPIO_BASE_ADRSS  	(0x50000000)
		constexpr std::uint32_t gpio_out = UINT32_C(0x50000000 + 0x504);
		constexpr std::uint32_t gpio_dir = UINT32_C(0x50000000 + 0x514);
	}
	namespace board
	{
		constexpr std::uint32_t led1_pin = 17;
	}
}

namespace timer
{
	static inline void nrf_delay_us(uint32_t number_of_us)
	{
		const uint32_t clock16MHz = UINT32_C(16000000);
		uint32_t SystemCoreClock /*__attribute__((used))*/ = UINT32_C(64000000);

		if (number_of_us)
		{
			__asm volatile (

	"1:\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " CMP %[SystemCoreClock], %[clock16MHz]\n"
		   " BEQ.N 2f\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
		   " NOP\n"
	"2:\n"
		   " SUBS %[number_of_us], #1\n"
		   " BNE.N 1b\n"
		: [number_of_us]    "=r"             (number_of_us)
		: [SystemCoreClock] "r"              (SystemCoreClock),
		  [clock16MHz]      "r"              (clock16MHz),
							"[number_of_us]" (number_of_us)
		);
		}
	}

	static inline void nrf_delay_ms(uint32_t number_of_ms)
	{
		nrf_delay_us(1000*number_of_ms);
	}
}


#endif /* INC_MCAL_HPP_ */
