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

#include <stdio.h>

#include <OpenGLViewportRenderer.h>

#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MFnPlugin.h>

#include <stdio.h>

///////////////////////////////////////////////////
//
// Plug-in functions
//
///////////////////////////////////////////////////

static OpenGLViewportRenderer *g_OpenGLRenderer = 0;

MStatus initializePlugin( MObject obj )
{ 
	MStatus   status = MStatus::kFailure;

	MFnPlugin plugin( obj, PLUGIN_COMPANY, "1.0", "Any");

	// Register the renderer
	//
	g_OpenGLRenderer = new OpenGLViewportRenderer();
	if (g_OpenGLRenderer)
	{
		status = g_OpenGLRenderer->registerRenderer();
		if (status != MStatus::kSuccess)
		{
			status.perror("Failed to register OpenGL renderer properly.");
		}
	}
	return status;
}

MStatus uninitializePlugin( MObject obj )
{
	MStatus   status = MStatus::kSuccess;

	// Deregister the renderer
	//
	if (g_OpenGLRenderer)
	{
		status = g_OpenGLRenderer->deregisterRenderer();
		if (status != MStatus::kSuccess)
		{
			status.perror("Failed to deregister OpenGL renderer properly.");
		}
	}
	g_OpenGLRenderer = 0;
	return status;
}

