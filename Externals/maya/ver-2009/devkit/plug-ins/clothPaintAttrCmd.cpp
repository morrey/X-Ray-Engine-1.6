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

// PLUGIN NAME: clothPaintAttrCmd v1.0
// FILE   Name: clothPaintAttrCmd.cpp

// DESCRIPTION:   This MEL command has no flags, takes two string arguments and returns a double array.
//				  First and second argument indicate cloth mesh node and cloth paint attribute respectively.
//
// USAGE      :	  Command   :  ClothPaintAttr
//				  argument1 :  cloth mesh Node
//				  argument2 :  cloth paint attribute name (e.g. density, scale, bendRate, bendResistance, 
//							   stretchResistance, shearresistance, airDamping, clothDamping, clothFriction,
//							   thickness, thicknessForce, staticFriction, dynamicFriction and bendAngle.
//
// Example	  :   setAttr clothShape1.densityWeights -type doubleArray 33 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ;
//                ClothPaintAttr clothShape1 densityWeights
//                //Result: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 //

// AUTHOR     :   Raja.T.
// TESTED ON  :   Windows/Irix/Linux (WIL)

#include <maya/MFnPlugin.h>
#include <maya/MArgList.h>
#include <maya/MGlobal.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include "clothPaintAttrCmd.h"


////////////////////////////////////////////////////////////////////////
//
// Description: Constructor.
// Use: public
////////////////////////////////////////////////////////////////////////
ClothPaintAttrCommand::ClothPaintAttrCommand()
{

}

////////////////////////////////////////////////////////////////////////
//
// Description: Destructor.
// Use: public
////////////////////////////////////////////////////////////////////////
ClothPaintAttrCommand::~ClothPaintAttrCommand()
{

}

////////////////////////////////////////////////////////////////////////
//
// Description: Constructs a ClothPaintAttrCommand
// Use: public
////////////////////////////////////////////////////////////////////////
void* ClothPaintAttrCommand::creator()

{
	return new ClothPaintAttrCommand;
}

////////////////////////////////////////////////////////////////////////
//
// Description:  Return whether the command is undoable or not.  
// Use: public
////////////////////////////////////////////////////////////////////////
bool ClothPaintAttrCommand::isUndoable() const
{
   return false;
}

////////////////////////////////////////////////////////////////////////
//
// Description:  Perform the action of the command.
// Use: public
////////////////////////////////////////////////////////////////////////
MStatus ClothPaintAttrCommand::doIt(const MArgList& args)
{
	//Checking for Cloth Plug-in.
	MString pluginCheck = "pluginInfo -q -l CpClothPlugin.mll";
	int pluginResult;
	MGlobal::executeCommand(pluginCheck,pluginResult);
	if(pluginResult != 1)
	{
	  displayError("\"CpClothPlugin\" should be loaded to use this Plug-in!");
      return MS::kFailure;
	}
	
	//   PARSING

   //Error message if number of arguments are not equal to two	
   MString nodeName[2];
   if (!args.length() || args.length() != 2)
   {
	  displayError("Cloth Mesh node and Cloth paint attribute name must be specified as\n          Command's first and second argument respectively!");
      return MS::kFailure;
   }
   else
   {
      nodeName[0] = args.asString(0);
	  nodeName[1] = args.asString(1);
   }

   // PARSING FIRST ARGUMENT
   

   bool isFirstArg = false;
   bool isSecondArg = false;
 

   MString clothMesh = "isClothMesh "+ nodeName[0];
   int result;
   MGlobal::executeCommand(clothMesh, result);
   if(result == 1)
   {
		isFirstArg = true;
   }

   // PARSING SECOND ARGUMENT	
   
   if(   nodeName[1] == "bendAngle"              ||		nodeName[1] == "densityWeights"				||
		 nodeName[1] == "scaleWeights"           ||		nodeName[1] == "bendRateWeights"			||
		 nodeName[1] == "thicknessWeights"       ||		nodeName[1] == "airDampingWeights"			||
		 nodeName[1] == "clothDampingWeights"    ||		nodeName[1] == "clothFrictionWeights"		||
		 nodeName[1] == "staticFrictionWeights"  ||		nodeName[1] == "thicknessForceWeights"		||
		 nodeName[1] == "bendResistanceWeights"  ||		nodeName[1] == "dynamicFrictionWeights"		||
		 nodeName[1] == "shearResistanceWeights" ||		nodeName[1] == "stretchResistanceWeights")
   {
		isSecondArg = true;
   }

   //Error message if both arguments are not proper.
   if(isFirstArg == false && isSecondArg == false)
   {
	   displayError("Cloth Mesh node and Cloth paint attribute name must be specified as\n          Command's first and second argument respectively!");
	   return MS::kFailure;
   }
   //Error message if second argument is not proper.
   else if(isFirstArg == true && isSecondArg == false)
   {
	   displayError("A cloth paint attribute name must be specified as command's second argument!");
	   return MS::kFailure;
   }
   //Error message if first argument is not proper.
   else if(isFirstArg == false && isSecondArg == true)
   {
	    displayError("A cloth Mesh node must be specified as command's first argument!");
		return MS::kFailure;
   }
   
   //  STORE CLOTH MESH NODE
   MSelectionList nodeList;
   nodeList.add(nodeName[0]);
   MObject clothNode;
   nodeList.getDependNode(0, clothNode);

   //  GET DOUBLE ARRAY 		
   MFnDependencyNode fnDN(clothNode);
   MPlug paintAttrPlug = fnDN.findPlug(nodeName[1]); 
   MObject doubleArrayData; 
   paintAttrPlug.getValue(doubleArrayData); 
   MFnDoubleArrayData fnDAD(doubleArrayData); 
   MDoubleArray finalArray = fnDAD.array();

    // SET RESULT
    setResult(finalArray);
    return MS::kSuccess;
}

// Initialize Plugin
MStatus initializePlugin(MObject obj)
{
   
   MStatus status;
   MFnPlugin plugin(obj, PLUGIN_COMPANY, MGlobal::mayaVersion().asChar(), "Any");

   //Register the plugin command.
   status = plugin.registerCommand("ClothPaintAttr", ClothPaintAttrCommand::creator);
   if (!status)
   {
      status.perror("registerCommand");
      return status;
   }

   return status;
}


// Uninitialize Plugin
MStatus uninitializePlugin(MObject obj)
{
   MStatus status;
   MFnPlugin plugin(obj);

   status = plugin.deregisterCommand("ClothPaintAttr");
   if (!status)
   {
      status.perror("deregisterCommand");
      return status;
   }

   return status;
}
