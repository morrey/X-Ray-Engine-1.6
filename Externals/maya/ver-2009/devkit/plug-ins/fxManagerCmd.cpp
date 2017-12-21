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
//
// fxManagerCmd.cpp
//
//  This file provides the implementation for the effectManager command.
// This command is useful for querying additional information from the
// shader. Presently, it only supportes listing of the shader text to 
// aid in debugging.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <maya/MArgDatabase.h>
#include <maya/MGlobal.h>

#include "fxManagerCmd.h"

//
// fxManagerCmd::doIt
//
//  This is the function used to invoke the command. The
// command is not undoable and it does not change any state,
// so it does not use the method to call back throught redoIt.
//////////////////////////////////////////////////////////////////////
MStatus fxManagerCmd::doIt( const MArgList &args) {
  MArgDatabase argData( syntax(), args);
  MString nodeName;
  glslShaderNode *node = NULL;

  //check to see if we have a node
  if (argData.isFlagSet( "-n")) {
    argData.getFlagArgument( "-n", 0, nodeName);
    node = glslShaderNode::findNodeByName(nodeName);
    if (!node) {
      MGlobal::displayError( MString("Node '") +nodeName +"' does not exist");
      return MStatus::kFailure;
    }
  }

  //check if we are in list shader mode
  if (argData.isFlagSet( "-ls")) {
    int pass;
    //are we listing a vertex shader
    if (argData.isFlagSet( "-vs")) {
      argData.getFlagArgument( "-vs", 0, pass);
      if (!node->printVertexShader(pass)) {
        MGlobal::displayError( MString("No vertex shader available for pass ") + pass);
        return MStatus::kFailure;
      }
    }
    //are we listing a vertex shader
    if (argData.isFlagSet( "-ps")) {
      argData.getFlagArgument( "-ps", 0, pass);
      if (!node->printPixelShader(pass)) {
        MGlobal::displayError( MString("No pixel shader available for pass ") + pass);
        return MStatus::kFailure;
      }
    }
  }
  

  return MStatus::kSuccess;
}

//
//  There is never anything to undo.
//////////////////////////////////////////////////////////////////////
MStatus fxManagerCmd::undoIt(){
  return MStatus::kSuccess;
}

//
//  There is never really anything to redo.
//////////////////////////////////////////////////////////////////////
MStatus fxManagerCmd::redoIt(){
  return MStatus::kSuccess;
}

//
//
//////////////////////////////////////////////////////////////////////
bool fxManagerCmd::isUndoable() const{
  return false;
}

//
//
//////////////////////////////////////////////////////////////////////
bool fxManagerCmd::hasSyntax() const {
  return true;
}

//
//
//////////////////////////////////////////////////////////////////////
MSyntax fxManagerCmd::mySyntax() {
  MSyntax syntax;

  syntax.addFlag( "-ls", "-listShader");
  syntax.addFlag( "-ps", "-pixelShader", MSyntax::kLong);
  syntax.addFlag( "-vs", "-vertexShader", MSyntax::kLong);
  syntax.addFlag( "-n", "-node", MSyntax::kString);

  return syntax;
}

//
//
//////////////////////////////////////////////////////////////////////
bool fxManagerCmd::isHistoryOn() const {
  //what is this supposed to do?
  return false;
}

//
//
//////////////////////////////////////////////////////////////////////
MString fxManagerCmd::commandString() const {
  return MString();
}

//
//
//////////////////////////////////////////////////////////////////////
MStatus fxManagerCmd::setHistoryOn( bool state ){
  //ignore it for now
  return MStatus::kSuccess;
}

//
//
//////////////////////////////////////////////////////////////////////
MStatus fxManagerCmd::setCommandString( const MString &str) {
  //ignore it for now
  return MStatus::kSuccess;
}

