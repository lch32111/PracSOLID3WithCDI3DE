#include "CH_Sphere.h"
#include "ch_GEN_MinMax.h"

CH_Scalar CH_Sphere::supportH(const CH_Vector3& v) const
{
	return m_radius * v.length();
}

CH_Point3 CH_Sphere::support(const CH_Vector3& v) const
{
	CH_Scalar s = v.length();

	if (s > CH_Scalar(0.0))
	{
		s = m_radius / s;
		return CH_Point3(v[0] * s, v[1] * s, v[2] * s);
	}
	
	return CH_Point3(m_radius, CH_Scalar(0.0), CH_Scalar(0.0));
}

bool CH_Sphere::ray_cast(const CH_Point3& source, const CH_Point3& target, CH_Scalar& param, CH_Vector3& normal) const
{
	CH_Vector3 r = target - source;
	CH_Scalar delta = -source.dot(r);
	CH_Scalar r_length2 = r.length2();
	CH_Scalar sigma = delta * delta - r_length2 * (source.length2() - m_radius * m_radius);

	if (sigma >= CH_Scalar(0.0))
		// source에서 target으로 가는 직선은 sphere를 교차한다.
	{
		CH_Scalar sqrt_sigma = CH_sqrt(sigma);
		// 우리는 오직 labmda2의 부호만 필요ㅏ다. 그래서, 양의 r_length2로 나누는 것이 제외될 수 있다
		CH_Scalar lambda2 = (delta + sqrt_sigma) /* / r_length2 */;
		if (lambda2 >= CH_Scalar(0.0))
			// 그 ray는 sphere를 향한다.
		{
			CH_Scalar lambda1 = (delta - sqrt_sigma) / r_length2;
			if (lambda1 <= param)
				// 그 ray는 sphere에 부딪힌다. 왜냐하면
				// [lambda1, labmda2]가 [0, param]에 중첩되기 때문이다.
			{
				if (lambda1 > CH_Scalar(0.0))
				{
					param = lambda1;
					normal = (source + r * lambda1) / m_radius;
					// NB : normal를 normalize하기 위해 m_raidus로 나눈다.
				}
				else
				{
					param = CH_Scalar(0.0);
					normal.setValue(CH_Scalar(0.0), CH_Scalar(0.0), CH_Scalar(0.0));
				}

				return true;
			}
		}
	}

	return false;
}