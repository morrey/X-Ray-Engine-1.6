#ifndef _MDataBlock
#define _MDataBlock
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
// CLASS:    MDataBlock
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>

// ****************************************************************************
// FORWARD DECLARATIONS

class MObject;
class MPlug;
class MDGContext;

// ****************************************************************************
// CLASS DECLARATION (MDataBlock)

//! \ingroup OpenMaya
//! \brief Dependency node data block. 
/*!
An MDataBlock provides storage for the data being received by or sent by the
node.  It is the data for the plugs and attributes of the node.  The data
block is only valid during the compute method of the depend node.  Pointers to
the data block should not be retained after the compute method.

Access to the data in an MDataBlock is done using an MDataHandle or an
MArrayDataHandle.
*/
class OPENMAYA_EXPORT MDataBlock
{

public:

	virtual		     ~MDataBlock ();
	MDataHandle      inputValue ( const MPlug & plug,
								        MStatus * ReturnStatus = NULL );
	MDataHandle      inputValue ( const MObject & attribute,
								        MStatus * ReturnStatus = NULL );
	MDataHandle      outputValue ( const MPlug & plug,
								        MStatus * ReturnStatus = NULL );
	MDataHandle      outputValue ( const MObject & attribute,
								        MStatus * ReturnStatus = NULL );
	MArrayDataHandle inputArrayValue ( const MPlug & plug,
								        MStatus * ReturnStatus = NULL );
	MArrayDataHandle inputArrayValue ( const MObject & attribute,
								        MStatus * ReturnStatus = NULL );
	MArrayDataHandle outputArrayValue ( const MPlug & plug,
										MStatus * ReturnStatus = NULL );
	MArrayDataHandle outputArrayValue ( const MObject & attribute,
										MStatus * ReturnStatus = NULL );
	MStatus          setClean ( const MPlug & plug );
	MStatus          setClean ( const MObject & attribute );

	bool			isClean ( const MPlug & plug );
	bool			isClean ( const MObject & attribute,
							  MStatus* ReturnStatus=NULL );

	MDGContext       context ( MStatus * ReturnStatus = NULL );
	MStatus          setContext ( const MDGContext & ctx );

protected:
// No protected members

private:
	const char*		 className() const;

	friend class MArrayDataBuilder;

	friend class MPxNode;
	friend class MPlug;
	MDataBlock( void * ptr );
	void * data;
};

#endif /* __cplusplus */
#endif /* _MDataBlock */
