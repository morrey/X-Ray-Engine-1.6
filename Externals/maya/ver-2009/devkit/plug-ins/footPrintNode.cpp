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

#include <maya/MPxLocatorNode.h> 
#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MColor.h>
#include <maya/M3dView.h>
#include <maya/MFnPlugin.h>
#include <maya/MDistance.h>
#include <maya/MFnUnitAttribute.h>

// Foot Data
//
static float sole[][3] = { {  0.00f, 0.0f, -0.70f },
						   {  0.04f, 0.0f, -0.69f },
						   {  0.09f, 0.0f, -0.65f },
						   {  0.13f, 0.0f, -0.61f }, 
						   {  0.16f, 0.0f, -0.54f },
						   {  0.17f, 0.0f, -0.46f },
						   {  0.17f, 0.0f, -0.35f },
						   {  0.16f, 0.0f, -0.25f },
						   {  0.15f, 0.0f, -0.14f },
						   {  0.13f, 0.0f,  0.00f },
						   {  0.00f, 0.0f,  0.00f },
						   { -0.13f, 0.0f,  0.00f },
						   { -0.15f, 0.0f, -0.14f },
						   { -0.16f, 0.0f, -0.25f },
						   { -0.17f, 0.0f, -0.35f },
						   { -0.17f, 0.0f, -0.46f }, 
						   { -0.16f, 0.0f, -0.54f },
						   { -0.13f, 0.0f, -0.61f },
						   { -0.09f, 0.0f, -0.65f },
						   { -0.04f, 0.0f, -0.69f }, 
						   { -0.00f, 0.0f, -0.70f } }; 
static float heel[][3] = { {  0.00f, 0.0f,  0.06f },
						   {  0.13f, 0.0f,  0.06f },
						   {  0.14f, 0.0f,  0.15f },
						   {  0.14f, 0.0f,  0.21f }, 
						   {  0.13f, 0.0f,  0.25f },
						   {  0.11f, 0.0f,  0.28f },
						   {  0.09f, 0.0f,  0.29f },
						   {  0.04f, 0.0f,  0.30f },
						   {  0.00f, 0.0f,  0.30f },
						   { -0.04f, 0.0f,  0.30f },
						   { -0.09f, 0.0f,  0.29f },
						   { -0.11f, 0.0f,  0.28f }, 
						   { -0.13f, 0.0f,  0.25f },
						   { -0.14f, 0.0f,  0.21f },
						   { -0.14f, 0.0f,  0.15f },
						   { -0.13f, 0.0f,  0.06f },  
						   { -0.00f, 0.0f,  0.06f } }; 
static int heelCount = 17;
static int soleCount = 21;
 

class footPrint : public MPxLocatorNode
{
public:
	footPrint();
	virtual ~footPrint(); 

    virtual MStatus   		compute( const MPlug& plug, MDataBlock& data );

	virtual void            draw( M3dView & view, const MDagPath & path, 
								  M3dView::DisplayStyle style,
								  M3dView::DisplayStatus status );

	virtual bool            isBounded() const;
	virtual MBoundingBox    boundingBox() const; 

	static  void *          creator();
	static  MStatus         initialize();

	static  MObject         size;         // The size of the foot

public: 
	static	MTypeId		id;
};

MTypeId footPrint::id( 0x80007 );
MObject footPrint::size;

footPrint::footPrint() {}
footPrint::~footPrint() {}

MStatus footPrint::compute( const MPlug& /*plug*/, MDataBlock& /*data*/ )
{ 
	return MS::kUnknownParameter;
}

void footPrint::draw( M3dView & view, const MDagPath & /*path*/, 
							 M3dView::DisplayStyle style,
							 M3dView::DisplayStatus status )
{ 
	// Get the size
	//
	MObject thisNode = thisMObject();
	MPlug plug( thisNode, size );
	MDistance sizeVal;
	plug.getValue( sizeVal );

	float multiplier = (float) sizeVal.asCentimeters();

	view.beginGL(); 


	if ( ( style == M3dView::kFlatShaded ) || 
		 ( style == M3dView::kGouraudShaded ) ) 
	{  
		// Push the color settings
		// 
		glPushAttrib( GL_CURRENT_BIT );

		if ( status == M3dView::kActive ) {
			view.setDrawColor( 13, M3dView::kActiveColors );
		} else {
			view.setDrawColor( 13, M3dView::kDormantColors );
		}  

		glBegin( GL_TRIANGLE_FAN );
	        int i;
			int last = soleCount - 1;
			for ( i = 0; i < last; ++i ) {
				glVertex3f( sole[i][0] * multiplier,
							sole[i][1] * multiplier,
							sole[i][2] * multiplier );
			} 
		glEnd();
		glBegin( GL_TRIANGLE_FAN );
			last = heelCount - 1;
			for ( i = 0; i < last; ++i ) {
				glVertex3f( heel[i][0] * multiplier,
							heel[i][1] * multiplier,
							heel[i][2] * multiplier );
			}
		glEnd();

		glPopAttrib();
	}

	// Draw the outline of the foot
	//
	glBegin( GL_LINES );
	    int i;
	    int last = soleCount - 1;
	    for ( i = 0; i < last; ++i ) { 
			glVertex3f( sole[i][0] * multiplier, 
						sole[i][1] * multiplier, 
						sole[i][2] * multiplier );
			glVertex3f( sole[i+1][0] * multiplier, 
						sole[i+1][1] * multiplier, 
						sole[i+1][2] * multiplier );
		} 
		last = heelCount - 1;
	    for ( i = 0; i < last; ++i ) { 
			glVertex3f( heel[i][0] * multiplier, 
						heel[i][1] * multiplier, 
						heel[i][2] * multiplier );
			glVertex3f( heel[i+1][0] * multiplier, 
						heel[i+1][1] * multiplier, 
						heel[i+1][2] * multiplier );
		}
	glEnd();
		

	view.endGL();
}

bool footPrint::isBounded() const
{ 
	return true;
}

MBoundingBox footPrint::boundingBox() const
{   
	// Get the size
	//
	MObject thisNode = thisMObject();
	MPlug plug( thisNode, size );
	MDistance sizeVal;
	plug.getValue( sizeVal );

	double multiplier = sizeVal.asCentimeters();
 
	MPoint corner1( -0.17, 0.0, -0.7 );
	MPoint corner2( 0.17, 0.0, 0.3 );

	corner1 = corner1 * multiplier;
	corner2 = corner2 * multiplier;

	return MBoundingBox( corner1, corner2 );
}

void* footPrint::creator()
{
	return new footPrint();
}

MStatus footPrint::initialize()
{ 
	MFnUnitAttribute unitFn;
	MStatus			 stat;

	size = unitFn.create( "size", "sz", MFnUnitAttribute::kDistance );
	unitFn.setDefault( 1.0 );

	stat = addAttribute( size );
	if (!stat) {
		stat.perror("addAttribute");
		return stat;
	}
	
	return MS::kSuccess;
}

MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj, PLUGIN_COMPANY, "3.0", "Any");

	status = plugin.registerNode( "footPrint", footPrint::id, 
						 &footPrint::creator, &footPrint::initialize,
						 MPxNode::kLocatorNode );
	if (!status) {
		status.perror("registerNode");
		return status;
	}
	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode( footPrint::id );
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

	return status;
}
