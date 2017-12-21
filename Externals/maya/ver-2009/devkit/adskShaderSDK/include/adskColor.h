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
  
  \brief Color manipulation functions
*/

#ifndef ADSK_COLOR_H
#define ADSK_COLOR_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

#ifndef ADSK_CONSTANTS_H
#include "adskConstants.h"
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

/*!
  \brief Check whether a given color is black.

  This function will check that the RGB components of the given color
  are less than a given epsilon (\c MAYA_EPS defined in \c
  adskConstants.h).

  \param[in] c The color to check.
  \return Whether the color can be considered to be black.
*/
inline bool MAYA_ISBLACK(const miColor &c){
    return (c.r < MAYA_EPS && c.g < MAYA_EPS && c.b < MAYA_EPS);
}

/*!
  \brief Calculate the luminance of the given RGB color.

  The luminance is a weighted sum of the response of the color
  channels which weighs green, red, and blue in decreasing
  amounts. This is to model human visual sensitivity.

  \param[in] c The given color.

  \return The luminance.
*/
inline miScalar MAYA_LUMINANCE(const miColor &c){
    return 
        c.r * MAYA_LUMINANCE_RED +
        c.g * MAYA_LUMINANCE_GREEN +
        c.b * MAYA_LUMINANCE_BLUE;
}


/*!
  \brief Calculate the intensity of the given RGB color.

  The intensity is calculated as the average of the RGB components.

  \param[in] c The given color.

  \return The intensity.
*/
inline miScalar MAYA_INTENSITY(const miColor &c){
    return (c.r + c.g + c.b) / 3.f;
}

/*!
  \brief Multiplies a color by a scalar.

  The alpha channel is also multiplied by the scalar.

  \param[in] lhs The color to be multiplied.
  \param[in] rhs The scalar to multiply by.
  
  \return The multiplied color.
*/
inline miColor operator*(const miColor &lhs, const miScalar &rhs){
    miColor result;
    result.r = lhs.r * rhs; // red
    result.g = lhs.g * rhs; // green
    result.b = lhs.b * rhs; // blue
    result.a = lhs.a * rhs; // alpha
    return result;
}

/*!
  \brief Multiplies a color by a scalar.

  The alpha channel is also multiplied by the scalar.

  \param[in] lhs The scalar to multiply by.
  \param[in] rhs The color to be multiplied.
  
  \return The multiplied color.
*/
inline miColor operator*(const miScalar &lhs, const miColor &rhs){
    miColor result;
    result.r = lhs * rhs.r; // red
    result.g = lhs * rhs.g; // green
    result.b = lhs * rhs.b; // blue
    result.a = lhs * rhs.a; // alpha
    return result;
}

/*!
  \brief Multiplies a color by a color.

  This returns a new color whose channels are the products of the
  respective channels of the operands (including the alpha component).

  \param[in] lhs The color to be multiplied.
  \param[in] rhs The other color to be multiplied.
  
  \return The multiplied color.
*/
inline miColor operator*(const miColor &lhs, const miColor &rhs){
    miColor result;
    result.r = lhs.r * rhs.r; // red
    result.g = lhs.g * rhs.g; // green
    result.b = lhs.b * rhs.b; // blue
    result.a = lhs.a * rhs.a; // alpha
    return result;
}

/*!
  \brief Divide a color by a scalar.

  This returns a color whose components have each been divided by a
  scalar (including the alpha component).

  \param[in] lhs The color to be divided.
  \param[in] rhs The divisor.

  \return The divided color.
*/
inline miColor operator/(const miColor &lhs, const miScalar &rhs){
    miScalar inverse = 1.f / rhs; // calculate the inverse
    return lhs * inverse;       // and multiply by it
}

/*!
  \brief Divide a color by an integer.

  This returns a color whose components have each been divided by an
  integer (including the alpha component).

  \param[in] lhs The color to be divided.
  \param[in] rhs The divisor.

  \return The divided color.
*/
inline miColor operator/(const miColor &lhs, const int &rhs){
    miScalar inverse = 1.f / rhs; // calculate the inverse
    return lhs * inverse;       // and multiply by it
}

/*!
  \brief Add two colors together.

  This returns a color representing the sum of the two operands. The
  alpha channel is also added.

  \param[in] lhs One of the colors to be added.
  \param[in] rhs The other color to be added.

  \return The added color.
*/
inline miColor operator+(const miColor &lhs, const miColor &rhs){
    miColor result;
    result.r = lhs.r + rhs.r; // red
    result.g = lhs.g + rhs.g; // green
    result.b = lhs.b + rhs.b; // blue
    result.a = lhs.a + rhs.a; // alpha
    return result;
}

/*!
  \brief Subtract two colors.

  This returns a color representing the difference of the two
  operands. The alpha channel is also included.

  \param[in] lhs The color to be subtracted from.
  \param[in] rhs The color to subtract.

  \result The color difference.
*/
inline miColor operator-(const miColor &lhs, const miColor &rhs){
    miColor result;
    result.r = lhs.r - rhs.r; // red
    result.g = lhs.g - rhs.g; // green
    result.b = lhs.b - rhs.b; // blue
    result.a = lhs.a - rhs.a; // alpha
    return result;
}

/*!
  \brief Return a color which is fully opaque.

  This function converts a color to a fully opaque color, meaning that
  it sets the alpha channel to 1.

  \param[in] color The color to be made opaque.

  \return The opaque color.
*/
inline miColor opaqueColor(const miColor &color){
    miColor result;
    result.r = color.r;
    result.g = color.g;
    result.b = color.b;
    result.a = 1.f;
    return result;
}

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif  // __cplusplus
#endif  // ADSK_COLOR_H

