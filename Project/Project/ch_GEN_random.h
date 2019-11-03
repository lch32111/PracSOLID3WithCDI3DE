#ifndef  __CH_GEN_RANDOM_H__
#define  __CH_GEN_RANDOM_H__

#ifdef MT19937

#include <limits.h>
#include <mt19937.h>

#define GEN_RAND_MAX UINT_MAX

inline void			GEN_srand(unsigned int seed)	{ init_genrand(seed); }
inline unsigned int GEN_rand()						{ return genrand_int32(); }

#else

#include <stdlib.h>

#define GEN_RAND_MAX RAND_MAX

inline void			GEN_srand(unsigned int seed) { srand(seed); }
inline unsigned int GEN_rand()					 { return rand(); }

#endif

#endif // ! __CH_GEN_RANDOM_H__

