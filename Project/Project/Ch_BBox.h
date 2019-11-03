#ifndef __CH_BBOX_H__
#define __CH_BBOX_H__

#include "CH_Scalar.h"
#include "CH_Point3.h"
#include "CH_Vector3.h"

#include "Tuple3.h"
#include "CH_Interval.h"

class CH_BBox : public CH::Tuple3<CH_Interval>
{
public:
	CH_BBox() { }
	CH_BBox(const CH_Point3& p)
		: CH::Tuple3<CH_Interval>(CH_Interval(p[0]), 
			CH_Interval(p[1]),
			CH_Interval(p[2]))
	{ }
	CH_BBox(const CH_Point3& lb, const CH_Point3& ub)
		: CH::Tuple3<CH_Interval>(CH_Interval(lb[0], ub[0]),
			CH_Interval(lb[1], ub[1]), 
			CH_Interval(lb[2], ub[2]))
	{ }
	CH_BBox(const CH_Interval& x, const CH_Interval& y, const CH_Interval& z)
		: CH::Tuple3<CH_Interval>(x, y, z)
	{ }

	CH_Point3 getMin() const
	{
		return CH_Point3(m_co[0].lower(), m_co[1].lower(), m_co[2].lower());
	}

	CH_Point3 getMax() const
	{
		return CH_Point3(m_co[0].upper(), m_co[1].upper(), m_co[2].upper());
	}

	CH_Point3 getCenter() const
	{
		return CH_Point3(CH::median(m_co[0]), CH::median(m_co[1]), CH::median(m_co[2]));
	}

	CH_Vector3 getExtent() const
	{
		return CH_Vector3(CH::width(m_co[0]) * CH_Scalar(0.5), CH::width(m_co[1]) * CH_Scalar(0.5), CH::width(m_co[2]) * CH_Scalar(0.5));
	}

	void extend(const CH_Vector3& v)
	{
		m_co[0] = CH::widen(m_co[0], v[0]);
		m_co[1] = CH::widen(m_co[1], v[1]);
		m_co[2] = CH::widen(m_co[2], v[2]);
	}

	bool overlaps(const CH_BBox& b) const
	{
		return CH::overlap(m_co[0], b[0]) &&
			CH::overlap(m_co[1], b[1]) &&
			CH::overlap(m_co[2], b[2]);
	}

	bool inside(const CH_BBox& b) const
	{
		return CH::in(m_co[0], b[0]) &&
			CH::in(m_co[1], b[1]) &&
			CH::in(m_co[2], b[2]);
	}

	CH_BBox hull(const CH_BBox& b) const
	{
		return CH_BBox(CH::hull(m_co[0], b[0]),
			CH::hull(m_co[1], b[1]),
			CH::hull(m_co[2], b[2]));
	}

	bool contains(const CH_Point3& p) const
	{
		return CH::in(p[0], m_co[0]) && CH::in(p[1], m_co[1]) && CH::in(p[2], m_co[2]);
	}
};

inline CH_BBox operator+(const CH_BBox& b1, const CH_BBox& b2)
{
	return CH_BBox(b1[0] + b2[0], b1[1] + b2[1], b1[2] + b2[2]);
}

inline CH_BBox operator-(const CH_BBox& b1, const CH_BBox& b2)
{
	return CH_BBox(b1[0] - b2[0], b1[1] - b2[1], b1[2] - b2[2]);
}

#endif
