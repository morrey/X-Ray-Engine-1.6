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

#include "meshRemapCmd.h"
#include "meshMapUtils.h"

#include <maya/MItSelectionList.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MArgList.h>
#include <maya/MStatus.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFnMesh.h>
#include <maya/MDagPathArray.h>
#include <maya/MObjectArray.h>


// CONSTRUCTOR DEFINITION:
meshRemapCommand::meshRemapCommand()
{
}


// DESTRUCTOR DEFINITION:
meshRemapCommand::~meshRemapCommand()
{
}


// METHOD FOR CREATING AN INSTANCE OF THIS COMMAND:
void* meshRemapCommand::creator()
{
   return new meshRemapCommand;
}


MStatus meshRemapCommand::parseArgs(const MArgList& args)
{
	MSelectionList list;
	MString err;
	MStatus stat; 

	if( args.length() != 6 )
	{
		displayError("6 vertices must be specified");
		return MS::kFailure;
	}

	int argIdx = 0;
	for (unsigned int i = 0; i < 2; i++)
	{
		MObjectArray selectedComponent(3);
		MDagPathArray selectedPath;

		selectedPath.setLength(3);

		for (unsigned int j = 0; j < 3; j++)
		{
			MString arg;

			if( ( stat = args.get( argIdx, arg )) != MStatus::kSuccess )
			{
				displayError( "Can't parse arg");
				return stat;
			}

			list.clear();	
			if (! list.add( arg ) )
			{
				err = arg + ": no such component";
				displayError(err);
				return MS::kFailure; // no such component
			}

			MItSelectionList selectionIt (list, MFn::kComponent);
			if (selectionIt.isDone ())
			{
				err = arg + ": not a component";
				displayError (err);
				return MS::kFailure;
			}

			if( selectionIt.getDagPath (selectedPath[j], selectedComponent[j]) != MStatus::kSuccess )
			{
				displayError( "Can't get path for");
				return stat;
			}


			if (!selectedPath[j].node().hasFn(MFn::kMesh) && !(selectedPath[j].node().hasFn(MFn::kTransform) && selectedPath[j].hasFn(MFn::kMesh)))
			{
				err = arg + ": Invalid type!  Only a mesh or its transform can be specified!";
				displayError (err);
				return MStatus::kFailure;
			}

			argIdx++;
		}

		if( i == 0 )
		{
			if( ( stat = meshMapUtils::validateFaceSelection( selectedPath, selectedComponent, &fFaceIdxSrc, &fFaceVtxSrc ) ) != MStatus::kSuccess )
			{
				displayError("Selected vertices don't define a unique face on source mesh");
				return stat;
			}

			fDagPathSrc = selectedPath[0];
		}
		else
		{
			if( ( stat = meshMapUtils::validateFaceSelection( selectedPath, selectedComponent, &fFaceIdxDst, &fFaceVtxDst ) ) != MStatus::kSuccess )
			{
				displayError("Selected vertices don't define a unique face on target mesh");
				return stat;
			}

			fDagPathDst = selectedPath[0];
		}
	}


	if( fDagPathSrc == fDagPathDst )
	{
		displayError("Cannot use one mesh for both source and target");
		return stat;
	}

	return MStatus::kSuccess;
}


// FIRST INVOKED WHEN COMMAND IS CALLED, PARSING THE COMMAND ARGUMENTS, INITIALIZING DEFAULT PARAMETERS, THEN CALLING redoIt():
MStatus meshRemapCommand::doIt(const MArgList& args)
{
	MStatus  stat = MStatus::kSuccess;

	if ( ( stat = parseArgs( args ) ) != MStatus::kSuccess )
	{
		displayError ("Error parsing arguments");
		return stat;
	}

	return redoIt();
}

