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

#include <maya/MFnPlugin.h>
#include <maya/MIOStream.h>
#include <maya/MSceneMessage.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MStringResource.h>
#include <maya/MStringResourceId.h>

//nodes that need to be registered
#include "GLSLShaderNode.h"
#include "fxManagerCmd.h"
//#include "fxVector.h"

#include "AshliShaderStrings.h"

//shader interface for configuration parameters
#include "Shader.h"

#include <stdlib.h>

#include <maya/MHWShaderSwatchGenerator.h>
#include <maya/MHardwareRenderer.h>
#include <maya/MGeometryData.h>
#include <maya/MImage.h>

//
// static variables for holding the callback IDs
//
MCallbackId openCallback;
MCallbackId importCallback;
MCallbackId referenceCallback;

static MStatus registerMStringResources(void)
{
	MStringResource::registerString(rGLSLShaderNodeFailedResourceContext);
	MStringResource::registerString(rGLSLShaderNodeFailedLoadShader);
	MStringResource::registerString(rGLSLShaderNodeAshliFailedFindExtensions);
	MStringResource::registerString(rGLSLShaderNodeFailedAddAttribute);
	MStringResource::registerString(rGLSLShaderNodeFailedDestroyAttribute);
	return MS::kSuccess;
}

MStatus initializePlugin( MObject obj )
//
//	Description:
//		this method is called when the plug-in is loaded into Maya.  It 
//		registers all of the services that this plug-in provides with 
//		Maya.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{ 
	MStatus   status;
    const char *sm3;

    if ( NULL != (sm3 = getenv("ASHLI_SM3_SUPPORT"))) {
      if (strcmp( sm3, "0") != 0)
        shader::sSupportSM3 = true;
    }

	const MString& swatchName =	MHWShaderSwatchGenerator::initialize();

    MString swatchClassification;

	// Allow an environment variable to override usage of swatch
	// rendering.
	const char *ashliEnvVar = getenv("ASHLI_SWATCH_RENDERING");
#ifdef WIN32 
  	if (!ashliEnvVar)
  		swatchClassification = ":swatch/" + swatchName;
	else
	{
		if ( 0 != strcmp(ashliEnvVar,"0") )
			swatchClassification = ":swatch/" + swatchName;
	}
#else
	if ( ashliEnvVar && ( 0 != strcmp( ashliEnvVar, "0") ) )
	{
		swatchClassification = ":swatch/" + swatchName;
	}
#endif
  
  	const MString UserClassify( "shader/surface/utility/" + swatchClassification );
	MFnPlugin plugin( obj, "ATI", "6.5", "Any");

	//handle info banner

	status = plugin.registerUIStrings(registerMStringResources, "AshliShaderInitStrings");
	if (!status) {
		status.perror("registerUIStrings");
		return status;
	}

	// Add plug-in feature registration here
	//

    //register the shader node
	CHECK_MSTATUS( plugin.registerNode("AshliShader", glslShaderNode::sId, glslShaderNode::creator, glslShaderNode::initialize,
		MPxNode::kHwShaderNode, &UserClassify));

    //register a helper command for querying shader information
    plugin.registerCommand( "effectManager", fxManagerCmd::creator, fxManagerCmd::mySyntax); 

	//handle scene callback registration (on load, on save, etc)
    openCallback = MSceneMessage::addCallback(MSceneMessage::kAfterOpen, glslShaderNode::rejigShaders);
    importCallback = MSceneMessage::addCallback(MSceneMessage::kAfterImport, glslShaderNode::rejigShaders);
    referenceCallback = MSceneMessage::addCallback(MSceneMessage::kAfterReference, glslShaderNode::rejigShaders);
 
	return status;
}

MStatus uninitializePlugin( MObject obj )
//
//	Description:
//		this method is called when the plug-in is unloaded from Maya. It 
//		deregisters all of the services that it was providing.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{
	MStatus   status;
	MFnPlugin plugin( obj );

	//disconnect callbacks

	// Add plug-in feature deregistration here
	//
    MSceneMessage::removeCallback( openCallback);
    MSceneMessage::removeCallback( importCallback);
    MSceneMessage::removeCallback( referenceCallback);

	//deregister the shader node
	CHECK_MSTATUS(plugin.deregisterNode(glslShaderNode::sId));

	//deregister any additional commands

	return status;
}


