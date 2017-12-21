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
  \brief Autodesk Shader Software Development Kit utility functions.

  Utility functions for use in constructing shaders using the Autodesk
  Shader Software Development Kit.
*/

#ifndef ADSK_UTILITIES_H
#define ADSK_UTILITIES_H

#if defined __cplusplus

#ifndef ADSK_COLOR_H
#include "adskColor.h"
#endif

#ifndef ADSK_VECTOR_H
#include "adskVector.h"
#endif

#ifndef ADSK_RENDER_PASS_TYPES_H
#include "adskRenderPassTypes.h"
#endif

#ifndef ADSK_RENDER_PASS_UTILITIES_H
#include "adskRenderPassUtilities.h"
#endif

#ifndef ADSK_FRAME_BUFFER_STATE_H
#include "adskFrameBufferState.h"
#endif

#ifndef ADSK_CONSTANTS_H
#include "adskConstants.h"
#endif

#ifndef SHADER_H
#include <shader.h>
#endif

#ifndef ADSK_EXPORT_H
#include <adskExport.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

#if (defined(_WIN32))
#include <float.h>
/*!
  \brief Implementation of copysignf for Windows platforms.

  \tparam T The type to use.

  \param[in] x Argument to adjust sign of.

  \param[in] y Argument to take sign from.

  \return x with its sign changed to match y.
*/
template<typename T>
inline float copysignf(const T &x, const T &y) {
    return float(_copysign(double(x), double(y)));
}
#endif

/*!
  \brief Emit fatal error from shader.

  \param[in] pString The error message.
*/
ADSK_SHADERSDK_EXPORT void adskFatal(const string &pString);
/*!
  \brief Emit error from shader.

  \param[in] pString The error message.
*/
ADSK_SHADERSDK_EXPORT void adskError(const string &pString);
/*!
  \brief Emit fatal warning from shader.

  \param[in] pString The warning message.
*/
ADSK_SHADERSDK_EXPORT void adskWarning(const string &pString);
/*!
  \brief Emit information from shader.

  \param[in] pString The information message.
*/
ADSK_SHADERSDK_EXPORT void adskInfo(const string &pString);

/*!
  \brief Allocate and construct an object on the mental ray heap.

  \tparam T The type of object to construct.

  \return pointer to the new object
*/
template <class T>
T* adskNewMIObject()
{
    T* ptr = static_cast< T* >(mi_mem_allocate(sizeof(T)));
    new (static_cast<void*>( ptr )) T();
    return ptr;
}

/*!
  \brief Allocate and construct an object array on the mental ray heap.

  \tparam T The type of object array to construct.

  \param[in] itemCount number of objects in the array.

  \return pointer to the new object array
*/
template <class T>
T* adskNewMIArray(size_t itemCount)
{
    T* ptr = static_cast< T* >(mi_mem_allocate(sizeof(T)*itemCount));
    T* arrayItemPtr = ptr;
    for (size_t arrayItem = 0;
        arrayItem < itemCount;
        arrayItem++, arrayItemPtr++ )
    {
        new (static_cast<void*>( arrayItemPtr)) T();
    }
}

/*!
  \brief Destruct and deallocate an object on the mental ray heap.

  \tparam T The type of object to delete.

  \param[in] ptr reference to the object to be deleted.
*/
template <class T>
void adskDeleteMIObject(T* ptr)
{
    ptr->~T();
    mi_mem_release(static_cast<void*>( ptr ));
}

/*!
  \brief Destruct and deallocate an object array on the mental ray heap.

  \tparam T The type of object array to delete.

  \param[in] ptr reference to the object to be deleted.

  \param[in] itemCount number of objects in the array.
*/
template <class T>
void adskDeleteMIArray(T* ptr, size_t itemCount)  
{
    T* arrayItemPtr = ptr;
    for (size_t arrayItem = 0;
        arrayItem < itemCount;
        arrayItem++, arrayItemPtr++ )
    {
        arrayItemPtr->~T();
    }
    mi_mem_release(static_cast<void*>( ptr ));
}

// Macro to construct an object on the mi heap, using the non-default 
// constructor
#define adskNewMIObjectWithParams(PTR, CLASS, ... )                           \
{                                                                             \
    PTR = static_cast< CLASS * >(mi_mem_allocate(sizeof(CLASS)));             \
    new (static_cast<void*>( PTR )) CLASS(__VA_ARGS__);                       \
}

