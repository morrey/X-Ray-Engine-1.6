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

///////////////////////////////////////////////////////
//
// DESCRIPTION:  Gamma correction utility node
//
///////////////////////////////////////////////////////

#include <math.h>

#include <maya/MPxNode.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFloatVector.h>
#include <maya/MFnPlugin.h>

//
// DESCRIPTION:
///////////////////////////////////////////////////////
class Gamma:public MPxNode
{
	public:
                    Gamma();
    virtual         ~Gamma();

	virtual MStatus compute( const MPlug&, MDataBlock& );
	virtual void    postConstructor();

    static void *  creator();
    static MStatus initialize();

	// Id tag for use with binary file format
    static MTypeId id;

	private:

	// Input attributes
	static MObject aColor;					// Input color
    static MObject aGamma;					// R, G, B correction

	// Output attributes
	static MObject aOutColor;
};

// static data
MTypeId Gamma::id( 0x81009 );

// Attributes
MObject Gamma::aColor;
MObject Gamma::aGamma;
MObject Gamma::aOutColor;

#define MAKE_INPUT(attr)								\
 CHECK_MSTATUS ( attr.setKeyable(true) );  			 	\
 CHECK_MSTATUS ( attr.setStorable(true) );				\
 CHECK_MSTATUS ( attr.setReadable(true) );  			\
 CHECK_MSTATUS ( attr.setWritable(true) );

#define MAKE_OUTPUT(attr)								\
  CHECK_MSTATUS ( attr.setKeyable(false) ); 			\
  CHECK_MSTATUS ( attr.setStorable(false) );			\
  CHECK_MSTATUS ( attr.setReadable(true) );  			\
  CHECK_MSTATUS ( attr.setWritable(false) );

//
// DESCRIPTION:
///////////////////////////////////////////////////////
void Gamma::postConstructor( )
{
	setMPSafe(true);
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
Gamma::Gamma()
{
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
Gamma::~Gamma()
{
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
void *Gamma::creator()
{
    return new Gamma();
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus Gamma::initialize()
{
    MFnNumericAttribute		nAttr; 

    // Input attributes

    aColor = nAttr.createColor( "color", "c" );
    MAKE_INPUT(nAttr);

	aGamma = nAttr.createPoint( "gamma", "g" );
    MAKE_INPUT(nAttr);
	CHECK_MSTATUS ( nAttr.setDefault(1.f, 1.f, 1.f) );

	// Output attributes

    aOutColor= nAttr.createColor( "outColor", "oc" );
    MAKE_OUTPUT(nAttr);

	//  Add attributes to the node database.
    CHECK_MSTATUS ( addAttribute(aColor) );
    CHECK_MSTATUS ( addAttribute(aGamma) );
    CHECK_MSTATUS ( addAttribute(aOutColor) );

    // All input affect the output color
    CHECK_MSTATUS ( attributeAffects( aColor, aOutColor ));
    CHECK_MSTATUS ( attributeAffects( aGamma, aOutColor ));

    return MS::kSuccess;
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus Gamma::compute(const MPlug &plug, MDataBlock &block) 
{
    if ((plug != aOutColor) && (plug.parent() != aOutColor))
		return MS::kUnknownParameter;

    MFloatVector & icol = block.inputValue( aColor ).asFloatVector();
    MFloatVector & igam = block.inputValue( aGamma ).asFloatVector();

    MDataHandle och = block.outputValue( aOutColor );
    MFloatVector & ocol = och.asFloatVector();
    ocol[0]= powf(icol[0], 1.f/igam[0]);
    ocol[1]= powf(icol[1], 1.f/igam[1]);
    ocol[2]= powf(icol[2], 1.f/igam[2]);
    och.setClean();

    return MS::kSuccess;
}


//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus initializePlugin( MObject obj )
{
   const MString UserClassify( "utility/color" );

   MFnPlugin plugin( obj, PLUGIN_COMPANY, "4.5", "Any");
   CHECK_MSTATUS ( plugin.registerNode( "gammaNode", Gamma::id, 
                         Gamma::creator, Gamma::initialize,
                         MPxNode::kDependNode, &UserClassify ) );

   return MS::kSuccess;
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus uninitializePlugin( MObject obj )
{
   MFnPlugin plugin( obj );
   CHECK_MSTATUS ( plugin.deregisterNode( Gamma::id ) );

   return MS::kSuccess;
}
