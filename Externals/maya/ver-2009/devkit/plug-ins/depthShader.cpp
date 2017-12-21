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

#include <maya/MPxNode.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h> 
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnLightDataAttribute.h> 
#include <maya/MFloatVector.h>
#include <maya/MFnPlugin.h>

/////////////////////////////////
// Plugin Depth Shader Class //
/////////////////////////////////

class depthShader : public MPxNode
{
	public:
                      depthShader();
    virtual          ~depthShader();

    virtual MStatus   compute( const MPlug&, MDataBlock& );
	virtual void      postConstructor();

    static  void *    creator();
    static  MStatus   initialize();

	//  Id tag for use with binary file format
    static  MTypeId   id;

	private:

	// Input attributes
    static MObject aColorNear;
    static MObject aColorFar;
    static MObject aNear;
    static MObject aFar;
    static MObject aPointCamera;

	// Output attributes
	static MObject aOutColor;
};

// static data
MTypeId depthShader::id( 0x81002 );

// Attributes
MObject depthShader::aColorNear;
MObject depthShader::aColorFar;
MObject depthShader::aNear;
MObject depthShader::aFar;
MObject depthShader::aPointCamera;

MObject depthShader::aOutColor;

#define MAKE_INPUT(attr)		\
    CHECK_MSTATUS(attr.setKeyable(true));  		\
	CHECK_MSTATUS(attr.setStorable(true));		\
    CHECK_MSTATUS(attr.setReadable(true)); 		\
	CHECK_MSTATUS(attr.setWritable(true));

#define MAKE_OUTPUT(attr)		\
    CHECK_MSTATUS(attr.setKeyable(false)); 		\
	CHECK_MSTATUS(attr.setStorable(false));		\
    CHECK_MSTATUS(attr.setReadable(true)); 		\
	CHECK_MSTATUS(attr.setWritable(false));

void depthShader::postConstructor( )
{
	setMPSafe(true);
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
depthShader::depthShader()
{
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
depthShader::~depthShader()
{
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
void* depthShader::creator()
{
    return new depthShader();
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus depthShader::initialize()
{
    MFnNumericAttribute nAttr; 

    // Create input attributes

	aColorNear = nAttr.createColor("color", "c");
	MAKE_INPUT(nAttr);
    CHECK_MSTATUS(nAttr.setDefault(0., 1., 0.));			// Green

	aColorFar = nAttr.createColor("colorFar", "cf");
	MAKE_INPUT(nAttr);
    CHECK_MSTATUS(nAttr.setDefault(0., 0., 1.));			// Blue

    aNear = nAttr.create("near", "n", MFnNumericData::kFloat);
	MAKE_INPUT(nAttr);
    CHECK_MSTATUS(nAttr.setMin(0.0f)); 
	CHECK_MSTATUS(nAttr.setSoftMax(1000.0f));

    aFar = nAttr.create("far", "f", MFnNumericData::kFloat);
	MAKE_INPUT(nAttr);
    CHECK_MSTATUS(nAttr.setMin(0.0f)); 
	CHECK_MSTATUS(nAttr.setSoftMax(1000.0f));
    CHECK_MSTATUS(nAttr.setDefault(2.0f));

    aPointCamera = nAttr.createPoint("pointCamera", "p");
	MAKE_INPUT(nAttr);
	CHECK_MSTATUS(nAttr.setHidden(true));

	// Create output attributes
    aOutColor = nAttr.createColor("outColor", "oc");
	MAKE_OUTPUT(nAttr);

    CHECK_MSTATUS(addAttribute(aColorNear));
    CHECK_MSTATUS(addAttribute(aColorFar));
    CHECK_MSTATUS(addAttribute(aNear) );
    CHECK_MSTATUS(addAttribute(aFar));
    CHECK_MSTATUS(addAttribute(aPointCamera));
    CHECK_MSTATUS(addAttribute(aOutColor));

    CHECK_MSTATUS(attributeAffects(aColorNear, aOutColor));
    CHECK_MSTATUS(attributeAffects(aColorFar, aOutColor));
    CHECK_MSTATUS(attributeAffects(aNear, aOutColor));
    CHECK_MSTATUS(attributeAffects(aFar, aOutColor));
    CHECK_MSTATUS(attributeAffects(aPointCamera, aOutColor));

    return MS::kSuccess;
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus depthShader::compute(
const MPlug&      plug,
      MDataBlock& block ) 
{
	// outColor or individial R, G, B channel
    if((plug != aOutColor) && (plug.parent() != aOutColor))
		return MS::kUnknownParameter;

	MFloatVector resultColor;

	// get sample surface shading parameters
	MFloatVector& pCamera = block.inputValue(aPointCamera).asFloatVector();
	MFloatVector& cNear   = block.inputValue(aColorNear).asFloatVector();
	MFloatVector& cFar    = block.inputValue(aColorFar).asFloatVector();
	float nearClip        = block.inputValue(aNear).asFloat();
	float farClip         = block.inputValue(aFar).asFloat();

	// pCamera.z is negative
	float ratio = (farClip + pCamera.z) / ( farClip - nearClip);
	resultColor = cNear * ratio + cFar*(1.f - ratio);

	// set ouput color attribute
	MDataHandle outColorHandle = block.outputValue( aOutColor );
	MFloatVector& outColor = outColorHandle.asFloatVector();
	outColor = resultColor;
	outColorHandle.setClean();

    return MS::kSuccess;
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus initializePlugin( MObject obj )
{ 
	const MString UserClassify( "shader/surface" );

	MFnPlugin plugin(obj, PLUGIN_COMPANY, "4.5", "Any");
	CHECK_MSTATUS( plugin.registerNode("depthShader", depthShader::id, 
						depthShader::creator, depthShader::initialize,
						MPxNode::kDependNode, &UserClassify ) );

	return MS::kSuccess;
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus uninitializePlugin( MObject obj )
{
	MFnPlugin plugin( obj );
	CHECK_MSTATUS( plugin.deregisterNode( depthShader::id ) );

	return MS::kSuccess;
}