/*!
  \brief Obtain the numeric ID for a named frame buffer.

  \param[in] pState mental ray state

  \param[in] pBufferName The name of the buffer to look up.

  \return The ID of the named frame buffer.
*/
miUint getNamedFrameBufferID(const miState *pState, const char *pBufferName);

/*!
  \brief Obtain the numeric ID for a named frame buffer.

  \param[in] pState mental ray state

  \param[in] pBufferTag The tag for the named frame buffer.

  \return The ID of the named frame buffer.
*/
ADSK_SHADERSDK_EXPORT miUint getNamedFrameBufferID(const miState *pState, const miTag pBufferTag);

/*!
  \brief Scaling function used internally by operateOnFrameBuffer.

  This function ensures that proper rounding takes place when
  and only when dealing with miInteger frame buffer values.
  It also takes care of using the color luminance when scaling a 
  scalar using a color.

  \tparam T Type to scale.

  \tparam F Type to scale by.

  \param[in] value Value to scale.

  \param[in] scale Amount to scale by.

  \return value scaled by amount scale.
*/
template<typename T, typename F>
inline T applyScale(const T& value, const F& scale)
{
    return value*scale;  
}

/*!
  \brief Template specialization of applyScale for integers and scalars.

  \param[in] value Value to scale.

  \param[in] scale Amount to scale by.

  \return value scaled by amount scale.
*/
template<>
inline miInteger applyScale<miInteger, miScalar>(const miInteger& value, const miScalar& scale)
{
    miScalar result = value * scale;
    return static_cast<miInteger>(result + (result>=0.f)?0.5f:(-0.5f));  
}

/*!
  \brief Template specialization of applyScale for integers and colors.
         Should not be used.

  \param[in] value Value to scale.

  \param[in] scale Amount to scale by.

  \return value scaled by amount scale.
*/
template<>
inline miInteger applyScale<miInteger, miColor>(const miInteger& value, const miColor& scale)
{
    //This specialization should not be used, but it is required to build. no-op
    return value;  
}

/*!
  \brief Template specialization of applyScale for scalars and colors.

  \param[in] value Value to scale.

  \param[in] scale Amount to scale by.

  \return value scaled by amount scale.
*/
template<>
inline miScalar applyScale<miScalar, miColor>(const miScalar& value, const miColor& scale)
{
    return value*MAYA_LUMINANCE(scale);
}

/*!
  \brief Template specialization of applyScale for vectors and colors.

  \param[in] value Value to scale.

  \param[in] scale Amount to scale by.

  \return value scaled by amount scale.
*/
template<>
inline miVector applyScale<miVector, miColor>(const miVector& value, const miColor& scale)
{
    //Need to do explicit assignment rather than pointer casting magic
    //to ensure portability (alignment, endianness)
    miVector factor;
    factor.x = scale.r;
    factor.y = scale.g;
    factor.z = scale.b;
    return value*factor;
}

/*!
  \brief Perform the desired operation on a frame buffer.

  This function will retrieve the existing value in a frame buffer at
  the sample location in raster space, and will perform the desired
  operation with the given value, and write it back to the frame
  buffer.

  \param[in] pState mental ray state.

  \param[in] pValue The value to use in the operation.

  \param[in] pFrameBufferInfo The info structure on the frame buffer to operate on.

  \param[in] pFrameBufferWriteOperation The operation to be performed.

  \param[in] pFrameBufferWriteFlags The flags pertaining to the operation.

  \param[in] pFrameBufferWriteFactor The scaling factor to be used based on the flags.

  \param[in] pUseIrradiance Set to true if the value should be modulated by 
  irradiance. This option should only be used inside a light loop.

  \param[in] pIrradianceNoShadow Sample irradiance without shadows, used to compute 
  differential shadow passes.  When non-null, the difference between pIrradianceNoShadow
  and the sample irradiance is used as a lighting factor, instead of the sample irradiance.

  \return The result code from the write. \c miTRUE on success, \c
  miFALSE on error.
 */
