// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

//! \internal

#ifndef ADSK_EXPORT_H
#define ADSK_EXPORT_H

#if defined __cplusplus

#define EXTERN_C extern "C"

#if defined(_WIN32)
#if defined(ADSKSHADERSDK_DLL)
#define ADSK_SHADERSDK_EXPORT EXTERN_C __declspec(dllexport)
#else
#define ADSK_SHADERSDK_EXPORT EXTERN_C __declspec(dllimport)
#endif // defined(ADSKSHADERSDK_DLL)
#else
#if (defined(LINUX) || defined(MACOSX))
#define ADSK_SHADERSDK_EXPORT EXTERN_C __attribute__ ((visibility ("default")))
#else
#define ADSK_SHADERSDK_EXPORT EXTERN_C
#endif // (defined(LINUX) || defined(MACOSX))
#endif // defined(_WIN32)

#endif // __cplusplus

#endif // ADSK_EXPORT_H
