// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

#ifndef ADSK_TRAVERSAL_H
#define ADSK_TRAVERSAL_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

/*!
   \brief Data structure for per-instance parameters.  This structure
   corresponds to the parameters of the DAG traversal shader.
   (see the declaration of adskTraversal in adskShaderSDK.mi)
*/
struct adskInstanceParameters {
    /*!
        \brief Per instance pass contribution encoding
    */
    miTag   passEncoding;
};

#endif // __cplusplus
#endif // ADSK_TRAVERSAL_H
