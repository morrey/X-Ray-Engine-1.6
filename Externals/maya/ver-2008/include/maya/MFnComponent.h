
#ifndef _MFnComponent
#define _MFnComponent
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
// CLASS:    MFnComponent
//
//    This is the base class for all function sets which deal with
//    component objects.
//
//    Components are MObjects which hold index information for shapes.
//    The component object does not contain any information about the
//    shape, it just contains index values and type information.
//
//    Components can be marked as complete meaning that the component
//    represents a complete set of indices from 0 to numElements-1;
//
//    Components come is 3 varieties based upon the dimensions of the
//    index. The types are single, double, and triple indexed.
//    Examples of these types are mesh vertices (single indexed),
//    nurbs surface CVs (double indexed), and lattice points (triple indexed).
//
//    To create, edit, or query a specific type of component, use the
//    derived classes MFnSingleIndexedComponent, MFnDoubleIndexedComponent,
//    and MFnTripleIndexedComponent.
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnComponent)
// 
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnBase.h>
#include <maya/MString.h>

// *****************************************************************************

// DECLARATIONS

class MIntArray;

// *****************************************************************************

// CLASS DECLARATION (MFnComponent)

/// Base class for component function sets. (OpenMaya) (OpenMaya.py)
/**
*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnComponent : public MFnBase 
{

	declareMFnNoVoidConstructor( MFnComponent, MFnBase );

public:
	///
	MFnComponent();
    ///
	int        elementCount( MStatus* ReturnStatus = NULL ); 
	///
	MFn::Type	componentType( MStatus * ReturnStatus = NULL );
	///
	bool		isEmpty( MStatus * ReturnStatus = NULL ) const;
	///
	bool		isEqual( MObject &, MStatus * ReturnStatus = NULL ) const;
	///
	bool		isComplete( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus		setComplete( bool );

BEGIN_NO_SCRIPT_SUPPORT:

	declareMFnNoVoidConstructorConstConstructor( MFnComponent, MFnBase );

	///	BSOLETE & NO SCRIPT SUPPORT
	MFn::Type	type( MStatus * ReturnStatus = NULL );

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
#endif /* _MFnComponent */