template<typename T>
inline miBoolean operateOnFrameBuffer(const miState *pState,
                                      const T &pValue,
                                      FrameBufferInfo& pFrameBufferInfo,
                                      const miInteger &pFrameBufferWriteOperation,
                                      const miInteger &pFrameBufferWriteFlags,
                                      const miScalar &pFrameBufferWriteFactor,
                                      const bool &pUseIrradiance,
                                      const miColor* const& pIrradianceNoShadow = 0 )
{
    // we need this until mental images fixes their const-correctness
    miState *state = const_cast<miState*>(pState);

    int level = state->reflection_level+state->refraction_level;
    if ((pFrameBufferInfo.stack[level].flags & FB_ACC_FLAG_HIDDEN) ||
        (pState->type == miRAY_ENVIRONMENT)) 
    {
        // Note: Environment rays do not contribute directly
        return miFALSE;
    }

    T &curT = *((T*)(&pFrameBufferInfo.stack[level].currentValue));
    T valueT;

    // are we scaling the color?
    if (pFrameBufferWriteFlags & FB_WRITE_FLAG_SCALED)
    {
        valueT = applyScale(pValue, pFrameBufferWriteFactor);
    }
    else
    {
        valueT = pValue;
    }

    if (pUseIrradiance)
    {
        if (pIrradianceNoShadow)
        {
            valueT = applyScale(valueT, (*pIrradianceNoShadow) - pFrameBufferInfo.lightIrradiance);        
        }
        else
        {
            valueT = applyScale(valueT, pFrameBufferInfo.lightIrradiance);
        }
    }

    switch (pFrameBufferWriteOperation){
    case FB_WRITE_OVERWRITE:
        curT = valueT;
        break;
    case FB_WRITE_ADDITIVE:
        curT = curT + valueT;
        break;
    case FB_WRITE_MULTIPLICATIVE:
        curT = curT * valueT;
        break;
    default:
        // add by default
        curT = curT + valueT;
        break;
    }
    return miTRUE;
}

/*!
  \brief Accumulates a frame buffer value for the current light sample

  \tparam T The type to contribute to the frame buffer.

  \param[in] pState mental ray state.

  \param[in] pValue The value to accumulate.

  \param[in] pFrameBufferInfo The frame buffer info of the buffer to be written to.

  \param[in] pUseIrradiance Set to true if the value should be modulated by 
  irradiance. This option should only be used inside a light loop.

  \param[in] pIrradianceNoShadow Sample irradiance without shadows, used to compute 
  differential shadow passes.  When non-null, the difference between pIrradianceNoShadow
  and the sample irradiance is used as a lighting factor, instead of the sample irradiance.
*/
template<typename T>
inline miBoolean accumulateLightSample(const miState *pState,
                                       const T &pValue,
                                       FrameBufferInfo& pFrameBufferInfo,
                                       const bool &pUseIrradiance,
                                       const miColor* const& pIrradianceNoShadow = 0 )
{
    T &curT = *((T*)(&pFrameBufferInfo.lightSampleAccumulator));
    T valueT;

    if (pUseIrradiance)
    {
        if (pIrradianceNoShadow)
        {
            valueT = applyScale(pValue, (*pIrradianceNoShadow) - pFrameBufferInfo.lightIrradiance);        
        }
        else
        {
            valueT = applyScale(pValue, pFrameBufferInfo.lightIrradiance);
        }
    }
    else
    {
        valueT = pValue;
    }

    curT = curT + valueT;
    return miTRUE;
}

/*!
  \brief Operate on all frame buffers of a given material pass type.

  For all frame buffers of a given type, this function will perform
  the desired operation. If in light sampling mode (called between 
  lightSampleBegin and lightSampleEnd), the value will simply be
  accumulated in a temporary location and the actual operation will
  be performed by lightSampleEnd.

  \tparam T The type to contribute to the frame buffer.

  \param[in] pState mental ray state.

  \param[in] pValue The value to add.

  \param[in] pFrameBufferInfo The array of frame buffer info structures.

  \param[in] pPassTypeInfo The array pass type info structures.

  \param[in] pTypeID Only frame buffers of this type will be written
  to.

  \param[in] pFrameBufferWriteOperation The operation to be performed.

  \param[in] pFrameBufferWriteFlags The flags pertaining to the operation.

  \param[in] pFrameBufferWriteFactor The scaling factor to be used based on the flags.

  \param[in] pUseIrradiance Set to true if the value should be modulated by 
  irradiance. This option should only be used inside a light loop.

  \param[in] pIrradianceNoShadow Sample irradiance without shadows, used to compute 
  differential shadow passes.  When non-null, the difference between pIrradianceNoShadow
  and the sample irradiance is used as a lighting factor, instead of the sample irradiance.
*/

