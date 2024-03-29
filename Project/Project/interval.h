#ifndef INTERVAL_H
#define INTERVAL_H

#include <cassert>
#include <iostream>
#include <algorithm>

namespace CH
{
	template <typename Scalar>
	class Interval
	{
	public:
		Interval() { }

#if _MSC_VER <= 1200
		explicit Interval(const Scalar& x)
			: m_lb(x), m_ub(x)
		{ }

		Interval(const Scalar& lb, const Scalar& ub)
			: m_lb(lb), m_ub(ub)
		{
			assert(lb <= ub);
		}
#else
		template <typename Scalar2>
		explicit Interval(const Scalar2& x)
			: m_lb(x), m_ub(x)
		{}

		template <typename Scalar2>
		Interval(const Scalar2& lb, const Scalar2& ub)
			: m _lb(lb), m_ub(ub)
		{
			assert(lb <= ub);
		}

		template <typename Scalar2>
		Interval(const Interval<Scalar2>& z)
		{
			*this = z;
		}

		template <typename Scalar2>
		Interval<Scalar>& operator=(const Interval<Scalar2>& z)
		{
			m_lb = Scalar(z.lower());
			m_ub = Scalar(z.upper());
			return *this;
		}
#endif

		Scalar&       lower() { return m_lb; }
		const Scalar& lower() const { return m_lb; }

		Scalar&       upper() { return m_ub; }
		const Scalar& upper() const { return m_ub; }

		Scalar center() const { return (m_lb + m_ub) * Scalar(0.5); }
		Scalar extent() const { return (m_ub - m_lb) * Scalar(0.5); }

	protected:
		Scalar m_lb, m_ub;
	};

	template <typename Scalar>
	inline Interval<Scalar>
		operator+(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
	{
		return Interval<Scalar>(z1.lower() + z2.lower(),
			z1.upper() + z2.upper());
	}

	template <typename Scalar>
	inline Interval<Scalar>
		operator-(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
	{
		return Interval<Scalar>(z1.lower() - z2.upper(),
			z1.upper() - z2.lower());
	}

	template <typename Scalar>
	inline std::ostream&
		operator<<(std::ostream& os, const Interval<Scalar>& z)
	{
		return os << '[' << z.lower() << ", " << z.upper() << ']';
	}

	template <typename Scalar>
	inline Scalar
		median(const Interval<Scalar>& z)
	{
		return (z.lower() + z.upper()) * Scalar(0.5);
	}

	template <typename Scalar>
	inline Scalar
		width(const Interval<Scalar>& z)
	{
		return z.upper() - z.lower();
	}

	template <typename Scalar>
	inline bool
		overlap(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
	{
		return z1.lower() <= z2.upper() && z2.lower() <= z1.upper();
	}

	template <typename Scalar>
	inline bool
		in(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
	{
		return z2.lower() <= z1.lower() && z1.upper() <= z2.upper();
	}

	template <typename Scalar>
	inline bool
		in(Scalar x, const Interval<Scalar>& z)
	{
		return z.lower() <= x && x <= z.upper();
	}

	template <typename Scalar>
	inline Interval<Scalar>
		widen(const Interval<Scalar>& z, const Scalar& x)
	{
		return Interval<Scalar>(z.lower() - x, z.upper() + x);
	}

	template<typename Scalar>
	inline Interval<Scalar>
		hull(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
	{
		return Interval<Scalar>(GEN_min(z1.lower(), z2.lower()),
			GEN_max(z1.upper(), z2.upper()));
	}

	template<typename Scalar>
	inline Interval<Scalar>
		operator+(Scalar x, const Interval<Scalar>& z)
	{
		return Interval<Scalar>(x + z.lower(), x + z.upper());
	}
}

#endif
