//
// Description: Get user selections for mesh vertex/edge reordering 
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

#include <meshReorderTool.h>
#include <meshMapUtils.h>


//////////////////////////////////////////////
// The user Context
//////////////////////////////////////////////

meshReorderTool::meshReorderTool()
{
	setTitleString ( "Mesh Reorder Tool" );
	setCursor( MCursor::editCursor );
	reset();
}

meshReorderTool::~meshReorderTool() {}

void* meshReorderTool::creator()
{
	return new meshReorderTool;
}

void meshReorderTool::toolOnSetup ( MEvent & )
{
	reset();
}

void meshReorderTool::reset()
{
	MEvent e;

	fNumSelectedPoints = 0;

	fSelectedPathSrc.clear();
	fSelectedComponentSrc.clear();
	fSelectVtxSrc.clear();
	fSelectedFaceSrc = -1;

	fCurrentHelpString = "Select 1st point on mesh.";

	helpStateHasChanged( e );
}

//
// Selects objects within the user defined area, then process them
// 
MStatus meshReorderTool::doRelease( MEvent & event )
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
	// Now that we know it's valid, process the selection
	//

	fSelectedPathSrc.append( path );
	fSelectedComponentSrc.append( component );

	//
	//  When each of the mesh defined, process it. An error/invalid selection will restart the selection for
	//  that particular mesh.
	//  
	if( fNumSelectedPoints == 2 )
	{
		if( ( stat = meshMapUtils::validateFaceSelection( fSelectedPathSrc, fSelectedComponentSrc, &fSelectedFaceSrc, &fSelectVtxSrc ) ) != MStatus::kSuccess )
		{
			MGlobal::displayError("Selected vertices don't define a unique face on mesh");
			reset();
			return stat;
		}

		fCmd = new meshReorderCommand;
		fCmd->setSeedInfo( fSelectedPathSrc[0], fSelectedFaceSrc, fSelectVtxSrc[0], fSelectVtxSrc[1] );
		fCmd->redoIt();

		//
		// Empty the selection list since the reodering may move the user's current selection on screen
		//
		MSelectionList empty;
		MGlobal::setActiveSelectionList( empty );

		MGlobal::displayInfo( "Mesh reordering complete" );

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

	helpStateHasChanged( event );

	return stat;
}

MStatus meshReorderTool::helpStateHasChanged( MEvent &)
//
// Description:
//              Set up the correct information in the help window based
//              on the current state.  
//
{
	switch (fNumSelectedPoints)
	{
		case 0:
		 fCurrentHelpString = "Select 1st point on mesh.";
		 break;
		case 1:
		 fCurrentHelpString = "Select 2nd point on mesh.";
		 break;
		case 2:
		 fCurrentHelpString = "Select 3rd point on mesh.";
		 break;
		default:
		 // nothing, shouldn't be here
		 break;
	 }

	setHelpString( fCurrentHelpString );

	return MS::kSuccess;
}

MPxContext* meshReorderContextCmd::makeObj()
{
	return new meshReorderTool;
}

void* meshReorderContextCmd::creator()
{
	return new meshReorderContextCmd;
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
