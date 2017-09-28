#include <stdint.h>
#include <string.h>
#include "pwm.hpp"

using namespace mcal;
using namespace mcal::reg;
using namespace ns_pwm;

simple_pwm::simple_pwm(const std::uint32_t * const pin, const std::uint32_t base_addrs)
: m_pin(pin), m_base_addrs(base_addrs)
{
	for(uint8_t i = 0; i < pwm_ch_num; i++) {
		if(!(m_pin[i] & mcal::bit_31)) {
			*REG_PTR(gpio::base_addr,gpio::out) |= (UINT32_C(1) << m_pin[i]);
			*REG_PTR(gpio::base_addr,gpio::dir) |= (UINT32_C(1) << m_pin[i]);
		}
	}
}

void simple_pwm::set_duty(const pwm_channel_t ch, const std::uint16_t duty)
{
	m_duty[ch] = duty;
	*REG_PTR(m_base_addrs,pwm::seq_start[0]) =
			*REG_PTR(m_base_addrs,pwm::seq_start[1]) = UINT32_C(0x1);
}

uint16_t simple_pwm::get_duty(const pwm_channel_t ch)
{
	return m_duty[ch];
}

void simple_pwm::init(void)
{
	*REG_PTR(m_base_addrs,pwm::psel_out[0]) = m_pin[0];
	*REG_PTR(m_base_addrs,pwm::psel_out[1]) = m_pin[1];
	*REG_PTR(m_base_addrs,pwm::psel_out[2]) = m_pin[2];
	*REG_PTR(m_base_addrs,pwm::psel_out[3]) = m_pin[3];

	*REG_PTR(m_base_addrs,pwm::enable) = UINT32_C(0x1);
	*REG_PTR(m_base_addrs,pwm::mode) = UINT32_C(0x0);
	*REG_PTR(m_base_addrs,pwm::prescalar) = UINT32_C(0x04); // 1MHz

	*REG_PTR(m_base_addrs,pwm::countertop) = pwm_max_count;
	*REG_PTR(m_base_addrs,pwm::loop) = UINT32_C(0x1);
	*REG_PTR(m_base_addrs,pwm::decoder) = UINT32_C(0x2);
	*REG_PTR(m_base_addrs,pwm::seq_ptr[0]) =
			*REG_PTR(m_base_addrs,pwm::seq_ptr[1]) = (uintptr_t)(m_duty);
	*REG_PTR(m_base_addrs,pwm::seq_cnt[0]) =
			*REG_PTR(m_base_addrs,pwm::seq_cnt[1]) = UINT32_C(0x4);

	*REG_PTR(m_base_addrs,pwm::seq_refresh[0]) =
			*REG_PTR(m_base_addrs,pwm::seq_refresh[1]) = UINT32_C(0x0);
	*REG_PTR(m_base_addrs,pwm::seq_enddelay[0]) =
			*REG_PTR(m_base_addrs,pwm::seq_enddelay[1]) = UINT32_C(0x0);

	*REG_PTR(m_base_addrs,pwm::seq_start[0]) =
			*REG_PTR(m_base_addrs,pwm::seq_start[1]) = UINT32_C(0x1);
}

