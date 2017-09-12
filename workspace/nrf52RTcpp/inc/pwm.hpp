#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#include <cstdint>
#include "mcal.hpp"

namespace ns_pwm
{
	class pwm_1CH
	{
	public:
		pwm_1CH(const std::uint32_t pin);
		void init(void);
		void deinit(void);
		void set_duty(const std::uint16_t duty);
		void get_duty(void);
	private:
		std::uint16_t m_duty[4];
		const std::uint32_t m_pin;
	};
};
#endif /* INC_PWM_HPP_ */
