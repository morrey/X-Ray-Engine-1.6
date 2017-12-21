#ifndef OpenGLViewportRenderer_h_
#define OpenGLViewportRenderer_h_

#include <maya/MViewportRenderer.h>

class MDagPath;
class MBoundingBox;

//
// Sample plugin viewport renderer using the OpenGL API.
//
class OpenGLViewportRenderer : public MViewportRenderer
{
public:
	OpenGLViewportRenderer();
	virtual ~OpenGLViewportRenderer();

	// Required virtual overrides from MViewportRenderer
	//
	virtual	MStatus	initialize();
	virtual	MStatus	uninitialize();
	virtual MStatus	render( const MRenderingInfo &renderInfo );
	virtual bool	nativelySupports( MViewportRenderer::RenderingAPI api, 
										  float version );
	virtual bool	override( MViewportRenderer::RenderingOverride override );

protected:
	bool			drawSurface( const MDagPath &dagPath, bool active, bool templated );
	bool			drawBounds( const MDagPath &dagPath,
								const MBoundingBox &box);
	bool			setupLighting();
	bool			renderToTarget( const MRenderingInfo &renderInfo );

	RenderingAPI	m_API;		// Rendering API
	float			m_Version;	// OpenGL version number as float.
};

#endif /* OpenGLViewportRenderer_h_ */

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

