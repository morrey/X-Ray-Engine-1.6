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
#ifndef FX_MANAGER_CMD_H
#define FX_MANAGER_CMD_H

#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>

#include "GLSLShaderNode.h"

class fxManagerCmd : public MPxCommand {
  public:
    fxManagerCmd() {};
    ~fxManagerCmd() {};

    virtual MStatus doIt( const MArgList &args );
    virtual MStatus undoIt();
 
    virtual MStatus redoIt();
 
    virtual bool isUndoable() const;
 
    virtual bool hasSyntax() const;
 
    static MSyntax mySyntax();

    static void* creator() {return new fxManagerCmd;};
 
    bool isHistoryOn() const;
 
    MString commandString() const;
 
    MStatus setHistoryOn( bool state );
 
    MStatus setCommandString( const MString & );
};



#endif //FX_MANAGER_CMD_H

