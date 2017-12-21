#ifndef D_TRI_COLLIDER_COMMON
#define D_TRI_COLLIDER_COMMON

#include "Externals/ode/include/ode/common.h"
#include "xrPhysics/ExtendedGeom.h"
#include "dTriColliderMath.h"

extern xr_vector<flags8> gl_cl_tries_state;

// extern xr_vector<int>::iterator		I,E,B				;

//#define CONTACT(Ptr, Stride) ((dContactGeom*)(((char*)Ptr) + (Stride)))
//#define SURFACE(Ptr, Stride) ((dSurfaceParameters*)(((char*)Ptr) + (Stride - sizeof(dSurfaceParameters))))
//#define SURFACE(Ptr, Stride) ((dSurfaceParameters*) (((char*)Ptr) + (Stride+sizeof(dContactGeom))))
inline dContactGeom* CONTACT(dContactGeom* ptr, const int stride)
{
	const size_t count = stride / sizeof(dContact);
	dContact* contact = (dContact*)(uintptr_t(ptr) - uintptr_t(offsetof(dContact, geom)));
	return &(contact[count]).geom;
}

inline dSurfaceParameters* SURFACE(dContactGeom* ptr, const int stride)
{
	const size_t count = stride / sizeof(dContact);
	dContact* contact = (dContact*)(uintptr_t(ptr) - uintptr_t(offsetof(dContact, geom)));
	return &(contact[count]).surface;
}
#define NUMC_MASK (0xffff)

#define M_SIN_PI_3 REAL(0.8660254037844386467637231707529362)
#define M_COS_PI_3 REAL(0.5000000000000000000000000000000000)
#endif