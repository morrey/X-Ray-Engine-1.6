#ifndef _MIkSystem
#define _MIkSystem
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
// CLASS:    MIkSystem
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MObject.h>
#include <maya/MStringArray.h>
#include <maya/MStatus.h>

// ****************************************************************************
// CLASS DECLARATION (MIkSystem)

//! \ingroup OpenMayaAnim
//! Inverse kinematics (IK) system class
/*!
	This class provides an interface to the inverse kinematics (IK) system.
	The ik system is used to set/query the global snapping flag for handles,
	set/query the global solve flag for solvers, and to find the ik solvers
	available in maya.
*/
class OPENMAYAANIM_EXPORT MIkSystem
{
public:
	static MObject	findSolver( MString name, MStatus * ReturnStatus = NULL );
	static MStatus	getSolvers( MStringArray & names );
	static bool		isGlobalSnap( MStatus * ReturnStatus = NULL );
	static MStatus	setGlobalSnap( bool isSnap );
	static bool		isGlobalSolve( MStatus * ReturnStatus = NULL );
	static MStatus	setGlobalSolve( bool isSnap );
protected:
	static const char* className();

private:
// No private members
};

#endif /* __cplusplus */
#endif /* _MIkSystem */
