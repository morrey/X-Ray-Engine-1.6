//
// Description: Get user selections for mesh vertex/edge remapping 
//
// Author: Bruce Hickey
//

// This is added to prevent multiple definitions of the MApiVersion string.
#define _MApiVersion

#include <maya/MIOStream.h>
#include <maya/MGlobal.h>
#include <maya/MCursor.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MItMeshVertex.h>

#include <meshRemapTool.h>
#include <meshMapUtils.h>


//////////////////////////////////////////////
// The user Context
//////////////////////////////////////////////

meshRemapTool::meshRemapTool()
{
	setTitleString ( "Mesh Remap Tool" );
	setCursor( MCursor::editCursor );
	reset();
}

meshRemapTool::~meshRemapTool() {}

void* meshRemapTool::creator()
{
	return new meshRemapTool;
}

void meshRemapTool::toolOnSetup ( MEvent & )
{
	reset();
}

void meshRemapTool::reset()
{
	fNumSelectedPoints = 0;

	fSelectedPathSrc.clear();
	fSelectedComponentSrc.clear();
	fSelectVtxSrc.clear();
	fSelectedFaceSrc = -1;

	fSelectedPathDst.clear();
	fSelectedComponentDst.clear();
	fSelectVtxDst.clear();
	fSelectedFaceDst = -1;

	fCurrentHelpString = "Select 1st point on source mesh.";

	helpStateHasChanged();
}

//
// Selects objects within the user defined area, then process them
// 
MStatus meshRemapTool::doRelease( MEvent & event )
{
	char buf[1024];

	// Perform the base actions
	MStatus stat = MPxSelectionContext::doRelease(event);

	// Get the list of selected items 
	MGlobal::getActiveSelectionList( fSelectionList );

	//
	//  If there's nothing selected, don't worry about it, just return
	//
	if( fSelectionList.length() != 1 )
	{
		MGlobal::displayWarning( "Components must be selected one at a time" );
		return MS::kSuccess;
	}

	//
	//  Get the selection's details, we must have exactly one component selected
	//
	MObject component;
	MDagPath path;

	MItSelectionList selectionIt (fSelectionList, MFn::kComponent);

	MStringArray	selections;
	selectionIt.getStrings( selections );
	
	if( selections.length() != 1 )
	{
		MGlobal::displayError( "Components must be selected one at a time" );
		return MS::kSuccess;
	}

	if (selectionIt.isDone ())
	{
		MGlobal::displayError( "Selected Item not a component" );
		return MS::kSuccess;
	}

	if( selectionIt.getDagPath (path, component) != MStatus::kSuccess )
	{
		MGlobal::displayError( "Can't get path for selection");
		return MS::kSuccess;
	}

	if (!path.node().hasFn(MFn::kMesh) && !(path.node().hasFn(MFn::kTransform) && path.hasFn(MFn::kMesh)))
	{
		MGlobal::displayError( " Invalid type! Only a mesh or its transform can be specified." );
		return MS::kSuccess;
	}

	MItMeshVertex fIt ( path, component, &stat );
	if( stat != MStatus::kSuccess )
	{
		MGlobal::displayError( " MItMeshVertex failed");
		return MStatus::kFailure;
	}

	if (fIt.count() != 1 )
	{
		sprintf(buf, " Invalid selection '%s'. Vertices must be picked one at a time.", selections[0].asChar() );
		MGlobal::displayError( buf );
		return MS::kSuccess;
	}
	else
	{
		sprintf(buf, "Accepting vertex '%s'", selections[0].asChar() );
		MGlobal::displayInfo(  buf );
	}

	//
	// Now that we know it's valid, process the selection, the first 3 items are the source, the second
	// 3 define the target
	//

	if( fNumSelectedPoints < 3 )
	{
		fSelectedPathSrc.append( path );
		fSelectedComponentSrc.append( component );
	}
	else 
	{
		fSelectedPathDst.append( path );
		fSelectedComponentDst.append( component );
	}

	//
	//  When each of the source/target are defined, process them. An error/invalid selection will restart the selection for
	//  that particular mesh.
	//  
	if( fNumSelectedPoints == 2 )
	{
		if( ( stat = meshMapUtils::validateFaceSelection( fSelectedPathSrc, fSelectedComponentSrc, &fSelectedFaceSrc, &fSelectVtxSrc ) ) != MStatus::kSuccess )
		{
			MGlobal::displayError("Selected vertices don't define a unique face on source mesh");
			reset();
			return stat;
		}
	}

	//
	// Once the target is defined, invoke the command
	//
	if( fNumSelectedPoints == 5 )
	{
		if( ( stat = meshMapUtils::validateFaceSelection( fSelectedPathDst, fSelectedComponentDst, &fSelectedFaceDst, &fSelectVtxDst ) ) != MStatus::kSuccess )
		{
			MGlobal::displayError("Selected vertices don't define a unique face on source mesh");
			reset();
			return stat;
		}

		fCmd = new meshRemapCommand;
		fCmd->setSeedInfo( true, fSelectedPathSrc[0], fSelectedFaceSrc, fSelectVtxSrc[0], fSelectVtxSrc[1] );
		fCmd->setSeedInfo( false, fSelectedPathDst[0], fSelectedFaceDst, fSelectVtxDst[0], fSelectVtxDst[1] );
		fCmd->redoIt();

		//
		// Empty the selection list since the reodering may move the user's current selection on screen
		//
		MSelectionList empty;
		MGlobal::setActiveSelectionList( empty );

		MGlobal::displayInfo( "Mesh remapping complete" );

		// 
		// Start again, get new meshes
		//
		reset();	
	}
	else
	{
		//
		// We don't have all the details yet, just move to the next item
		//
		fNumSelectedPoints++;	
	}

	helpStateHasChanged();

	return stat;
}

void meshRemapTool::helpStateHasChanged()
//
// Description:
//              Set up the correct information in the help window based
//              on the current state.  
//
{
	switch (fNumSelectedPoints)
	{
		case 0:
		 fCurrentHelpString = "Select 1st point on source mesh.";
		 break;
		case 1:
		 fCurrentHelpString = "Select 2nd point on source mesh.";
		 break;
		case 2:
		 fCurrentHelpString = "Select 3rd point on source mesh.";
		 break;
		case 3:
		 fCurrentHelpString = "Select 1st point on target mesh.";
		 break;
		case 4:
		 fCurrentHelpString = "Select 2nd point on target mesh.";
		 break;
		case 5:
		 fCurrentHelpString = "Select 3rd point on target mesh.";
		 break;
		default:
		 // nothing, shouldn't be here
		 break;
	 }

	setHelpString( fCurrentHelpString );
}

MPxContext* meshRemapContextCmd::makeObj()
{
	return new meshRemapTool;
}

void* meshRemapContextCmd::creator()
{
	return new meshRemapContextCmd;
}

//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+