template<typename T>
inline void operateOnFrameBuffersOfType(const miState *pState,
                                        const T &pValue,
                                        FrameBufferInfo* const pFrameBufferInfo,
                                        PassTypeInfo* const pPassTypeInfo,
                                        const PassTypeID &pTypeID,
                                        const miInteger &pFrameBufferWriteOperation,
                                        const miInteger &pFrameBufferWriteFlags,
                                        const miScalar &pFrameBufferWriteFactor,
                                        const bool &pUseIrradiance,
                                        const miColor* const& pIrradianceNoShadow = 0 ){
    if (!pFrameBufferInfo || !pPassTypeInfo || pPassTypeInfo[pTypeID].count == 0) return;

    miInteger i;
    miUint pass;
    if ( pFrameBufferInfo[0].flags & FB_FLAG_SAMPLING_LIGHT )
    {
        for (i = 0, pass = pPassTypeInfo[pTypeID].start;
             i < pPassTypeInfo[pTypeID].count;
             ++i, ++pass){
            accumulateLightSample(pState,
                                  pValue,
                                  pFrameBufferInfo[pass],
                                  pUseIrradiance,
                                  pIrradianceNoShadow);
        }    
    }
    else
    {
        for (i = 0, pass = pPassTypeInfo[pTypeID].start;
             i < pPassTypeInfo[pTypeID].count;
             ++i, ++pass){
            operateOnFrameBuffer(pState,
                                 pValue,
                                 pFrameBufferInfo[pass],
                                 pFrameBufferWriteOperation,
                                 pFrameBufferWriteFlags,
                                 pFrameBufferWriteFactor,
                                 pUseIrradiance,
                                 pIrradianceNoShadow);
        }
    }
}

/*!
  \brief Operate on material normal frame buffers

  For all material normal frame buffers, this function will perform
  the desired operation.

  \param[in] pState mental ray state.

  \param[in] pValue The value to add.

  \param[in] pFrameBufferInfo The array of frame buffer info structures.

  \param[in] pPassTypeInfo The array pass type info structures.

  \param[in] pFrameBufferWriteOperation The operation to be performed.

  \param[in] pFrameBufferWriteFlags The flags pertaining to the operation.

  \param[in] pFrameBufferWriteFactor The scaling factor to be used based on the flags.
 */

inline void operateOnNormalMaterialFrameBuffersOfType(const miState *pState,
                                                      miVector pValue,
                                                      FrameBufferInfo* const pFrameBufferInfo,
                                                      PassTypeInfo* const pPassTypeInfo,
                                                      const miInteger &pFrameBufferWriteOperation,
                                                      const miInteger &pFrameBufferWriteFlags,
                                                      const miScalar &pFrameBufferWriteFactor)
{
    if (!pFrameBufferInfo || !pPassTypeInfo) return;

    PassTypeInfo* passTypeInfo;
    FrameBufferInfo* frameBufferInfo;
    getFrameBufferInfo(pState, passTypeInfo, frameBufferInfo);

    miInteger i;
    miUint pass;
    for (i = 0, pass = pPassTypeInfo[NORMAL].start;
         i < pPassTypeInfo[NORMAL].count;
         ++i, ++pass){

        // get the parameter associated with this normal material pass

        miInteger lNormalMode = frameBufferInfo[pass].integerUserParameter1;
        switch (lNormalMode){
        case 0:                 // world
            mi_normal_to_world(pState, &pValue, &pValue);
            break;
        case 1:                 // camera
            mi_normal_to_camera(pState, &pValue, &pValue);
            break;
        case 2:                 // object
            mi_normal_to_object(pState, &pValue, &pValue);
            break;
        default:                // use world as the default
            mi_normal_to_world(pState, &pValue, &pValue);
            break;
        }

        operateOnFrameBuffer(pState,
                             pValue,
                             pFrameBufferInfo[pass],
                             pFrameBufferWriteOperation,
                             pFrameBufferWriteFlags,
                             pFrameBufferWriteFactor,
                             false);
    }
}

/*!
  \brief Clamp value to range

  \tparam T Type of value to clamp.

  \param[in] x Value to clamp.
  
  \param[in] a Minimum value for clamp.

  \param[in] b Minimum value for clamp.

  \return x clamped to range [a,b].
*/
template<typename T>
inline T MAYA_CLAMP(const T &x, const T &a, const T &b)
{
    return (x < a ? a : x > b ? b : x);
}


