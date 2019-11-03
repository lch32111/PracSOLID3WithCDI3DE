#ifndef TUPLE3_H
#define TUPLE3_H

#include <cassert>
#include <iostream>

namespace CH
{
	template <typename Scalar>
	class Tuple3
	{
	public:
		Tuple3() { }

		template <typename Scalar2>
		explicit Tuple3(const Scalar2* v)
		{
			setValue(x);
		}

		template<typename Scalar2>
		Tuple3(const 
	};
}
