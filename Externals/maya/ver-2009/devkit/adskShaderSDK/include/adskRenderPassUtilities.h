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
  \brief Utility functions for use with render passes
*/

#ifndef ADSK_RENDER_PASS_UTILITIES_H
#define ADSK_RENDER_PASS_UTILITIES_H

#ifndef ADSK_EXPORT_H
#include <adskExport.h>
#endif

#include <string>

using std::string;

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

/*!
  \brief Determine whether an object or a light contributes to a given pass.

  This function is used to evaluate whether a specific pass receives
  a shading contribution from the current object.

  \param[in] pPassIndex The index of the pass to query.

  \param[in] pContributionMap The encoding string to be queried.

  \return True if the light/object is enabled, false otherwise.
 */
ADSK_SHADERSDK_EXPORT bool contributesToPass(const int pPassIndex,
                                             const char* pContributionMap);


// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // ADSK_RENDER_PASS_UTILITIES_H
