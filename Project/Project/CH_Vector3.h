#ifndef __CH_VECTOR3_H__
#define __CH_VECTOR3_H__

#include "CH_Scalar.h"
#include "Vector3.h"

typedef CH::Vector3<CH_Scalar> CH_Vector3;

#ifdef CPU_CMP

inline bool operator==(const CH_Vector3& p1, const CH_Vector3& p2)
{
	const unsigned int *i1 = (const unsigned int *)&p1;
	const unsigned int *i2 = (const unsigned int *)&p2;
	return i1[0] == i2[0] && i1[1] == i2[1] && i1[2] == i2[2];
}

#else

inline bool operator==(const CH_Vector3& p1, const CH_Vector3& p2)
{
	return p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2];
}

#endif

#endif