MStatus meshRemapCommand::redoIt()
{
	MStatus  stat = MStatus::kSuccess;

	fDagPathSrc.extendToShape();
	MFnMesh theMeshSrc( fDagPathSrc, &stat );
	if( stat != MStatus::kSuccess )
	{
		displayError(" MFnMesh creation");
		return stat;
	}

	MFloatPointArray 	origVertices;
	stat = theMeshSrc.getPoints (origVertices, MSpace::kObject );
	if( stat != MStatus::kSuccess )
	{
		displayError(" MFnMesh getPoints");
		return stat;
	}

	// 
	// Traverse the source
	//
	
	// 
	// Initialize the traversal flags and CV mappings for this shape 
	MIntArray 			faceTraversal( theMeshSrc.numPolygons(), false );
	MIntArray 			cvMapping( theMeshSrc.numVertices(), -1 );
	MIntArray 			cvMappingInverse( theMeshSrc.numVertices(), -1 ); 

	//
	//  Starting with the user selected face, recursively rebuild the entire mesh
	//

	MIntArray 			newPolygonCounts;
	MIntArray 			newPolygonConnects;
	MFloatPointArray 	newVertices;

	stat = meshMapUtils::traverseFace( fDagPathSrc, fFaceIdxSrc, fFaceVtxSrc[0], fFaceVtxSrc[1], faceTraversal,
					cvMapping, cvMappingInverse, 
					newPolygonCounts, newPolygonConnects, 
					origVertices, newVertices );
	if ( stat != MStatus::kSuccess )
	{
		displayError(" could not process all the mesh faces.");
		return stat;
	}

	// 
	// Now, traverse the destination
	//
	
	fDagPathDst.extendToShape();
	MFnMesh theMeshDst( fDagPathDst, &stat );
	if( stat != MStatus::kSuccess )
	{
		displayError(" MFnMesh creation");
		return stat;
	}

	MFloatPointArray 	origVerticesDst;
	stat = theMeshDst.getPoints (origVerticesDst, MSpace::kObject );
	if( stat != MStatus::kSuccess )
	{
		displayError(" MFnMesh getPoints");
		return stat;
	}

	// Initialize the traversal flags and CV mappings for this shape 
	MIntArray 			faceTraversalDst( theMeshDst.numPolygons(), false );
	MIntArray 			cvMappingDst( theMeshDst.numVertices(), -1 );
	MIntArray 			cvMappingInverseDst( theMeshDst.numVertices(), -1 ); 

	//
	//  Starting with the user selected face, recursively rebuild the entire mesh
	//

	MIntArray 			newPolygonCountsDst;
	MIntArray 			newPolygonConnectsDst;
	MFloatPointArray 	newVerticesDst;

	stat = meshMapUtils::traverseFace( fDagPathDst, fFaceIdxDst, fFaceVtxDst[0], fFaceVtxDst[1], faceTraversalDst,
					cvMappingDst, cvMappingInverseDst, 
					newPolygonCountsDst, newPolygonConnectsDst, 
					origVerticesDst, newVerticesDst );
	if ( stat != MStatus::kSuccess )
	{
		displayError(" could not process all the mesh faces.");
		return stat;
	}

	//
	// Use the generated maps to build a new CV list that will remap
	// the destination to the source topology
	//
	for( int i = 0; i < theMeshDst.numVertices(); i++ )
	{
		newVerticesDst[cvMappingInverse[i]] = origVerticesDst[cvMappingInverseDst[i]];
	}

	//
	//  Copy the topology
	// 
	stat = theMeshDst.copyInPlace( fDagPathSrc.node() );
	if ( stat != MStatus::kSuccess )
	{
		displayError(" mesh copy failed.");
		return stat;
	}

	//
	// Transfer the reindexed CVs
	//
	stat = theMeshDst.setPoints( newVerticesDst );
	if ( stat != MStatus::kSuccess )
	{
		displayError(" setPoints failed.");
		return stat;
	}


	return stat;
}

MStatus meshRemapCommand::setSeedInfo( bool src, MDagPath& path, int face, int vtx0, int vtx1 )
{
	if( src )
	{
		fDagPathSrc = path;
		fFaceIdxSrc = face;
		fFaceVtxSrc.setLength(2);
		fFaceVtxSrc[0] = vtx0;
		fFaceVtxSrc[1] = vtx1;
	}
	else
	{
		fDagPathDst = path;
		fFaceIdxDst = face;
		fFaceVtxDst.setLength(2);
		fFaceVtxDst[0] = vtx0;
		fFaceVtxDst[1] = vtx1;
	}

	return MStatus::kSuccess;
}
