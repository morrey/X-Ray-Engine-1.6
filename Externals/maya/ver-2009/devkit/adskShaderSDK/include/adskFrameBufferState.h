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
  \brief Structures and functions for manipulating the frame buffer state.
*/

#ifndef ADSK_FRAME_BUFFER_STATE_H
#define ADSK_FRAME_BUFFER_STATE_H

#if defined __cplusplus

#ifndef ADSK_EXPORT_H
#include "adskExport.h"
#endif

#ifndef ADSK_RENDER_PASS_TYPES_H
#include "adskRenderPassTypes.h"
#endif

#ifndef ADSK_MAYA_STATE_H
#include "adskMayaState.h"
#endif

#ifndef ADSK_MI_DATABASE_POINTER_H
#include "adskMIDataPtr.h"
#endif

#ifndef SHADER_H
#include "shader.h"
#endif

#include "adskShaderSDKNamespaceBegin.h"

/*!
  \brief Bit flags used to describe the state and rendering options
  for render passes.  The flags marked as "global" are only used on
  frame buffer 0, and store state information that is global to all
  frame buffers.
*/
enum FrameBufferFlagBits {
    FB_FLAG_NONE =                    0,       //!< No flags
    FB_FLAG_USE_TRANSPARENCY =        1 << 0,  //!< The render pass uses transparency
    FB_FLAG_HOLDOUT =                 1 << 1,  //!< The render pass uses holdout
    FB_FLAG_REFLECT_HIDDEN =          1 << 2,  //!< Hidden objects are visible in reflections for the current render pass 
    FB_FLAG_REFRACT_HIDDEN =          1 << 3,  //!< Hidden objects are visible in refractions for the current render pass 
    FB_FLAG_HIDDEN_REFLECT =          1 << 4,  //!< Hidden objects cast reflections for the current render pass 
    FB_FLAG_HIDDEN_REFRACT =          1 << 5,  //!< Hidden objects cast refractions for the current render pass 
    FB_FLAG_TRANSPARENT_ATTENUATION = 1 << 6,  //!< The render pass is to be modulated by its opacity 
    FB_FLAG_COMPUTE_SHADOWS =         1 << 7,  //!< The renderpass contains shadows
    FB_FLAG_HIDDEN_SHADOWS =          1 << 8,  //!< Hidden objects cast shadows for in the render pass
    FB_FLAG_LIGHT_ACTIVE =            1 << 9,  //!< Indicates whether the current light contributes to the render pass
    FB_FLAG_SAMPLING_LIGHT =          1 << 10, //!< Indicates that the shader is inside a light sampling loop (global)
    FB_FLAG_NON_ADSK_LIGHT =          1 << 11, //!< Indicates that the current light shader is not compliant with the SDK (global)
    FB_FLAG_NO_MASTERBEAUTY =         1 << 12  //!< Indicates that the current ray was cast solely for render passes and does not contribute to the master beauty (global)
};

typedef miInteger FrameBufferFlags;

enum FrameBufferAccumulatorFlagBits {
    FB_ACC_FLAG_NONE =                0,
    FB_ACC_FLAG_HIDDEN =              1 << 0,
    FB_ACC_FLAG_FORCE_PROPAGATION =   1 << 1
};

typedef miInteger FrameBufferAccumulatorFlags;

ADSK_SHADERSDK_EXPORT const char* const PASS_TYPE_INFO_KEY;
ADSK_SHADERSDK_EXPORT const char* const FRAME_BUFFER_INFO_KEY;

/*!
  \brief Data structure that stores frame buffer state relative
  to a specific trace recursion level.
*/
struct FrameBufferAccumulator
{
    miColor                      currentValue; //!< Accumulator for the current shading network.
    miColor                      compositedValue; //!< Accumulator for the current eye ray.
    miColor                      opacity; //!< Per-channel (rgb) accumulated opacity.
    FrameBufferAccumulatorFlags  flags; //!< Sample compositing options.
};

/*!
  \brief Data structure required to store the intermediate 
  state for controlling frame buffer operations.
*/
struct FrameBufferInfo {
    miInteger               id; //!< The frame buffer number for use with \c mi_fb_put.
    FrameBufferFlags        flags; //!< Bit mask that specifies rendering options.
    miInteger               minReflectionLevel; //!< The lowest reflection level to contribute to this pass.
    miInteger               maxReflectionLevel; //!< The highest reflection level to contribute to this pass.
    miInteger               minRefractionLevel; //!< The lowest reflection level to contribute to this pass.
    miInteger               maxRefractionLevel; //!< The highest reflection level to contribute to this pass.
    miColor                 lightIrradiance; //!< Irradiance values for the last sampled light.
    miColor                 lightFilter; //!< Proportion of light transmitted for the last sampled light.
    miColor                 lightFilterAccumulator; //!< Accumulator used internally for shadow sampling.
    miColor                 lightSampleAccumulator; //!< Accumulator used internally for light sampling.
    miInteger               integerUserParameter1; //!< General purpose user parameter.
    FrameBufferAccumulator* stack; //!< The frame buffer state stack for all recursion levels.
};

/*!
  \brief Datastructure used internally to store type information
  on material render passes.
*/
struct PassTypeInfo {
    miInteger count; //!< Number of passes of a given type.
    miInteger start; //!< Index of the first pass of a given type.
};

/*!
  \brief Tests whether a given render pass is a volume rendering pass

  \param[in] index the render pass index
  \param[in] pPassTypeInfo pointer to the pass type info array

  \return true if the pass is a volume pass
*/
inline bool isVolumePass( int index, PassTypeInfo* pPassTypeInfo)
{
    return (index >= pPassTypeInfo[LIGHT_VOLUME].start &&
        index < (pPassTypeInfo[SCENE_VOLUME].start + pPassTypeInfo[SCENE_VOLUME].count));
}

/*!
  \brief Retrieve the user data block that contains all the frame buffer
  configuration information for the current camera

  \param[in] pState the shading state

  \return The data block
*/
MIDataPtr<FrameBufferData> getFrameBufferDataBlock(miState* pState);

/*!
  \brief Retrieve pass and frame buffer information

  \param[in] pState the shading state
  \param[out] pPassTypeInfo pointer to the pass type info shader state
  \param[out] pFrameBufferInfo pointer to the frame buffer info shader state

  \return Number of frame buffers
*/
ADSK_SHADERSDK_EXPORT
unsigned int getFrameBufferInfo(
    const miState* const pState, 
    PassTypeInfo*& pPassTypeInfo, 
    FrameBufferInfo*& pFrameBufferInfo);

/*!
  \brief Retrieve non material pass frame buffer index

  \param[in] pState the shading state
  \param[in] pPassNumber the number of the pass

  \return The frame buffer index.
*/
miInteger getNonMaterialPassFrameBufferIndex(miState* pState,
                                             miInteger pPassNumber);

#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus
#endif // ADSK_FRAME_BUFFER_STATE_H
