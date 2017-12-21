// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

/*!
  \file
  \brief Constants used in the ShaderSDK
 */

#ifndef ADSK_CONSTANTS_H
#define ADSK_CONSTANTS_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

#ifndef ADSK_EXPORT_H
#include <adskExport.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

ADSK_SHADERSDK_EXPORT const float MAYA_LUMINANCE_RED; //!< The weight of the red channel when computing luminance using \c MAYA_LUMINANCE.
ADSK_SHADERSDK_EXPORT const float MAYA_LUMINANCE_GREEN; //!< The weight of the green channel when computing luminance using \c MAYA_LUMINANCE.
ADSK_SHADERSDK_EXPORT const float MAYA_LUMINANCE_BLUE; //!< The weight of the blue channel when computing luminance using \c MAYA_LUMINANCE.

ADSK_SHADERSDK_EXPORT const miColor BLACK; //!< A color with RGB values of 0, and an alpha of 1.
ADSK_SHADERSDK_EXPORT const miColor WHITE; //!< A color with RGB values of 1, and an alpha of 1.

//! \cond DOCUMENT_CONSTANTS

ADSK_SHADERSDK_EXPORT const miInteger MAYA_MAGIC; //!< For internal use.

ADSK_SHADERSDK_EXPORT const float TRANSLUCENCE_ANGLE_FAC; //!< For internal use.
ADSK_SHADERSDK_EXPORT const float TRANSLUCENCE_FADE; //!< For internal use.

ADSK_SHADERSDK_EXPORT const float MAYA_EPS; //!< For internal use.

ADSK_SHADERSDK_EXPORT const unsigned int MAYA_CUBE_SIDE; //!< For internal use.

ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_BUMP2D; //!< For internal use.
ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_IMAGEPLANE; //!< For internal use.
ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_ENVLIGHTFOG; //!< For internal use.
ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_VOLUMEFOG; //!< For internal use.
ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_FLUID; //!< For internal use.
ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_NOAF; //!< For internal use.
ADSK_SHADERSDK_EXPORT const unsigned int MAYA_BIT_MOTION; //!< For internal use.

ADSK_SHADERSDK_EXPORT const miRay_type miRAY_MRFM_DISPLACE; //!< For internal use.

ADSK_SHADERSDK_EXPORT const miColor MAYA_BLACK; //!< For internal use. Please use \c BLACK instead.
ADSK_SHADERSDK_EXPORT const miColor MAYA_WHITE; //!< For internal use. Please use \c WHITE instead.

ADSK_SHADERSDK_EXPORT const miMatrix MAYA_NULL_MATRIX; //!< For internal use.
ADSK_SHADERSDK_EXPORT const miMatrix MAYA_IDENTITY_MATRIX; //!< For internal use.

ADSK_SHADERSDK_EXPORT const char* const MAYA_FRAMEBUFFER_DATA_SUFFIX; //!< For internal use.

//! \endcond

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus
#endif // ADSK_CONSTANTS_H
