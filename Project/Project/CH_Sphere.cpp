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
		// source���� target���� ���� ������ sphere�� �����Ѵ�.
	{
		CH_Scalar sqrt_sigma = CH_sqrt(sigma);
		// �츮�� ���� labmda2�� ��ȣ�� �ʿ䤿��. �׷���, ���� r_length2�� ������ ���� ���ܵ� �� �ִ�
		CH_Scalar lambda2 = (delta + sqrt_sigma) /* / r_length2 */;
		if (lambda2 >= CH_Scalar(0.0))
			// �� ray�� sphere�� ���Ѵ�.
		{
			CH_Scalar lambda1 = (delta - sqrt_sigma) / r_length2;
			if (lambda1 <= param)
				// �� ray�� sphere�� �ε�����. �ֳ��ϸ�
				// [lambda1, labmda2]�� [0, param]�� ��ø�Ǳ� �����̴�.
			{
				if (lambda1 > CH_Scalar(0.0))
				{
					param = lambda1;
					normal = (source + r * lambda1) / m_radius;
					// NB : normal�� normalize�ϱ� ���� m_raidus�� ������.
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