/*!
  \brief Find minimum value.

  \tparam T Type of value to find minimum.

  \param[in] x First value.
  
  \param[in] y Second value.

  \return Minimum of x and y.
*/
template<typename T>
inline T MAYA_MIN(const T &x, const T &y)
{
    return x < y ? x : y;
}

/*!
  \brief Find maximum value.

  \tparam T Type of value to find minimum.

  \param[in] x First value.
  
  \param[in] y Second value.

  \return Maximum of x and y.
*/
template<typename T>
inline T MAYA_MAX(const T &x, const T &y)
{
    return x > y ? x : y;
}

/*!
  \brief Is value effectively zero.

  \param[in] a Value.
  
  \return True if the value is within MAYA_EPS of zero.
*/
inline bool MAYA_ISZERO(const miScalar a)
{
    return (fabsf(a) < MAYA_EPS);
}

/*!
  \brief Computer linear interpolation.

  \tparam T Type to perform computation with.

  \param[in] t Split parameter.

  \param[in] a Start value.

  \param[in] b End value.

  \return Linearly interpolated value.
*/
template<typename T>
inline T lerp(const T &t, const T &a, const T &b)
{
    return a + t * (b - a);
}

/*!
  \brief Computer linear ramp.

  \tparam T Type to perform computation with.

  \param[in] a a value.

  \param[in] b b value.

  \param[in] x x value.

  \return Linear ramp value.
*/
template<typename T>
inline T linearRamp(const T &a, const T &b, const T &x)
{
    return (x - a) / (b - a);
}

/*!
  \brief Remap value to new range.

  \tparam T Type to perform computation with.

  \param[in] pValue Value to remap.

  \param[in] pOldMinimum Old minimum value.

  \param[in] pOldMaximum Old maximum value.

  \param[in] pNewMinimum New minimum value.

  \param[in] pNewMaximum New maximum value.

  \return The remapped value.
*/
template<typename T>
inline T remap(const T &pValue, const T &pOldMinimum, const T &pOldMaximum, const T &pNewMinimum, const T &pNewMaximum)
{
    return pNewMinimum + ((pValue - pOldMinimum) / (pOldMaximum - pOldMinimum)) * (pNewMaximum - pNewMinimum);
}

/*!
  \brief Remap value to new range and clamp to that range.

  \tparam T Type to perform computation with.

  \param[in] pValue Value to remap.

  \param[in] pOldMinimum Old minimum value.

  \param[in] pOldMaximum Old maximum value.

  \param[in] pNewMinimum New minimum value.

  \param[in] pNewMaximum New maximum value.

  \return The remapped, clamped value.
*/
template<typename T>
inline T clampedRemap(const T &pValue, const T &pOldMinimum, const T &pOldMaximum, const T &pNewMinimum, const T &pNewMaximum)
{
    return MAYA_CLAMP(remap(pValue, pOldMinimum, pOldMaximum, pNewMinimum, pNewMaximum),
                      pNewMinimum,
                      pNewMaximum);
}

/*!
  \brief Convert pixel aspect ratio.

  \param[in,out] pState Pointer to mental ray state.

  \param[out] vec Result vector.
*/
inline void convertToNormalizedPixels(const miState *pState, miVector &vec){
    // get the current pixel aspect ratio
    miScalar pixelAspectRatio = 1.f;
    if (pState->camera){
        pixelAspectRatio = pState->camera->aspect / 
            (miScalar(pState->camera->x_resolution) / miScalar(pState->camera->y_resolution));
    }
    // multiply the x component by that ratio
    vec.x *= pixelAspectRatio;
    // zero out the z component
    vec.z = 0.f;
}

/*!
  \brief Prepare the frame buffer states for a series
  of reflection and/or refraction trace recursions

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pState shading state
*/
ADSK_SHADERSDK_EXPORT void tracePassInit(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    miState*         pState
    );

/*!
  \brief Composite the frame buffer states after a series
  of reflection and/or refraction trace recursions

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pState shading state
  \param[in] pFactor the light transport factor
  \param[in] pIsRefraction must be set to true if the the traced rays were refraction rays.
*/
ADSK_SHADERSDK_EXPORT void tracePassAdd(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    miState*         pState,
    miColor          pFactor,
    bool             pIsRefraction
    );

