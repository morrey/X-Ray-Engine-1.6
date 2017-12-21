
#ifndef _MAngle
#define _MAngle
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
// CLASS:    MAngle
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MAngle)
//
//	The MAngle class provides a fundamental type for the Maya API to hold
//	and manipulate angular data.  All API methods that require or return
//	angular information do so through variables of this type.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MTypes.h>
#include <maya/MStatus.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MAngle)

/// Manipulate Angular Data (OpenMaya) (OpenMaya.py)
/**
 Methods for setting and retreiving angular data in various unit systems
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MAngle  
{

public:
	/// Available Unit Systems
	enum Unit
	{
		///
		kInvalid,
		/// Radians
		kRadians,
		/// Degrees
		kDegrees,
		/// Minutes of Arc
		kAngMinutes,
		/// Seconds of Arc
		kAngSeconds,
		///
		kLast
	};
	///
	MAngle();
	///
	MAngle( const MAngle & src );
	///
	MAngle( double value, Unit u = kRadians );
 	///
 	~MAngle();
 	///
 	MAngle &     	operator=( const MAngle & other );
 	///
 	Unit    		unit() const;
 	///
 	double  		value() const;
 	///
 	MStatus         setUnit( Unit newUnit );
 	///
 	MStatus         setValue( double newValue );
 	///
 	double         	as( Unit otherUnit, MStatus *ReturnStatus = NULL ) const;
 	///
 	double         	asRadians() const;
 	///
 	double         	asDegrees() const;
 	///
 	double         	asAngMinutes() const;
 	///
 	double         	asAngSeconds() const;
 	///
 	static Unit		uiUnit();
 	///
 	static MStatus	setUIUnit( Unit newUnit );
	///
	static Unit		internalUnit();
	///
	static double	internalToUI( double internalValue );
	///
	static double	uiToInternal( double uiValue );
	///OBSOLETE Changing the internal units is generally not a good idea and using this method may often produce unexpected results.
	static MStatus  setInternalUnit( Unit internalUnit );

protected:
 	double 	val;
	Unit	valUnit;

private:
	static const char* className();

// No private members

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MAngle */
