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
  \brief Render pass type definitions
*/

#ifndef ADSK_RENDER_PASS_TYPES_H
#define ADSK_RENDER_PASS_TYPES_H

#if defined __cplusplus

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

/*!
  \brief The numeric ID associated with each kind of pass.
 */
typedef enum {
    BEAUTY                        = 0,  //!< Beauty pass
    AMBIENT_MATERIAL_COLOR        = 1,  //!< Ambient material color pass
    AMBIENT_IRRADIANCE            = 2,  //!< Ambient irradiance pass
    AMBIENT                       = 3,  //!< Ambient pass
    DIFFUSE_MATERIAL_COLOR        = 4,  //!< Diffuse material color pass
    DIFFUSE                       = 5,  //!< Diffuse pass
    DIFFUSE_NO_SHADOW             = 6,  //!< Diffuse pass without shadows
    SPECULAR                      = 7,  //!< Specular pass
    SPECULAR_NO_SHADOW            = 8,  //!< Specular pass without shadows
    INDIRECT                      = 9,  //!< Indirect illumination pass
    DIRECT_IRRADIANCE             = 10, //!< Direct irradiance pass
    DIRECT_IRRADIANCE_NO_SHADOW   = 11, //!< Direct irradiance pass without shadows
    SHADOW                        = 12, //!< Shadow pass (multi-channel)
    SHADOW_MONO                   = 13, //!< Shadow pass (single channel)
    RAW_SHADOW                    = 14, //!< Raw shadow pass (multi-channel)
    RAW_SHADOW_MONO               = 15, //!< Raw shadow pass (single channel)
    LIGHT_VOLUME                  = 16, //!< Light volume pass
    OBJECT_VOLUME                 = 17, //!< Object volume pass
    SCENE_VOLUME                  = 18, //!< Scene volume pass
    REFLECTION                    = 19, //!< Reflection pass
    REFRACTION                    = 20, //!< Refraction pass
    SCATTER                       = 21, //!< Scatter pass
    INCANDESCENCE                 = 22, //!< Incandescence pass
    MATTE                         = 23, //!< Matte pass
    OPACITY                       = 24, //!< Opacity pass
    TRANSLUCENCE                  = 25, //!< Translucence pass
    REFLECTED_MATERIAL_COLOR      = 26, //!< Reflected material color pass
    INCIDENCE_LIGHT_NORMAL        = 27, //!< Incidence pass (light/normal)
    REFRACTION_MATERIAL_COLOR     = 28, //!< Refraction material color pass
    GLOW_SOURCE                   = 29, //!< Base glow color pass
    CUSTOM_PASS                   = 30, //!< Custom pass
    TRANSLUCENCE_NO_SHADOW        = 31, //!< Translucence pass without shadows
    NORMAL                        = 32, //!< Normal pass
    INCIDENCE_CAMERA_NORMAL       = 33, //!< Incidence pass (camera/normal)
    BEAUTY_NO_SHADOW              = 34, //!< Beauty pass without shadows
    NUMBER_OF_PASS_TYPES          = 35  //!< Total number of pass types (must be last)
} PassTypeID;

/*!
  \brief The encoding of how the shader will affect the frame buffers.
*/
typedef enum {
    FB_WRITE_NOOP           = 0,    //!< Do not write to the frame buffers
    FB_WRITE_ADDITIVE       = 1,    //!< Add to the contents of the frame buffer
    FB_WRITE_MULTIPLICATIVE = 2,    //!< Multiply the contents of the frame buffer
    FB_WRITE_OVERWRITE      = 3     //!< Overwrite the contents of the frame buffer
} FrameBufferWriteOperationType;

/*!
  \brief The encoding of the flags pertaining to the frame buffer operation.
  
  If FB_WRITE_FLAG_SCALED is set, the frame buffer contribution will be scaled by
  FrameBufferWriteFactor before being applied to the relevant frame
  buffer.
*/
typedef enum {
    FB_WRITE_FLAG_SCALED    = 1 << 0     //!< Scale the contribution by FrameBufferWriteFactor
} FrameBufferWriteFlagsType;

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif  // __cplusplus
#endif  // ADSK_RENDER_PASS_TYPES_H
