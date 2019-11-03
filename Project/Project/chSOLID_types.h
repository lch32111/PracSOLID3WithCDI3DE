#ifndef __CH_SOLID_TYPES_H__
#define __CH_SOLID_TYPES_H__

#if defined(_WIN32)
#	if defined(CH_SOLID_STATIC)
#		define DECLSPEC extern
#	elif defined(CH_SOLID_DLL_EXPORT)
#		define DECLSPEC __declspec(dllexport)
#	else
#		define DECLSPEC __declspec(dllimport)
#	endif
#else
#	define DECLSPEC extern
#endif

#define CH_DECLARE_HANDLE(name) typedef struct name##__ {int unused;} *name

typedef unsigned int	CH_Index;
typedef unsigned int	CH_Count;
typedef unsigned int	CH_Size;
typedef float			CH_Scalar;
typedef int				CH_Bool;

#define CH_FALSE 0
#define CH_TRUE 1

#define CH_CONTINUE 0
#define CH_DONE 1

typedef CH_Scalar CH_Vector3[3];
typedef CH_Scalar CH_Quaternion[4];

#endif
