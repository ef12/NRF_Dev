/*
 * utilities.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: user
 */

#ifndef INC_UTILITIES_HPP_
#define INC_UTILITIES_HPP_

#include <cstdint>
#include <cstring>
#include <array>

template<typename T, const std::size_t N>
class circ_buff
{
public:
	typedef T value_type;
	typedef value_type* ptr;
	typedef const value_type* const_ptr;
	typedef std::size_t  size_type;
	typedef value_type& ref;
	typedef const value_type& const_ref;

	circ_buff(const T& value = value_type(),
				const size_type count = size_type(0U))
	: in_ptr(buffer), out_ptr(buffer)
	{
		const size_type the_count = (N < count) ? N : count;

		std::fill(in_ptr, in_ptr + the_count, value);
		in_ptr += the_count;
	}

	circ_buff(const circ_buff& other)
	: in_ptr(other.in_ptr), out_ptr(other.out_ptr)
	{
		std::copy(other.buffer, (other.buffer + N), buffer);
	}

	circ_buff& operator = (const circ_buff& other)
	{
		if(this != &other) {
			in_ptr = other.in_ptr;
			out_ptr = other.out_ptr;
			std::copy(other.buffer, other.buffer + N, buffer);
		}
		return *this;
	}

	size_type capacity() const { return N; }

	bool empty() const
	{
		return (in_ptr == out_ptr);
	}

	size_type size() const
	{
		const bool is_wrap = (in_ptr < out_ptr);

		return size_type( (is_wrap == false) ) ?
				size_type( in_ptr - out_ptr) :
				N - size_type(out_ptr - in_ptr);
	}

	void clear()
	{
		in_ptr = buffer;
		out_ptr = buffer;
	}

	void in(const value_type value)
	{
		if(in_ptr >= (buffer + N)) {
			in_ptr = buffer;
		}

		*in_ptr = value;
		++in_ptr;
	}

	value_type out()
	{
		if(out_ptr >= (buffer + N)) {
			out_ptr = buffer;
		}

		const value_type value = *out_ptr;
		++out_ptr;
		return value;
	}

	ref front()
	{
		return ( (out_ptr >= (buffer + N ) ) ?
				buffer[N-1] :
				*out_ptr );
	}

	const_ref front() const
	{
		return ( (out_ptr >= (buffer + N ) ) ?
				buffer[N-1] :
				*out_ptr );
	}

	ref back()
	{
		return ( (in_ptr >= (buffer + N ) ) ?
				buffer[N-1] :
				*in_ptr );
	}

	const_ref back() const
	{
		return ( (in_ptr >= (buffer + N ) ) ?
				buffer[N-1] :
				*in_ptr );
	}

private:
	value_type buffer[N];
	ptr in_ptr;
	ptr out_ptr;
};



#endif /* INC_UTILITIES_HPP_ */