/*!
  \brief Trace a shadow ray using per frame-buffer lighting
  Note: should only be called from a light shader

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[out] pFilter attenuation factor cause by shadows
  \param[in] pLightColor unattenuated irradiance
  \param[in] pShadowColor Shadow Color
  \param[in] pUsingShadowMap must be set to true if shadow maps are used
  \param[in] pState shading state

  \return false if full occlusion is detected
*/
ADSK_SHADERSDK_EXPORT bool traceShadow(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    miColor&         pFilter, 
    const miColor&   pLightColor, 
    const miColor&   pShadowColor, 
    bool             pUsingShadowMap,
    miState*         pState
    );

/*!
  \brief When not rendering with shadows, this function is called to set
  the irradiance value for the current light
  Note: should only be called from a light shader

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pLightColor unattenuated irradiance
*/
ADSK_SHADERSDK_EXPORT void setLightIrradiance(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    const miColor&   pLightColor );

/*!
  \brief Initialize frame buffer states for shadow area sampling, used
  for area lights, final gathering, etc.
  Note: should only be called from a light shader when not using a shadow map

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
*/
ADSK_SHADERSDK_EXPORT void traceShadowAccumulateBegin(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo);

/*!
  \brief Trace a shadow ray and accumulate results for per frame-buffer lighting
  Note: should only be called from a light shader, between calls to 
  traceShadowAccumulateBegin and traceShadowAccumulateEnd

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[out] pFilter attenuation factor cause by shadows
  \param[in] pState shading state
*/
ADSK_SHADERSDK_EXPORT bool traceShadowAccumulate(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    miColor&         pFilter, 
    miState*         pState);

/*!
  \brief Process accumulated shadow rays for light sampling
  Note: should only be called from a light shader when not using a shadow map

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pNumberOfRays the number of rays cast during the accumulation process
  \param[in] pLightColor unattenuated irradiance
  \param[in] pShadowColor Shadow Color
  \param[in] pState shading state
*/
ADSK_SHADERSDK_EXPORT void traceShadowAccumulateEnd(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    unsigned int     pNumberOfRays,
    const miColor&   pLightColor, 
    const miColor&   pShadowColor, 
    miState*         pState);

/*!
  \brief Function to be called before all light sampling loops.  Takes care
  of initializing light sample accumulators

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
*/
ADSK_SHADERSDK_EXPORT void sampleLightBegin(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo);

/*!
  \brief Function to be called after all light sampling loops.  Takes care
  of combining sample values into the material frame buffer values.

  \param[in] pState the shading state
  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pSamples The number of times the current light was sampled
  \param[in] pFrameBufferWriteOperation The operation to be performed.
  \param[in] pFrameBufferWriteFlags The flags pertaining to the operation.
  \param[in] pFrameBufferWriteFactor The scaling factor to be used based on the flags.
*/
ADSK_SHADERSDK_EXPORT void sampleLightEnd(
    miState*         pState,
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    const int        pSamples,
    const miInteger &pFrameBufferWriteOperation,
    const miInteger &pFrameBufferWriteFlags,
    const miScalar  &pFrameBufferWriteFactor);

/*!
  \brief Initializes the frame buffer states for receiving
  illumination information
  Note: should be called at the beginning of a light shader

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pState the shading state
*/
ADSK_SHADERSDK_EXPORT void setupLightContributions(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    miState*         pState);

/*!
  \brief Applies the shadow opacity of the current object to all 
  relevant frame buffer states.
  Note: should only be called from shadow shaders

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pTransparency The shadow transparency of the current material
  \param[in] pState the shading state

  \return returns true if the light path is not completely opaque for at 
  least one frame buffer for which shadows are computed.
*/
ADSK_SHADERSDK_EXPORT miBoolean applyShadowTransparencyToFrameBuffers(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    const miColor&   pTransparency,
    miState*         pState);

/*!
  \brief This function should be called at the beginning of light
  sample loops in material shaders.  It enables renderpass contributions 
  for lightshaders that were not developped using the AdskShaderSDK.
  Whenever such light shaders are used, pass contributions will
  continue to work for controlling light contributions, but
  not for controlling shadow casters.  Only SDK-compliant light
  shaders support per-pass independent shadow casting.

  \param[in] pNumberOfFrameBuffers the number of frame buffers in the state
  \param[in,out] pFrameBufferInfo the array of frame buffer info structures
  \param[in] pLightColor The light color used for the Master Beauty pass
  \param[in] pLightInstance The light instance currently being evaluated
  \param[in] pState the shading state
*/
ADSK_SHADERSDK_EXPORT void handleNonAdskLights(
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    const miColor&   pLightColor,
    miTag            pLightInstance,
    miState*         pState);

