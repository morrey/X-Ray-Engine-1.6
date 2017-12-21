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

////////////////////////////////////////////////////////////////////////
// 
// meshReorderCmd.h
// 
// Description:
// 	Command to reindex a polygon mesh based on a used defined starting face
//
// Usage:
//      meshOrder mesh.vtx[5] mesh.vtx[23] mesh.vtx[9] 
//
// See Also:
//      meshReorderTool.cpp : this context allows you to interactively pick vertices and invoke this command
// 
////////////////////////////////////////////////////////////////////////

#ifndef _MESH_REORDER_CMD_H_
#define _MESH_REORDER_CMD_H_

#include <maya/MArgList.h>
#include <maya/MPxCommand.h>
#include <maya/MSelectionList.h>
#include <maya/MIntArray.h>
#include <maya/MItMeshEdge.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MDagPath.h>

// MAIN CLASS DECLARATION FOR THE MEL COMMAND:
class meshReorderCommand : public MPxCommand
{
   private:
	int                 fFaceIdxSrc;
	MIntArray           fFaceVtxSrc;
	MDagPath            fDagPathSrc;

	MStatus 			parseArgs(const MArgList&);

   public:
	meshReorderCommand();
	virtual ~meshReorderCommand();

	MStatus setSeedInfo( MDagPath& path, int face, int vtx0, int vtx1 );

	static void* creator();
	MStatus doIt(const MArgList&);
	MStatus redoIt();

};

#endif

