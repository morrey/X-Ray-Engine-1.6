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
  \brief Scatter functions
*/

#ifndef ADSK_SCATTER_H
#define ADSK_SCATTER_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

#ifndef ADSK_EXPORT_H
#include <adskExport.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

/*!
  \brief Compute the scatter for a given intersection.

  \param[out] resScatter The resulting scatter color.
  \param[in] pScatterColor The given scatter color.
  \param[in] pScatterRadius The scatter radius.
  \param[in] pScatterAccuracy The scatter accuracy.
  \param[in] pScatterFalloff The scatter falloff.
  \param[in] pScatterLimit The scatter limit.
  \param[in] pScatterCache The scatter cache.
  \param[in] pDiffuse The diffuse reflectivity of the material.
  \param[in] pColor The color of the material.
  \param[in] pTranslucence The translucence of the material.
  \param[in] pTranslucenceFocus The translucence focus.
  \param[in] pTranslucenceDepth The translucence depth.
  \param[in] pNormalCamera The material normal in camera space.
  \param[in] pIrradiance The incoming irradiance.
  \param[in] pIrradianceColor The incoming irradiance color.
  \param[in] state mental ray state
  \param[in,out] scatterData The computed scatter data.
 */
ADSK_SHADERSDK_EXPORT void compute_scatter(
    miColor     *resScatter,
    miColor     *pScatterColor,
    miScalar    *pScatterRadius,
    miInteger   *pScatterAccuracy,
    miInteger   *pScatterFalloff,
    miInteger   *pScatterLimit,
    miInteger   *pScatterCache,
    miScalar    *pDiffuse,
    miColor     *pColor,
    miScalar    *pTranslucence,
    miScalar    *pTranslucenceFocus,
    miScalar    *pTranslucenceDepth,
    miVector    *pNormalCamera,
    miColor     *pIrradiance,
    miColor     *pIrradianceColor,
    miState     *state,
    void        **scatterData);

/*!
  \brief Destroy scatter data.

  \param[in] state mental ray state
  \param[in,out] scatterData The scatter data to destroy.
 */
ADSK_SHADERSDK_EXPORT void destroy_scatter(
    miState     *state,
    void        **scatterData);

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif  // __cplusplus
#endif // ADSK_SCATTER_H
