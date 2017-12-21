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

//
//	squareScaleManip.cpp
//		Creates manipulator node squareScaleManipulator
//		Creates command squareManipCmd
//
//	This example demonstrates how to use the MPxManipulatorNode
//	class along with a command to create a user defined
//	manipulator.  The manipulator created is a simple square
//	with the 4 sides as OpenGL pickable components.  As you
//	move the pickable component, selected transforms have
//	their scale attribute modified.
//	A corresponding command is used to create and delete
//	the manipulator node and to support undo/redo etc.
 
/*

// To show this example using MEL, run the following:
loadPlugin squareScaleManip.so;
squareManipCmd -create;

// To delete the manipulator using MEL:
squareManipCmd -delete;

*/

#include "squareScaleManip.h"

#include <maya/MHardwareRenderer.h>
#include <maya/MIOStream.h>
#include <maya/MMatrix.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MFnTransform.h>
#include <maya/MGlobal.h>
#include <maya/MFnCamera.h>
#include <maya/MTemplateCommand.h>

// Statics
MTypeId squareScaleManipulator::id( 0x81046 );

// Utility class for returning square points
class squareGeometry
{
public:
	static MPoint topLeft() {
		return MPoint( -0.5f, 0.5f, 0.0f );
	}
	static MPoint topRight() {
		return MPoint( 0.5f, 0.5f, 0.0f );
	}
	static MPoint bottomLeft() {
		return MPoint( -0.5f, -0.5f, 0.0f );
	}
	static MPoint bottomRight() {
		return MPoint( 0.5f, -0.5f, 0.0f );
	}
};

//
// class implementation
//
squareScaleManipulator::squareScaleManipulator()
{
	// Setup the plane with a point on the
	// plane along with a normal
	MPoint pointOnPlane(squareGeometry::topLeft());
	// Normal = cross product of two vectors on the plane
	MVector normalToPlane = (MVector(squareGeometry::topLeft()) - MVector(squareGeometry::topRight())) ^ 
					(MVector(squareGeometry::topRight()) - MVector(squareGeometry::bottomRight()));
	// Necessary to normalize
	normalToPlane.normalize();
	// Plane defined by a point and a normal
	plane.setPlane( pointOnPlane, normalToPlane );
}

squareScaleManipulator::~squareScaleManipulator()
{
	// No-op
}

// virtual 
void squareScaleManipulator::draw(M3dView &view, const MDagPath &path,
				M3dView::DisplayStyle style, M3dView::DisplayStatus status)
{
	// Acquire the GL function table pointer first time through
	static MGLFunctionTable *gGLFT = 0;
	if ( 0 == gGLFT )
		gGLFT = MHardwareRenderer::theRenderer()->glFunctionTable();

	// Are we in the right view
	MDagPath dpath;
	view.getCamera(dpath);
	MFnCamera viewCamera(dpath);
	const char *nameBuffer = viewCamera.name().asChar();
	if ( 0 == nameBuffer )
		return;
	if ( ( 0 == strstr(nameBuffer,"persp") ) && ( 0 == strstr(nameBuffer,"front") ) )
		return;

	// Populate the point arrays which are in local space
	float tl[4],tr[4],br[4],bl[4];
	squareGeometry::topLeft().get(tl);
	squareGeometry::topRight().get(tr);
	squareGeometry::bottomLeft().get(bl);
	squareGeometry::bottomRight().get(br);

	// Depending on what's active, we modify the
	// end points with mouse delta's in local
	// space
	MGLuint active = 0;
	if ( glActiveName( active ) )
	{
		float *a = 0,*b = 0;
		if ( active == topName )
		{
			a = &tl[0]; b = &tr[0];
		}
		if ( active == bottomName )
		{
			a = &bl[0]; b = &br[0];
		}
		if ( active == rightName )
		{
			a = &tr[0]; b = &br[0];
		}
		if ( active == leftName )
		{
			a = &tl[0]; b = &bl[0];
		}

		if ( active != 0 )
		{
			a[0] += (float) mousePointGlName.x; a[1] += (float) mousePointGlName.y; a[2] += (float) mousePointGlName.z;
			b[0] += (float) mousePointGlName.x; b[1] += (float) mousePointGlName.y; b[2] += (float) mousePointGlName.z;
		}
        }

	// Begin the drawing
	view.beginGL();

	// Get the starting value of the pickable items
	MGLuint glPickableItem;
	glFirstHandle( glPickableItem );

	// Top
	topName = glPickableItem;
	// Place before you draw the manipulator component that can
	// be pickable.
	colorAndName( view, glPickableItem, true, mainColor() );
	gGLFT->glBegin( MGL_LINES );
		gGLFT->glVertex3fv( tl );
		gGLFT->glVertex3fv( tr );
	gGLFT->glEnd();

	// Right
	glPickableItem++;
	rightName = glPickableItem;
	colorAndName( view, glPickableItem, true, mainColor() );
	gGLFT->glBegin( MGL_LINES );
		gGLFT->glVertex3fv( tr );
		gGLFT->glVertex3fv( br );
	gGLFT->glEnd();

	// Bottom
	glPickableItem++;
	bottomName = glPickableItem;
	colorAndName( view, glPickableItem, true, mainColor() );
	gGLFT->glBegin( MGL_LINES );
		gGLFT->glVertex3fv( br );
		gGLFT->glVertex3fv( bl );
	gGLFT->glEnd();

	// Left
	glPickableItem++;
	leftName = glPickableItem;
	colorAndName( view, glPickableItem, true, mainColor() );
	gGLFT->glBegin( MGL_LINES );
		gGLFT->glVertex3fv( bl );
		gGLFT->glVertex3fv( tl );
	gGLFT->glEnd();

	// End the drawing
	view.endGL();
}

