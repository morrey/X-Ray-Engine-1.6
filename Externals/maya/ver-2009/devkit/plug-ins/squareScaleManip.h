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

#include <maya/MTypeId.h>
#include <maya/MTypes.h>
#include <maya/MPxManipulatorNode.h>
#include <maya/MFnPlugin.h>
#include <maya/MObjectHandle.h>
#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>
#include <maya/MDagModifier.h>

#include <maya/M3dView.h>
#include <maya/MGLFunctionTable.h>

#include "manipulatorMath.h"

//
// Custom manipulator class
//
class squareScaleManipulator : public MPxManipulatorNode
{
public:
	squareScaleManipulator();
	~squareScaleManipulator();

	// The important virtuals to implement
	virtual void draw(M3dView &view, const MDagPath &path,
				M3dView::DisplayStyle style, M3dView::DisplayStatus status);

	virtual MStatus	doPress( M3dView& view );
	virtual MStatus	doDrag( M3dView& view );
	virtual MStatus	doRelease( M3dView& view );

	// Utility method
	MStatus updateDragInformation();

	// Standard API required methods
	static void* creator();
	static MStatus initialize();

	// Node id
	static MTypeId id;

private:
	// GL component names for drawing and picking
	MGLuint topName, rightName, bottomName, leftName;
	// Simple class for plane creation, intersection
	planeMath plane;
	// Modified mouse position used for updating manipulator
	MPoint mousePointGlName;
};



