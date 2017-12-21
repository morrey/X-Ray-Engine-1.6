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
// FILE   Name: clothPaintAttrCmd.h

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

#ifndef  _CLOTH_PAINTATTR_COMMAND_
#define  _CLOTH_PAINTATTR_COMMAND_

#include <maya/MDagPathArray.h>
#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MPxCommand.h>
#include <maya/MSelectionList.h>
#include <maya/MDGModifier.h>
#include <maya/MMessage.h>
#include <maya/MStringArray.h>
#include <maya/MTypeId.h>
#include <maya/MSyntax.h>



//////////////////////////////////////////////////////////////////////////////
//
//  Class: ClothPaintAttrCommand
//
//////////////////////////////////////////////////////////////////////////////

class ClothPaintAttrCommand : public MPxCommand
{
   public:
      
	  ClothPaintAttrCommand(); //CONSTRUCTOR
      virtual ~ClothPaintAttrCommand(); //DESTRUCTOR

      static void* creator();
      bool isUndoable() const;
      
	  MStatus doIt(const MArgList&);
};

#endif