// virtual 
MStatus	squareScaleManipulator::doPress( M3dView& view )
{
	// Reset the mousePoint information on
	// a new press
	mousePointGlName = MPoint::origin;
	updateDragInformation();
	return MS::kSuccess;
}

// virtual
MStatus	squareScaleManipulator::doDrag( M3dView& view )
{
	updateDragInformation();	
	return MS::kSuccess;
}

// virtual
 MStatus squareScaleManipulator::doRelease( M3dView& view )
{
	// Scale nodes on the selection list. Implementation
	// is very simple and will not support undo.
	MSelectionList list;
	MGlobal::getActiveSelectionList( list );
	for ( MItSelectionList iter( list ); !iter.isDone(); iter.next() ) 
	{
		MObject node;
		MStatus status;
	        iter.getDependNode( node );
		MFnTransform xform( node, &status );
		if ( MS::kSuccess == status )
		{
			double newScale[3];
			newScale[0] = mousePointGlName.x + 1;
			newScale[1] = mousePointGlName.y + 1;
			newScale[2] = mousePointGlName.z + 1;
			xform.setScale( newScale );
		}
	}
	return MS::kSuccess;
}

//
MStatus squareScaleManipulator::updateDragInformation()
{
	// Find the mouse point in local space
	MPoint localMousePoint;
	MVector localMouseDirection;
	if ( MS::kFailure == mouseRay( localMousePoint, localMouseDirection) )
		return MS::kFailure;

	// Find the intersection of the mouse point with the
	// manip plane
	MPoint mouseIntersectionWithManipPlane;
	if ( ! plane.intersect( localMousePoint, localMouseDirection, 	mouseIntersectionWithManipPlane ) )
		return MS::kFailure;

	mousePointGlName = mouseIntersectionWithManipPlane;

	MGLuint active = 0;
	if ( glActiveName( active ) )
	{
		float start[4],end[4];
		if ( active == topName )
		{
			squareGeometry::topLeft().get(start);
			squareGeometry::topRight().get(end);
		}
		if ( active == bottomName )
		{
			squareGeometry::bottomLeft().get(start);
			squareGeometry::bottomRight().get(end);
		}
		if ( active == rightName )
		{
			squareGeometry::topRight().get(start);
			squareGeometry::bottomRight().get(end);
		}
		if ( active == leftName )
		{
			squareGeometry::topLeft().get(start);
			squareGeometry::bottomLeft().get(end);
		}

		if ( active != 0 )
		{
			lineMath line;
			// Find a vector on the plane
			MPoint a( start[0], start[1], start[2] );
			MPoint b( end[0], end[1], end[2] );
			MPoint vab = a - b;
			// Define line with a point and a vector on the plane
			line.setLine( start, vab );
			MPoint cpt;
			// Find the closest point so that we can get the
			// delta change of the mouse in local space
			if ( line.closestPoint( mousePointGlName, cpt ) )
			{
				mousePointGlName.x -= cpt.x;
				mousePointGlName.y -= cpt.y;
				mousePointGlName.z -= cpt.z;
			}
		}
	}
	return MS::kSuccess;
}

//
// Template command that creates and deletes the manipulator
//

class squareManipCmd;
char cmdName[] = "squareManipCmd";
char nodeName[] = "squareScaleManipulator";

class squareManipCmd : public MTemplateCreateNodeCommand<squareManipCmd,cmdName,nodeName>
{
public:
	//
	squareManipCmd()
	{}
};

static squareManipCmd _squareManipCmd;

//
// Static methods
//
void* squareScaleManipulator::creator()
{
	return new squareScaleManipulator();
}

MStatus squareScaleManipulator::initialize()
{
	// No-op
	return MS::kSuccess;
}

//
//	Entry points
//

MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj, PLUGIN_COMPANY, "2009", "Any");

	status = plugin.registerNode( nodeName, squareScaleManipulator::id, squareScaleManipulator::creator,
		squareScaleManipulator::initialize, MPxNode::kManipulatorNode );
	if (!status) {
		status.perror("registerNode");
		return status;
	}

	status = _squareManipCmd.registerCommand( obj );
	if (!status) {
		status.perror("registerCommand");
		return status;
	}

	return status;
}

MStatus uninitializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode( squareScaleManipulator::id );
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}
	status = _squareManipCmd.deregisterCommand( obj );
	if (!status) {
		status.perror("deregisterCommand");
		return status;
	}

	return status;
}


