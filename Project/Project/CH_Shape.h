#ifndef __CH_SHAPE_H__
#define __CH_SHAPE_H__

#include <algorithm>

#include "Ch_BBox.h"

#include "CH_Transform.h"

class CH_Object;

enum CH_ShapeType
{
	COMPLEX,
	CONVEX
};

class CH_Shape
{
public:
	virtual ~CH_Shape() { }

	virtual CH_ShapeType getType() const = 0;
	virtual CH_BBox bbox(const CH_Transform& t, CH_Scalar margin) const = 0;
	virtual bool ray_cast(const CH_Point3& source, const CH_Point3& target, CH_Scalar& param, CH_Vector3& normal) const = 0;

protected:
	CH_Shape() { }
};

#endif
