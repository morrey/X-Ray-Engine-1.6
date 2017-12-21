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
//
// Original Author:    XCW
//
//

#ifndef   MDTLIGHT_H
#define   MDTLIGHT_H

int	add_AmbientLight( MObject, MObject );
int	add_DirectionLight( MObject, MObject );
int	add_PointLight( MObject, MObject );
int	add_SpotLight( MObject, MObject );
MObject is_LightGroup( MObject );
int addTransformLight( MObject, MObject );

#endif // MDTLIGHT_H

