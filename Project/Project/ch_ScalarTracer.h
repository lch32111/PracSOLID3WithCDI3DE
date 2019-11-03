#ifndef __CH_SCALAR_TRACER_H__
#define __CH_SCALAR_TRACER_H__

#include <cmath>
#include <iostream>
#include <cassert>

template <typename Scalar>
class CH_ScalarTracer
{
public:
	CH_ScalarTracer() { }
	explicit CH_ScalarTracer(Scalar value, Scalar error = Scalar(0.0))
		:	m_value(value), 
			m_error(value == Scalar(0.0) ? Scalar(0.0) : error)
	{ }

	Scalar getValue() const { return m_value; }
	Scalar getError() const { return m_error; }

	void setError(Scalar error) { m_error = error; }

	CH_ScalarTracer operator-() const
	{
		return CH_ScalarTracer < Scalar(-m_value, m_error);
	}

	CH_ScalarTracer operator=(Scalar value)
	{
		m_value = value;
		m_error = Scalar(0.0);
		return  *this;
	}

	CH_ScalarTracer& operator+=(const CH_ScalarTracer& x)
	{
		*this = *this + x;
		return *this;
	}

	CH_ScalarTracer& operator-=(const CH_ScalarTracer& x)
	{
		*this = *this - x;
		return *this;
	}

	CH_ScalarTracer& operator*=(const CH_ScalarTracer& x)
	{
		*this = *this * x;
		return *this;
	}

	CH_ScalarTracer& operator/=(const CH_ScalarTracer& x)
	{
		*this = *this / x;
		return *this;
	}

private:
	Scalar m_value; // the value of the scalar
	Scalar m_error; // the relative rounding error
};

/*
'm_error' 곱하기 machine epsilon (floats에 대해서는 FLT_EPSILON, double에 대해서는 DBL_EPSILON)
하는 것은 'm_value'에 있는 rounding error에 대한 측정된 upper bound를 준다.
mantissa에 있는 dirty bits의 개수는 'log(m_error) / log(2)'이고, 그래서 
만약 'm_error'가 2^24 = 16777216에 도달한다면, 그러면 우리는 한 float에 있는 mantissa에서
모든 bits를 사용한 것이다. 
그 error가 rough upper bound라는 것에 유의해라. 현실에서 i386 platforms은
더 높은 정밀도로 compound 식들을 측정할지도 모른다. 그래서 주어진 machine epsilon은
보통 대부분의 경우에 매우 크다.
*/

template <typename Scalar>
struct Scalar_traits {
	static CH_ScalarTracer<Scalar> TwoTimesPi() { return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::TwoTimesPi()); }
	static CH_ScalarTracer<Scalar> epsilon() { return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::epsilon()); }
	static CH_ScalarTracer<Scalar> max() { return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::max()); }

	static CH_ScalarTracer<Scalar> random() { return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::random()); }
	static CH_ScalarTracer<Scalar> sqrt(CH_ScalarTracer<Scalar> x) { return ::sqrt(x); }
	static CH_ScalarTracer<Scalar> abs(CH_ScalarTracer<Scalar> x) { return ::abs(x); }

	static CH_ScalarTracer<Scalar> cos(CH_ScalarTracer<Scalar> x) { return ::cos(x); }
	static CH_ScalarTracer<Scalar> sin(CH_ScalarTracer<Scalar> x) { return ::sin(x); }
	static CH_ScalarTracer<Scalar> tan(CH_ScalarTracer<Scalar> x) { return ::tan(x); }

	static CH_ScalarTracer<Scalar> acos(CH_ScalarTracer<Scalar> x) { return ::acos(x); }
	static CH_ScalarTracer<Scalar> asin(CH_ScalarTracer<Scalar> x) { return ::asin(x); }
	static CH_ScalarTracer<Scalar> atan(CH_ScalarTracer<Scalar> x) { return ::atan(x); }
	static CH_ScalarTracer<Scalar> atan2(CH_ScalarTracer<Scalar> x, CH_ScalarTracer<Scalar> y) { return ::atan2(x, y); }

	static CH_ScalarTracer<Scalar> exp(CH_ScalarTracer<Scalar> x) { return ::exp(x); }
	static CH_ScalarTracer<Scalar> log(CH_ScalarTracer<Scalar> x) { return ::log(x); }
	static CH_ScalarTracer<Scalar> pow(CH_ScalarTracer<Scalar> x, CH_ScalarTracer<Scalar> y) { return ::pow(x, y); }
};

