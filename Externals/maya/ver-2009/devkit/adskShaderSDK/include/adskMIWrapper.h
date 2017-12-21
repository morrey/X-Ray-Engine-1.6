// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

//! \internal

#ifndef ADSK_MI_WRAPPER_H
#define ADSK_MI_WRAPPER_H

#if defined __cplusplus

#ifndef ADSK_UTILITIES_H
#include "adskUtilities.h"
#endif

// The following is the version number for shaders that are built-in to the 
// SDK library.
// Note: user shaders that use the SDK use a user-defined version number.
//
// Version History: 
//      1: Maya 2009
#define ADSK_SHADER_VERSION 1

#define EXTERN_C extern "C"

#if defined(_WIN32)
#define ADSKMIWRAPPER_EXPORT EXTERN_C __declspec(dllexport)
#else
#if (defined(LINUX) || defined(MACOSX))
#define ADSKMIWRAPPER_EXPORT EXTERN_C __attribute__ ((visibility ("default")))
#else
#define ADSKMIWRAPPER_EXPORT EXTERN_C
#endif
#endif

#define EXPOSE_INTERNAL( Name, ResultType, Prefix )                                         \
                                                                                            \
ADSKMIWRAPPER_EXPORT void Prefix##Name##_init(miState *state,                               \
                          void *paras,                                                      \
                          miBoolean *inst_init_req){                                        \
    if (!paras){                                                                            \
        *inst_init_req = miTRUE;                                                            \
        Name##Class::init(state, static_cast<Name##Parameters*>(paras));                    \
    }                                                                                       \
    else{                                                                                   \
        void **user;                                                                        \
        mi_query(miQ_FUNC_USERPTR, state, 0, &user);                                        \
        Name##Class *ptr;																	\
		adskNewMIObjectWithParams(ptr, Name##Class, state, static_cast<Name##Parameters*>(paras)) \
        *user = ptr;                                                                        \
    }                                                                                       \
}                                                                                           \
                                                                                            \
ADSKMIWRAPPER_EXPORT void Prefix##Name##_exit(miState *state,                               \
                          void *paras){                                                     \
    if (!paras){                                                                            \
        Name##Class::exit(state, static_cast<Name##Parameters*>(paras));                    \
    }                                                                                       \
    else{                                                                                   \
        void **user;                                                                        \
        mi_query(miQ_FUNC_USERPTR, state, 0, &user);                                        \
        Name##Class *ptr = static_cast<Name##Class*>(*user);                                \
        ptr->mDestructorState = state;                                                      \
        ptr->mDestructorParameters = static_cast<Name##Parameters*>(paras);                 \
        adskDeleteMIObject(ptr);                                                            \
    }                                                                                       \
}                                                                                           \
                                                                                            \
ADSKMIWRAPPER_EXPORT int Prefix##Name##_version(void){                                      \
    return Name##Class::version();                                                          \
}                                                                                           \
                                                                                            \
ADSKMIWRAPPER_EXPORT miBoolean Prefix##Name (ResultType *result,                            \
                          miState *state,                                                   \
                          struct Name##Parameters *paras){                                  \
    void **user;                                                                            \
    mi_query(miQ_FUNC_USERPTR, state, 0, &user);                                            \
    Name##Class &shader = *(static_cast<Name##Class*>(*user));                              \
    return shader(result, state, paras);                                                    \
}

#define EXPOSE( Name, ResultType, Prefix )  EXPOSE_INTERNAL( Name, ResultType, Prefix )

#define EXPOSE_MAYA_SURFACE( Name ) EXPOSE_INTERNAL( Name, SurfaceShaderReturnType, adskMaya )

#define EXPOSE_PASS( Name ) EXPOSE_INTERNAL( Name, miColor, adskPass )

#define EXPOSE_CUSTOM_SURFACE( Name ) EXPOSE_INTERNAL( Name, SurfaceShaderReturnType,  )

#endif // __cplusplus

#endif // ADSK_MI_WRAPPER_H
