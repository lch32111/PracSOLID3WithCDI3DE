#ifndef __CH_GEN_MINMAX_H__
#define __CH_GEN_MINMAX_H__

template <class T>
inline const T& GEN_min(const T& a, const T& b)
{
	return b < a ? b : a;
}

template <class T>
inline const T& GEN_max(const T& a, const T& b)
{
	return a < b ? b : a;
}

template <class T>
inline const T& GEN_clmaped(const T& a, const T& lb, const T& ub)
{
	return a < lb ? lb : (ub < a ? ub : a);
}

template <class T>
inline void GEN_set_min(T& a, const T& b)
{
	if (b < a)
	{
		a = b;
	}
}

template <class T>
inline void GEN_set_max(T& a, const T& b)
{
	if (a < b)
	{
		a = b;
	}
}

template <class T>
inline void GEN_clamp(T& a, const T& lb, const T& ub)
{
	if (a < lb)
	{
		a = lb;
	}
	else if (ub < a)
	{
		a = ub;
	}
}

#endif
