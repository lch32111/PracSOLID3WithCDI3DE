#ifndef __CH_SCALAR_H__
#define __CH_SCALAR_H__

#include <cmath>

#undef max

#include <cstdlib>
#include <cfloat>
#include "chSOLID_types.h"

#include "ch_GEN_MinMax.h"
#include "ch_GEN_random.h"

template <typename Scalar>
struct Scalar_traits {};

template<>
struct Scalar_traits<float>
{
	static float TwoTimesPi() { 	return 6.283185307179586232f; }
	static float epsilon() { return FLT_EPSILON; }
	static float max() { return FLT_MAX; }

	static float random() { return float(GEN_rand() / float(GEN_RAND_MAX)); }
	static float sqrt(float x) { return ::sqrtf(x); }
	static float abs(float x) { return ::fabsf(x); }
	
	static float cos(float x) { return ::cosf(x); }
	static float sin(float x) { return ::sinf(x); }
	static float tan(float x) { return ::tanf(x); }

	static float acos(float x) { return ::acosf(x); }
	static float asin(float x) { return ::asinf(x); }
	static float atan(float x) { return ::atanf(x); }
	static float atan2(float x, float y) { return ::atan2f(x, y); }

	static float exp(float x) { return ::expf(x); }
	static float log(float x) { return ::logf(x); }
	static float pow(float x, float y) { return ::powf(x, y); }
};

template<>
struct Scalar_traits<double> {
	static double TwoTimesPi() { return 6.283185307179586232; }
	static double epsilon() { return DBL_EPSILON; }
	static double max() { return DBL_MAX; }

	static double random() { return double(GEN_rand()) / double(GEN_RAND_MAX); }
	static double sqrt(double x) { return ::sqrt(x); }
	static double abs(double x) { return ::fabs(x); }

	static double cos(double x) { return ::cos(x); }
	static double sin(double x) { return ::sin(x); }
	static double tan(double x) { return ::tan(x); }

	static double acos(double x) { return ::acos(x); }
	static double asin(double x) { return ::asin(x); }
	static double atan(double x) { return ::atan(x); }
	static double atan2(double x, double y) { return ::atan2(x, y); }

	static double exp(double x) { return ::exp(x); }
	static double log(double x) { return ::log(x); }
	static double pow(double x, double y) { return ::pow(x, y); }
};

#ifdef USE_TRACER
#include "ch_ScalarTracer.h"

#ifdef USE_DOUBLES
typedef CH_ScalarTracer<double> CH_Scalar;
#else 
typedef CH_ScalarTracer<float>	CH_Scalar;
#endif

#else

#ifdef USE_DOUBLES
typedef double	CH_Scalar;
#else
typedef float	CH_Scalar;
#endif

#endif

const CH_Scalar  CH_2_PI = Scalar_traits<CH_Scalar>::TwoTimesPi();
const CH_Scalar  CH_PI = CH_2_PI * CH_Scalar(0.5);
const CH_Scalar  CH_HALF_PI = CH_2_PI * CH_Scalar(0.25);
const CH_Scalar  CH_RADS_PER_DEG = CH_2_PI / CH_Scalar(360.0);
const CH_Scalar  CH_DEGS_PER_RAD = CH_Scalar(360.0) / CH_2_PI;

const CH_Scalar  CH_EPSILON = Scalar_traits<CH_Scalar>::epsilon();
const CH_Scalar  CH_INFINITY = Scalar_traits<CH_Scalar>::max();

inline CH_Scalar CH_random() { return  Scalar_traits<CH_Scalar>::random(); }
inline CH_Scalar CH_abs(CH_Scalar x) { return Scalar_traits<CH_Scalar>::abs(x); }
inline CH_Scalar CH_sqrt(CH_Scalar x) { return Scalar_traits<CH_Scalar>::sqrt(x); }

inline CH_Scalar CH_cos(CH_Scalar x) { return Scalar_traits<CH_Scalar>::cos(x); }
inline CH_Scalar CH_sin(CH_Scalar x) { return Scalar_traits<CH_Scalar>::sin(x); }
inline CH_Scalar CH_tan(CH_Scalar x) { return Scalar_traits<CH_Scalar>::tan(x); }

inline CH_Scalar CH_acos(CH_Scalar x) { return Scalar_traits<CH_Scalar>::acos(x); }
inline CH_Scalar CH_asin(CH_Scalar x) { return Scalar_traits<CH_Scalar>::asin(x); }
inline CH_Scalar CH_atan(CH_Scalar x) { return Scalar_traits<CH_Scalar>::atan(x); }
inline CH_Scalar CH_atan2(CH_Scalar x, CH_Scalar y) { return Scalar_traits<CH_Scalar>::atan2(x, y); }

inline CH_Scalar CH_radians(CH_Scalar x) { return x * CH_RADS_PER_DEG; }
inline CH_Scalar CH_degrees(CH_Scalar x) { return x * CH_DEGS_PER_RAD; }


#endif
