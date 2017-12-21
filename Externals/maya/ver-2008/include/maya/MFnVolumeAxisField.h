
#ifndef _MFnVolumeAxisField
#define _MFnVolumeAxisField
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MFnVolumeAxisField
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnVolumeAxisField)
//
// Function set for VolumeAxis Fields
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnField.h>
#include <maya/MVector.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MFnVolumeAxisField)

/// Function set for VolumeAxis Fields (OpenMayaFX) (OpenMayaFX.py)
/**

*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAFX_EXPORT MFnVolumeAxisField : public MFnField
{

    declareDagMFn(MFnVolumeAxisField, MFnField);

public:
    ///
    bool         invertAttenuation  ( MStatus *ReturnStatus = NULL ) const;
    ///
    MVector      direction          ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       speedAlongAxis     ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       speedAroundAxis    ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       speedAwayFromAxis  ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       speedAwayFromCenter( MStatus *ReturnStatus = NULL ) const;
    ///
    double       directionalSpeed   ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       turbulence         ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       turbulenceSpeed    ( MStatus *ReturnStatus = NULL ) const;
    ///
    MVector      turbulenceFrequency ( MStatus *ReturnStatus = NULL ) const;
    ///
    MVector      turbulenceOffset   ( MStatus *ReturnStatus = NULL ) const;
    ///
    double       detailTurbulence   ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setInvertAttenuation  ( bool enable );
    ///
    MStatus      setDirection       ( const MVector & direction );
    ///
    MStatus      setSpeedAlongAxis  ( double value );
    ///
    MStatus      setSpeedAroundAxis  ( double value );
    ///
    MStatus      setSpeedAwayFromAxis  ( double value );
    ///
    MStatus      setSpeedAwayFromCenter  ( double value );
    ///
    MStatus      setDirectionalSpeed ( double value );
    ///
    MStatus      setTurbulence       ( double value );
    ///
    MStatus      setTurbulenceSpeed  ( double value );
    ///
    MStatus      setTurbulenceFrequency ( const MVector &value );
    ///
    MStatus      setTurbulenceOffset ( const MVector &value );
    ///
    MStatus      detailTurbulence    ( double value );

BEGIN_NO_SCRIPT_SUPPORT:

 	declareDagMFnConstConstructor( MFnVolumeAxisField, MFnField );
	
END_NO_SCRIPT_SUPPORT:

protected:
// No protected members
private:
// No private members

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFnVolumeAxisField */
