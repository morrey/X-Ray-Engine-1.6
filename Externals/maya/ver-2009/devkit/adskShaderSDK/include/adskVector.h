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
  
  \brief Vector manipulation functions
*/

#ifndef ADSK_VECTOR_H
#define ADSK_VECTOR_H

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
  \brief Determine if vector is NULL vector

  \param[in] v Vector to test.

  \return True if all components of the vector are with MAYA_EPS of zero.
*/
inline bool MAYA_ISVECTORNULL(const miVector &v)
{
    return (v.x < MAYA_EPS && v.y < MAYA_EPS && v.z < MAYA_EPS);
}

/*!
  \brief Multiplies a vector by a scalar.

  \param[in] lhs The vector to be multiplied.
  \param[in] rhs The scalar to multiply by.
  
  \return The multiplied vector.
 */
inline miVector operator*(const miVector &lhs, const miScalar &rhs){
    miVector result;
    result.x = lhs.x * rhs;
    result.y = lhs.y * rhs;
    result.z = lhs.z * rhs;
    return result;
}

/*!
  \brief Multiplies a vector by a scalar.

  \param[in] lhs The scalar to multiply by.
  \param[in] rhs The vector to be multiplied.
  
  \return The multiplied vector.
 */
inline miVector operator*(const miScalar &lhs, const miVector &rhs){
    miVector result;
    result.x = lhs * rhs.x;
    result.y = lhs * rhs.y;
    result.z = lhs * rhs.z;
    return result;
}


/*!
  \brief Multiplies a vector by a vector (component by component).

  This returns a new vector whose components are the products of the
  respective components of the operands.

  \param[in] lhs The vector to be multiplied.
  \param[in] rhs The other vector to be multiplied.
  
  \return The multiplied vector.
 */
inline miVector operator*(const miVector &lhs, const miVector &rhs){
    miVector result;
    result.x = lhs.x * rhs.x;
    result.y = lhs.y * rhs.y;
    result.z = lhs.z * rhs.z;
    return result;
}

/*!
  \brief Divide a vector by a scalar.

  This returns a vector whose components have each been divided by a
  scalar.

  \param[in] lhs The vector to be divided.
  \param[in] rhs The divisor.

  \return The divided vector.
 */
inline miVector operator/(const miVector &lhs, const miScalar &rhs){
    miScalar inverse = 1.f / rhs; // calculate the inverse
    return lhs * inverse;       // and multiply by it
}

/*!
  \brief Divide a vector by an integer.

  This returns a vector whose components have each been divided by an
  integer.

  \param[in] lhs The vector to be divided.
  \param[in] rhs The divisor.

  \return The divided vector.
 */
inline miVector operator/(const miVector &lhs, const int &rhs){
    miScalar inverse = 1.f / rhs; // calculate the inverse
    return lhs * inverse;       // and multiply by it
}

/*!
  \brief Add two vectors together.

  This returns a vector representing the sum of the two operands.

  \param[in] lhs One of the vectors to be added.
  \param[in] rhs The other vector to be added.

  \return The added vector.
 */
inline miVector operator+(const miVector &lhs, const miVector &rhs){
    miVector result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

/*!
  \brief Subtract two vectors.

  This returns a vector representing the difference of the two
  operands.

  \param[in] lhs The vector to be subtracted from.
  \param[in] rhs The vector to subtract.

  \result The vector difference.
 */
inline miVector operator-(const miVector &lhs, const miVector &rhs){
    miVector result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif  // __cplusplus
#endif  // ADSK_COLOR_H

