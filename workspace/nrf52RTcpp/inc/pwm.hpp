#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#include <cstdint>
#include "mcal.hpp"

namespace ns_pwm
{
	typedef enum
	{
		channel_1,
		channel_2,
		channel_3,
		channel_4,
		channel_lim
	}pwm_channel_t;

	static constexpr uint32_t pwm_max_count = UINT32_C(99);
	class simple_pwm
	{
	public:
		simple_pwm(const std::uint32_t * const pin, const std::uint32_t base_addrs);
		void init(void);
		void set_duty(const pwm_channel_t ch, const std::uint16_t duty);
		uint16_t get_duty(const pwm_channel_t ch);
	private:
		static constexpr std::uint8_t pwm_ch_num = 4;
		std::uint16_t m_duty[pwm_ch_num] = {0,0,0,0};
		const std::uint32_t* const m_pin;
		const std::uint32_t m_base_addrs;
		inline std::uint32_t offset(std::uint32_t offset) { return (m_base_addrs + offset); }
	};
};
#endif /* INC_PWM_HPP_ */