// Auxiliary functions for surface shaders.

/*!
  \brief Convert HSV color to RGB.

  \param[in] hsv The HSV color.
  \param[out] rgb The result RGB color.
*/
ADSK_SHADERSDK_EXPORT void hsv_to_rgb(
    const miColor *hsv,
    miColor       *rgb);

/*!
  \brief Convert RGB color to HSV.

  \param[in] rgb The RGB color.
  \param[out] hsv The result HSV color.
*/
ADSK_SHADERSDK_EXPORT void rgb_to_hsv(
    const miColor *rgb,
    miColor       *hsv);

/*!
  \brief Retrieve derivatives at point.

  \param[in,out] state Pointer to the mental ray state.
  \param[in] u u-coordinate for derivative.
  \param[in] v v-coordinate for derivative.
  \param[in] space Space to compute derivatives in.
  \param[in] tangentSet Tangent set to retrieve derivatives for.
*/
ADSK_SHADERSDK_EXPORT void get_derivs(
    miState         *state,
    miVector        *u,
    miVector        *v,
    int             space,
    int             tangentSet);

/*!
  \brief Compute the reflection at the current point.

  \param[out] resRefr Refraction result
  \param[out] resTrsp Transparency result
  \param[in] pRefractionLimit Refraction limit
  \param[in] pRefractiveIndex Refractive index
  \param[in] refractions refractions
  \param[in] transparency transparency
  \param[in] hideSource Hide source
  \param[in] pRefractionBlur Refraction blur
  \param[in] pRefractionBlurLimit Refraction blur limit
  \param[in] pRefractionRays Refraction rays
  \param[in] pSurfaceThickness Surface thickness
  \param[in] pTransparencyDepth Transparency depth
  \param[in] pLightAbsorbance Light absorbance
  \param[in] pChromaticAberration Chromatic aberration
  \param[in] normal normal
  \param[in] dot_nd Dot product of normal and direction
  \param[in,out] state Pointer to mental ray state
  \param[in] pNumberOfFrameBuffers Number of frame buffers
  \param[in] pFrameBufferInfo Frame buffer information
  \param[in] pPassTypeInfo Pass type information
  \param[in] pFrameBufferScale Frame buffer scale
*/
ADSK_SHADERSDK_EXPORT void compute_refraction(
    miColor          *resRefr,
    miColor          *resTrsp,
    miInteger        *pRefractionLimit,
    miScalar         *pRefractiveIndex,
    miBoolean        refractions,
    const miColor    *transparency,
    miBoolean        hideSource,
    miScalar         *pRefractionBlur,
    miInteger        *pRefractionBlurLimit,
    miInteger        *pRefractionRays,
    miScalar         *pSurfaceThickness,
    miScalar         *pTransparencyDepth,
    miScalar         *pLightAbsorbance,
    miBoolean        *pChromaticAberration,
    miVector         *normal,
    float            dot_nd,
    miState          *state,
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    PassTypeInfo*    pPassTypeInfo,
    const miScalar&  pFrameBufferScale);

/*!
  \brief Compute the reflection at the current point.

  \param[out] resRefl Reflection result
  \param[in] reflectivity Reflectivity of material
  \param[in] specularColor Specular color
  \param[in] glowIntensity Glow intensity
  \param[in] pReflectedColor Reflected color
  \param[in] pReflectionLimit Reflection limit
  \param[in] pReflectionBlur Reflection blur
  \param[in] pReflectionBlurLimit Reflection blur limit
  \param[in] pReflectionRays Reflection rays
  \param[in] hideSource Hide source
  \param[in] normal normal
  \param[in] dot_nd Dot product of normal and direction
  \param[in,out] state Pointer to mental ray state
  \param[in] pNumberOfFrameBuffers Number of frame buffers
  \param[in] pFrameBufferInfo Frame buffer information
  \param[in] pPassTypeInfo The array pass type info structures.
  \param[in] pFrameBufferScale Frame buffer scale
*/
ADSK_SHADERSDK_EXPORT void compute_reflection(
    miColor          *resRefl,
    miScalar         reflectivity,
    const miColor    *specularColor,
    miScalar         glowIntensity,
    miColor          *pReflectedColor,
    miInteger        *pReflectionLimit,
    miScalar         *pReflectionBlur,
    miInteger        *pReflectionBlurLimit,
    miInteger        *pReflectionRays,
    miBoolean        hideSource,
    miVector         *normal,
    float            dot_nd,
    miState          *state,
    unsigned int     pNumberOfFrameBuffers,
    FrameBufferInfo* pFrameBufferInfo,
    PassTypeInfo*    pPassTypeInfo,
    const miScalar&  pFrameBufferScale);