template <class Scalar>
inline CH_ScalarTracer<Scalar> operator+(const CH_ScalarTracer<Scalar>& x,
	const CH_ScalarTracer<Scalar>& y)
{
	Scalar value = x.getValue() + y.getValue();
	return CH_ScalarTracer<Scalar>
		(
			value,
			(
				(Scalar_traits<Scalar>::abs(x.getValue()) *
				x.getError() +
				Scalar_traits<Scalar>::abs(y.getValue()) *
				y.getError()) /
				Scalar_traits<Scalar>::abs(value) + Scalar(1.0)
			)
		);
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> operator-(const CH_ScalarTracer<Scalar>& x,
	const CH_ScalarTracer<Scalar>& y)
{
	Scalar value = x.getValue() - y.getValue();
	return CH_ScalarTracer<Scalar>(
		value,
		(Scalar_traits<Scalar>::abs(x.getValue()) * x.getError() +
			Scalar_traits<Scalar>::abs(y.getValue()) * y.getError()) / Scalar_traits<Scalar>::abs(value) + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> operator*(const CH_ScalarTracer<Scalar>& x,
	const CH_ScalarTracer<Scalar>& y)
{
	return CH_ScalarTracer<Scalar>(x.getValue() * y.getValue(),
		x.getError() + y.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> operator/(const CH_ScalarTracer<Scalar>& x, const CH_ScalarTracer<Scalar>& y)
{
	return CH_ScalarTracer<Scalar>(x.getValue() / y.getValue(),
		x.getError() + y.getError() + Scalar(1.0));
}

template <typename Scalar>
inline std::ostream& operator<<(std::ostream& os, const CH_ScalarTracer<Scalar>& x)
{
	return os << x.getValue() << '[' << x.getError() << ']';
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> sqrt(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(sqrt(x.getValue()), Scalar(0.5) * x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> abs(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::abs(x.getValue()), x.getError());
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> cos(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::cos(x.getValue()), x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> sin(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::sin(x.getValue()), x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> tan(const CH_ScalarTracer<Scalar>& x)
{
	Scalar value = Scalar_traits<Scalar>::tan(x.getValue());
	return CH_ScalarTracer<Scalar>(value, (Scalar(1.0) + value * value) * x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> acos(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::acos(x.getValue()), x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> asin(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::asin(x.getValue()), x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> atan(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::atan(x.getValue()), x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> atan2(const CH_ScalarTracer<Scalar>& x, const CH_ScalarTracer<Scalar>& y)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::atan2(x.getValue(), y.getValue()), x.getError() + y.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> exp(const CH_ScalarTracer<Scalar>& x)
{
	Scalar value = Scalar_traits<Scalar>::exp(x.getValue());
	return CH_ScalarTracer<Scalar>(value, value * x.getError() + Scalar(1.0));
}

template <typename Scalar>
inline CH_ScalarTracer<Scalar> log(const CH_ScalarTracer<Scalar>& x)
{
	return CH_ScalarTracer<Scalar>(Scalar_traits<Scalar>::log(x.getValue()), x.getError() / x.getValue() + Scalar(1.0));
}


template <typename Scalar>
inline CH_ScalarTracer<Scalar> pow(const CH_ScalarTracer<Scalar>& x, const CH_ScalarTracer<Scalar>& y)
{
	assert(x.getValue() >= Scalar(0.0));
	Scalar value = Scalar_traits<Scalar>::pow(x.getValue(), y.getValue());
	return CH_ScalarTracer<Scalar>(value,
		Scalar_traits<Scalar>::abs(y.getValue()) * x.getError() +
		Scalar_traits<Scalar>::abs(value * Scalar_traits<Scalar>::log(x.getValue())) * y.getError() + Scalar(1.0));
}

#endif
