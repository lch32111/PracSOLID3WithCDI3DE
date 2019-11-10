#ifndef __CH_CONVEX_H__
#define __CH_CONVEX_H__

#include "CH_Shape.h"

#include "CH_Vector3.h"
#include "CH_Point3.h"

#include "CH_Matrix3x3.h"
#include "CH_Transform.h"

class CH_Convex : public CH_Shape
{
	virtual ~CH_Convex() { }
	virtual CH_ShapeType getType() const { return CONVEX; }

	virtual CH_Scalar supportH(const CH_Vector3& v) const { return v.dot(support(v)); }
	virtual CH_Point3 support(const CH_Vector3& v) const = 0;
	virtual CH_BBox bbox() const;
	virtual CH_BBox bbox(const CH_Matrix3x3& basis) const;
	virtual CH_BBox bbox(const CH_Transform& t, CH_Scalar margin = CH_Scalar(0.0)) const;
	virtual bool ray_cast(const CH_Point3& source, const CH_Point3& target, CH_Scalar& param, CH_Vector3& normal) const;

protected:
	CH_Convex() { }
};

// GJK Methods...
bool intersect(const CH_Convex& a, const CH_Convex& b, CH_Vector3& v);

bool common_point(const CH_Convex& a, const CH_Convex& b, CH_Vector3& v, CH_Point3& pa, CH_Point3& pb);

CH_Scalar closest_points(const CH_Convex&, const CH_Convex&, CH_Scalar max_dist2, CH_Point3& pa, CH_Point3& pb);

bool penetration_depth(const CH_Convex& a, const CH_Convex& b, CH_Vector3& v, CH_Point3& pa, CH_Point3& pb);

bool hybrid_penetration_depth(const CH_Convex& a, CH_Scalar a_margin,
	const CH_Convex& b, CH_Scalar b_margin,
	CH_Vector3& v, CH_Point3& pa, CH_Point3& pb);
// GJK Methods...

#endif
