#ifndef _cgfxShaderCmd_h_
#define _cgfxShaderCmd_h_
//
// Copyright (C) 2002-2003 NVIDIA 
// 
// File: cgfxShaderCmd.h
//
// MEL Command: cgfxShader
//
// Author: Maya SDK Wizard
//
// Changes:
//  10/2003  Kurt Harriman - www.octopusgraphics.com +1-415-893-1023
//             Multiple UV sets; user-specified texcoord assignment;
//             error handling.
//  12/2003  Kurt Harriman - www.octopusgraphics.com +1-415-893-1023
//           - Added members: fListTechniques, fCaseInsensitive,
//             fDescription, fOldeTechnique, fOldSelection,
//             fNewTechnique, fNodeSelection
//           - Deleted members: fSemantic, fTechnique
//           - Deleted class cgfxShaderCmd::InternalError
//           - Changed: redoCmd(), fDagMod
//           - Use MDGModifier instead of MDagModifier
//
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
#include "cgfxShaderCommon.h"

#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>
#include <maya/MArgList.h>
#include <maya/MSelectionList.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MDGModifier.h>

#include "cgfxAttrDef.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

class MArgList;

class cgfxShaderCmd : public MPxCommand
{

public:
	cgfxShaderCmd();
	virtual				~cgfxShaderCmd();

	MStatus				doIt( const MArgList& );
	MStatus				redoIt();
	MStatus				undoIt();
	bool				isUndoable() const;

	static MSyntax		newSyntax();
	static void*		creator();

	static MString      sPluginPath;   // directory path for scripts etc.

private:
	MStatus             doCmd( const MArgList& );
	MStatus             redoCmd( 
		MObject& oNode, 
		MFnDependencyNode& fnNode, 
		cgfxShaderNode* pNode );
	MStatus             undoCmd();

	MStatus				parseArgs(const MArgList& args,
		MSelectionList& selList);

	// Command line flags 

	MString             fArgString;         // all of the args
	bool                fIsEdit;            // -e   / -edit 
	bool                fIsQuery;           // -q   / -query

	bool                fMaxTexCoords;      // -mtc / -maxTexCoords
	bool                fPluginPath;        // -pp  / -pluginPath  

	bool                fEmptyUV;           // -euv / -emptyUV
	bool                fEmptyUVShapes;     // -eus / -emptyUVShapes
	bool                fListParameters;    // -lp  / -listParameters
	bool                fListTechniques;    // -lt  / -listTechniques
	bool                fTexCoordSource;    // -tcs / -texCoordSource
#if MAYA_API_VERSION >= 700
	bool                fColorSource;       // -cs / -colorSource
#endif

	bool                fCaseInsensitive;   // -ci  / -caseInsensitive   
	bool                fDescription;       // -des / -description   

	// Are we listing a single parameter
	//
	MString				fParameterName;

	// For undo purposes, save the current state before making changes
	//
	MString						fOldFxFile;
	MString						fOldTechnique;
	MStringArray			fOldAttributeList;
	CGeffect					fOldEffect;
	cgfxAttrDefList*	fOldAttrDefList;
	MSelectionList    fOldSelection;

	// For redo purposes, save new current state after making changes
	//
	MString						fNewFxFile;
	MString						fNewTechnique;
	MStringArray			fNewAttributeList;
	CGeffect					fNewEffect;
	cgfxAttrDefList*	fNewAttrDefList;

	// For undo and redo,
	//
	MSelectionList      fNodeSelection;
	MString				fNodeName;		// Create only
	MDGModifier*        fDagMod;

	// Error reporting
	void reportInternalError( const char* function, size_t errcode );

};

#endif /* _cgfxShaderCmd_h_ */