/*!
  \brief Compute irradiance for material.

  \param[out] resIrrad Irradiance result
  \param[in] pIrradianceColor Irradiance color
  \param[in] diffuse Diffuse factor
  \param[in] color Diffuse color
  \param[in] transparency Transparency
  \param[in] glowIntensity Glow intensity
  \param[in] pIrradiance Irradiance
  \param[in,out] state Pointer to mental ray state
*/
ADSK_SHADERSDK_EXPORT void compute_irradiance(
    miColor        *resIrrad,
    miColor        *pIrradianceColor,
    float          diffuse,
    const miColor  *color,
    const miColor  *transparency,
    miScalar       glowIntensity,
    miColor        *pIrradiance,
    miState        *state);

/*!
  \brief Compute lambertian translucence.

  \param[in,out] state Pointer to mental ray state
  \param[in] cos_nl Dot product of normal and light
  \param[in] ldir Light direction
  \param[in] translucence translucence
  \param[in] translucenceFocus Translucence focus
  \param[in] translucenceDepth Translucence depth
  \param[in] blindData Light data

  \return Lambertian translucence value.
*/
ADSK_SHADERSDK_EXPORT float compute_lambert_translucence(
    miState     *state,
    float       cos_nl,
    miVector    *ldir,
    miScalar    translucence,
    miScalar    translucenceFocus,
    miScalar    translucenceDepth,
    void        *blindData);

/*!
  \brief Compute phong specular value.

  \param[in] ldir Light direction
  \param[in] cosinePower Cosine power
  \param[in] reflectionSpecularity Reflection specularity
  \param[in] reflDirection Reflection direction
  \param[in,out] state Pointer to mental ray state

  \return Phong specular value
*/
ADSK_SHADERSDK_EXPORT float compute_phong_specular(
    miVector    *ldir,
    miScalar    cosinePower,
    miScalar    reflectionSpecularity,
    miVector    *reflDirection,
    miState     *state);

/*!
  \brief Compute blinn specular value.

  \param[in] cos_nl Dot product of normal and light
  \param[in] cos_nv Dot product of normal and direction
  \param[in] ldir Light direction
  \param[in] eccentricity Eccentricity
  \param[in] specularRollOff Specular rolloff
  \param[in] reflectionSpecularity Reflection specularity
  \param[in] normal normal
  \param[in] state Pointer to mental ray state

  \return The Blinn specular value.
*/
ADSK_SHADERSDK_EXPORT float compute_blinn_specular(
    float       cos_nl,
    float       cos_nv,
    miVector    *ldir,
    miScalar    eccentricity,
    miScalar    specularRollOff,
    miScalar    reflectionSpecularity,
    miVector    *normal,
    miState     *state);

/*!
  \brief Compute specular for hair tube shader

  \param[in] specularPower Specular power
  \param[in] lightDir Light direction
  \param[in] viewDir View direction
  \param[in] tubeDir Tube direction

  \return The hair tube shader specular value.
*/
ADSK_SHADERSDK_EXPORT float compute_hairtubeshader_specular (
    miScalar    specularPower,
    const miVector    *lightDir,
    const miVector    *viewDir,
    const miVector    *tubeDir);

/*!
  \brief Compute area light lambertian reflection

  \param[in] point The point to compute at.
  \param[in] normal The normal
  \param[in] blindData Custom light data

  \return The area light lambertian reflection
*/
ADSK_SHADERSDK_EXPORT float arealight_lambertian_reflect(
    const miVector    *point,
    const miVector    *normal,
    const void        *blindData);

/*!
  \brief Compute area light maximum phong specular direction

  \param[in] point The point to compute at.
  \param[in] direction The direction
  \param[in] blindData Custom light data
  \param[in] lightInst The light instance
  \param[out] result The direction result
*/
ADSK_SHADERSDK_EXPORT void arealight_max_phong_spec_dir(
    const miVector    *point,
    const miVector    *direction,
    const void        *blindData,
    miTag             lightInst,
    miVector          *result);

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus
#endif // ADSK_UTILITIES_H

