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
// meshRemapCmd.h
//
// Description:
//      Transfer the vertex/edge/face information from one mesh onto another.
//      The meshes are travesed based on three user supplied CVs, for each mesh,
//      The CV/edge/face information is mapped based on the traversal order within
//      each mesh.
//
// Usage:
//              meshRemap srcMesh.vtx[5] srcMesh.vtx[23] srcMesh.vtx[9] dstMesh.vtx[13] dstMesh.vtx[16] dstMesh.vtx[17]
//
// See Also:
//      meshRemapTool.cpp : this context allows you to interactively pick vertices and invoke this command
//
////////////////////////////////////////////////////////////////////////

#ifndef _MESH_REMAP_CMD_H_
#define _MESH_REMAP_CMD_H_

#include <maya/MPxCommand.h>

#include <maya/MDagPath.h>
#include <maya/MSelectionList.h>
#include <maya/MIntArray.h>

class MArgList;


// MAIN CLASS DECLARATION FOR THE MEL COMMAND:
class meshRemapCommand : public MPxCommand
{
	private:
 		int					fFaceIdxSrc;
 		int					fFaceIdxDst;

 		MIntArray			fFaceVtxSrc;
 		MIntArray			fFaceVtxDst;		

		MDagPath 			fDagPathSrc;
		MDagPath 			fDagPathDst;

	MStatus parseArgs(const MArgList&);

   public:
      meshRemapCommand();
      virtual ~meshRemapCommand();
      static void* creator();

	  MStatus setSeedInfo( bool src, MDagPath& path, int face, int vtx0, int vtx1 );

      MStatus doIt(const MArgList&);
      MStatus redoIt();
};

#endif
