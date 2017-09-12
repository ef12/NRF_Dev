#include <stdint.h>
#include "pwm.hpp"


ns_pwm::pwm_1CH::pwm_1CH(const std::uint32_t pin) : m_pin(pin)
{
	m_duty[0] = m_duty[1] = m_duty[2] = m_duty[3] = 0x0000;
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_out) |= (UINT32_C(1) << m_pin);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::gpio_dir) |= (UINT32_C(1) << m_pin);
}

void ns_pwm::pwm_1CH::set_duty(const std::uint16_t duty)
{
	m_duty[0] = m_duty[1] = m_duty[2] = m_duty[3] = duty;
	*reinterpret_cast<std::uint32_t*>(mcal::reg::pwm0_seq0_start) =
			*reinterpret_cast<std::uint32_t*>(mcal::reg::pwm0_seq1_start) = UINT32_C(0x1);

}

void ns_pwm::pwm_1CH::init(void)
{
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_psel_out0) = m_pin;
//	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_psel_out1) = UINT32_C(0xFF);
//	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_psel_out2) = UINT32_C(0xFF);
//	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_psel_out3) = UINT32_C(0xFF);

	*reinterpret_cast<std::uint32_t*>(mcal::reg::pwm0_enable) = UINT32_C(0x1);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_mode) = UINT32_C(0x0);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_prescalar) = UINT32_C(0x04);

	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_countertop) = UINT32_C(100);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_loop) = UINT32_C(0x1);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_decoder) = UINT32_C(0x2);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq0_ptr) =
			*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq1_ptr) = (uintptr_t)(m_duty);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq0_cnt) =
			*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq1_cnt) = UINT32_C(0x4);

	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq0_refresh) =
			*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq1_refresh) = UINT32_C(0x0);
	*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq0_enddelay) =
			*reinterpret_cast<volatile std::uint32_t*>(mcal::reg::pwm0_seq1_enddelay) = UINT32_C(0x0);

	*reinterpret_cast<std::uint32_t*>(mcal::reg::pwm0_seq0_start) =
			*reinterpret_cast<std::uint32_t*>(mcal::reg::pwm0_seq1_start) = UINT32_C(0x1);
}

