#ifndef CH_SPHERE_H
#define CH_SPHERE_H

#include "CH_Convex.h"

class CH_Sphere : public CH_Convex
{
public:
	CH_Sphere(CH_Scalar radius) : m_radius(radius) { }

	virtual CH_Scalar supportH(const CH_Vector3& v) const;
	virtual CH_Point3 support(const CH_Vector3& v) const;

	virtual bool ray_cast(const CH_Point3& source, const CH_Point3& target,
		CH_Scalar& param, CH_Vector3& normal) const;

protected:
	CH_Scalar m_radius;
};

#endif
