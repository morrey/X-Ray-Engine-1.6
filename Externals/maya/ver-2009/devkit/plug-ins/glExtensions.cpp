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
#include <stdlib.h>
#include <string.h>

#include "glExtensions.h"

#include <maya/MTypes.h>
#include <maya/MHWShaderSwatchGenerator.h>
#include <maya/MHardwareRenderer.h>
#include <maya/MGlobal.h>

bool extensionsAvailable = false;
bool glInitialised = false;

/* GLSL extensions */

PFNGLDELETEOBJECTARBPROC                    glDeleteObject           = NULL;
PFNGLGETHANDLEARBPROC                       glGetHandle              = NULL;
PFNGLDETACHOBJECTARBPROC                    glDetachObject           = NULL;
PFNGLCREATESHADEROBJECTARBPROC              glCreateShaderObject     = NULL;
PFNGLSHADERSOURCEARBPROC                    glShaderSource           = NULL;
PFNGLCOMPILESHADERARBPROC                   glCompileShader          = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC             glCreateProgramObject    = NULL;
PFNGLATTACHOBJECTARBPROC                    glAttachObject           = NULL;
PFNGLLINKPROGRAMARBPROC                     glLinkProgram            = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC                glUseProgramObject       = NULL;
PFNGLVALIDATEPROGRAMARBPROC                 glValidateProgram        = NULL;
PFNGLUNIFORM1FARBPROC                       glUniform1f              = NULL;
PFNGLUNIFORM2FARBPROC                       glUniform2f              = NULL;
PFNGLUNIFORM3FARBPROC                       glUniform3f              = NULL;
PFNGLUNIFORM4FARBPROC                       glUniform4f              = NULL;
PFNGLUNIFORM1IARBPROC                       glUniform1i              = NULL;
PFNGLUNIFORM2IARBPROC                       glUniform2i              = NULL;
PFNGLUNIFORM3IARBPROC                       glUniform3i              = NULL;
PFNGLUNIFORM4IARBPROC                       glUniform4i              = NULL;
PFNGLUNIFORM1FVARBPROC                      glUniform1fv             = NULL;
PFNGLUNIFORM2FVARBPROC                      glUniform2fv             = NULL;
PFNGLUNIFORM3FVARBPROC                      glUniform3fv             = NULL;
PFNGLUNIFORM4FVARBPROC                      glUniform4fv             = NULL;
PFNGLUNIFORM1IVARBPROC                      glUniform1iv             = NULL;
PFNGLUNIFORM2IVARBPROC                      glUniform2iv             = NULL;
PFNGLUNIFORM3IVARBPROC                      glUniform3iv             = NULL;
PFNGLUNIFORM4IVARBPROC                      glUniform4iv             = NULL;
PFNGLUNIFORMMATRIX2FVARBPROC                glUniformMatrix2fv       = NULL;
PFNGLUNIFORMMATRIX3FVARBPROC                glUniformMatrix3fv       = NULL;
PFNGLUNIFORMMATRIX4FVARBPROC                glUniformMatrix4fv       = NULL;
PFNGLGETOBJECTPARAMETERFVARBPROC            glGetObjectParameterfv   = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC            glGetObjectParameteriv   = NULL;
PFNGLGETINFOLOGARBPROC                      glGetInfoLog             = NULL;
PFNGLGETATTACHEDOBJECTSARBPROC              glGetAttachedObjects     = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC              glGetUniformLocation     = NULL;
PFNGLGETACTIVEUNIFORMARBPROC                glGetActiveUniform       = NULL;
PFNGLGETUNIFORMFVARBPROC                    glGetUniformfv           = NULL;
PFNGLGETUNIFORMIVARBPROC                    glGetUniformiv           = NULL;
PFNGLGETSHADERSOURCEARBPROC                 glGetShaderSource        = NULL;

PFNGLBINDATTRIBLOCATIONARBPROC       glBindAttribLocation     = NULL;
PFNGLGETACTIVEATTRIBARBPROC          glGetActiveAttrib        = NULL;
PFNGLGETATTRIBLOCATIONARBPROC        glGetAttribLocation      = NULL;

PFNGLVERTEXATTRIB1SARBPROC                   glVertexAttrib1s = NULL;
PFNGLVERTEXATTRIB1FARBPROC                   glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1DARBPROC                   glVertexAttrib1d = NULL;
PFNGLVERTEXATTRIB2SARBPROC                   glVertexAttrib2s = NULL;
PFNGLVERTEXATTRIB2FARBPROC                   glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2DARBPROC                   glVertexAttrib2d = NULL;
PFNGLVERTEXATTRIB3SARBPROC                   glVertexAttrib3s = NULL;
PFNGLVERTEXATTRIB3FARBPROC                   glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3DARBPROC                   glVertexAttrib3d = NULL;
PFNGLVERTEXATTRIB4SARBPROC                   glVertexAttrib4s = NULL;
PFNGLVERTEXATTRIB4FARBPROC                   glVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4DARBPROC                   glVertexAttrib4d = NULL;
PFNGLVERTEXATTRIB4NUBARBPROC                 glVertexAttrib4Nub = NULL;
PFNGLVERTEXATTRIB1SVARBPROC                  glVertexAttrib1sv = NULL;
PFNGLVERTEXATTRIB1FVARBPROC                  glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB1DVARBPROC                  glVertexAttrib1dv = NULL;
PFNGLVERTEXATTRIB2SVARBPROC                  glVertexAttrib2sv = NULL;
PFNGLVERTEXATTRIB2FVARBPROC                  glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB2DVARBPROC                  glVertexAttrib2dv = NULL;
PFNGLVERTEXATTRIB3SVARBPROC                  glVertexAttrib3sv = NULL;
PFNGLVERTEXATTRIB3FVARBPROC                  glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB3DVARBPROC                  glVertexAttrib3dv = NULL;
PFNGLVERTEXATTRIB4SVARBPROC                  glVertexAttrib4sv = NULL;
PFNGLVERTEXATTRIB4FVARBPROC                  glVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIB4DVARBPROC                  glVertexAttrib4dv = NULL;
PFNGLVERTEXATTRIB4IVARBPROC                  glVertexAttrib4iv = NULL;
PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bv = NULL;
PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usv = NULL;
PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubv = NULL;
PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uiv = NULL;
PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4Nbv = NULL;
PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4Nsv = NULL;
PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4Niv = NULL;
PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4Nubv = NULL;
PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4Nusv = NULL;
PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4Nuiv = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArray = NULL;

PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC glGetVertexAttribPointerv = NULL;

PFNGLPROGRAMSTRINGARBPROC glProgramStringARB = NULL;
PFNGLBINDPROGRAMARBPROC glBindProgramARB = NULL;
PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB = NULL;
PFNGLGENPROGRAMSARBPROC glGenProgramsARB = NULL;
PFNGLPROGRAMENVPARAMETER4DARBPROC glProgramEnvParameter4dARB = NULL;
PFNGLPROGRAMENVPARAMETER4DVARBPROC glProgramEnvParameter4dvARB = NULL;
PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB = NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC glProgramEnvParameter4fvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC glProgramLocalParameter4dARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glProgramLocalParameter4dvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC glProgramLocalParameter4fARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC glGetProgramEnvParameterdvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC glGetProgramEnvParameterfvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glGetProgramLocalParameterdvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glGetProgramLocalParameterfvARB = NULL;
PFNGLGETPROGRAMIVARBPROC glGetProgramivARB = NULL;;
PFNGLGETPROGRAMSTRINGARBPROC glGetProgramStringARB = NULL;
PFNGLISPROGRAMARBPROC glIsProgramARB = NULL;

#ifdef WIN32
PFNGLACTIVETEXTUREPROC       glActiveTexture = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = NULL;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = NULL;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = NULL;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = NULL;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = NULL;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = NULL;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = NULL;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = NULL;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = NULL;
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = NULL;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = NULL;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = NULL;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = NULL;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = NULL;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = NULL;
PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = NULL;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = NULL;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = NULL;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = NULL;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = NULL;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = NULL;
PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = NULL;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = NULL;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = NULL;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = NULL;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = NULL;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = NULL;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = NULL;
#endif

#ifdef WIN32
PFNGLTEXIMAGE3DEXTPROC glTexImage3D = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;
#endif

/* Point Parameters */
PFNGLPOINTPARAMETERFPROC glPointParameterf = NULL;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = NULL;

/* Blend Equation */
#ifdef WIN32
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
#endif

/* Secondary Color */
PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b = NULL;
PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv = NULL;
PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d = NULL;
PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv = NULL;
PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f = NULL;
PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv = NULL;
PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i = NULL;
PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv = NULL;
PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s = NULL;
PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv = NULL;
PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub = NULL;
PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv = NULL;
PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui = NULL;
PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv = NULL;
PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us = NULL;
PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv = NULL;
PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer = NULL;

//Extension support
bool glShadingLanguageSupport = false;
bool glMultiTextureSupport = false;
bool glTexture3DSupport = false;
bool glAsmProgramSupport = false;
bool glPointParametersSupport = false;
bool glBlendEquationSupport = false;
bool glSecondaryColorSupport = false;
bool glTextureNonPowerOfTwo = false;

/* Get Function pointer safely */
#ifdef WIN32
#define SAFE_GET_PROC( type, func, fail)     \
  func = (type) wglGetProcAddress( #func);    \
  fail &= (func != NULL);
#define SAFE_GET_PROC_ARB( type, func, fail)     \
  func = (type) wglGetProcAddress( #func "ARB");    \
  fail &= (func != NULL);
#define SAFE_GET_PROC_EXT( type, func, fail)     \
  func = (type) wglGetProcAddress( #func "EXT");    \
  fail &= (func != NULL);
#else


// We need to always use glXGetProcAddressARB for now as
// glXGetProcAddress is not guaranteed to exist.
#if defined(RedHat8_)
extern "C" void (*glXGetProcAddressARB(const GLubyte *procName))( void );
#endif

#define useGetProcAddress ::glXGetProcAddressARB

#define SAFE_GET_PROC( type, func, fail)     \
  func = (type) useGetProcAddress( (const GLubyte*) #func);    \
  fail &= (func != NULL);
#define SAFE_GET_PROC_ARB( type, func, fail)     \
  func = (type) useGetProcAddress( (const GLubyte*) #func "ARB");    \
  fail &= (func != NULL);
#define SAFE_GET_PROC_EXT( type, func, fail)     \
  func = (type) useGetProcAddress( (const GLubyte*) #func "EXT");    \
  fail &= (func != NULL);
#endif //WIN32

/* Determine if a particular extension is supported */
bool extensionSupported(const char* string, const char *extension) {
  const char *start;
  char *where, *terminator;
  
  where = strchr((char *)extension, ' ');
  if (where || *extension == '\0')
    return false;
  
  start = string;
  for (;;) {
    where = strstr( (char *)start, (char *)extension);
    if (!where)
      break;
    terminator = where + strlen(extension);
    if (where == start || *(where - 1) == ' ') {
      if (*terminator == ' ' || *terminator == '\0') {
        return true;
      }
    }
    start = terminator;
  }
  return false;
}

/* Get GL version as an integer with xxyy as major/minor version */
int GLversion() {
  int majorVersion;
  int minorVersion;
  const char* version;
   
  version = (const char*)glGetString(GL_VERSION);
  majorVersion = atoi(version);
  version = strchr( version, '.');
  version++;
  minorVersion = atoi(version);

  //minor hack to prevent overflow
  minorVersion %= 100;

  return majorVersion*100 + minorVersion;
}

bool InitializeExtensions() {

	// If we've already initialised, we're done
	if( glInitialised)
		return extensionsAvailable;
	glInitialised = true;

	// Make sure we have a Maya OpenGL context setup
	// The hardware renderer is the most reliable one to try
	MHardwareRenderer *pRenderer = MHardwareRenderer::theRenderer();

	if (pRenderer) {
		const MString & backEndStr = pRenderer->backEndString();
		unsigned int width = 64, height = 64;
		MStatus status = pRenderer->makeSwatchContextCurrent( backEndStr,
			width, 
			height );
		if (status != MStatus::kSuccess) {
			MGlobal::displayError(MString("Unqualified video card : Offscreen contexts not supported. Ashli Shader plugin will not be loaded."));
			return false;
		}
	}
	else {
		MGlobal::displayError(MString("Unqualified video card. Ashli Shader plugin will not be loaded."));
		return false;
	}

  int ver = GLversion();
  const char *extensions = (const char*)glGetString(GL_EXTENSIONS);


  if ( 0) { //turning off looking for GL 2.0 versions right now 
    //query for the OpenGL 2.0 version of the entrypoints

    //
    //This section needs to be rewritten to properly handle the minor name mangling
    //that occurred in promoting the extensions to core. Lots of entrypoints lost
    //"object" from the name, and some were forked to deal specifically with shaders
    //and programs.
    //

    glShadingLanguageSupport = true;
    glMultiTextureSupport = true;
    glTexture3DSupport = true;

    SAFE_GET_PROC( PFNGLDELETEOBJECTARBPROC, glDeleteObject, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETHANDLEARBPROC, glGetHandle, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLDETACHOBJECTARBPROC, glDetachObject, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLCREATESHADEROBJECTARBPROC, glCreateShaderObject, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLSHADERSOURCEARBPROC, glShaderSource, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLCOMPILESHADERARBPROC, glCompileShader, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLCREATEPROGRAMOBJECTARBPROC, glCreateProgramObject, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLATTACHOBJECTARBPROC, glAttachObject, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLLINKPROGRAMARBPROC, glLinkProgram, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUSEPROGRAMOBJECTARBPROC, glUseProgramObject, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVALIDATEPROGRAMARBPROC, glValidateProgram, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM1FARBPROC, glUniform1f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM2FARBPROC, glUniform2f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM3FARBPROC, glUniform3f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM4FARBPROC, glUniform4f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM1IARBPROC, glUniform1i, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM2IARBPROC, glUniform2i, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM3IARBPROC, glUniform3i, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM4IARBPROC, glUniform4i, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM1FVARBPROC, glUniform1fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM2FVARBPROC, glUniform2fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM3FVARBPROC, glUniform3fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM4FVARBPROC, glUniform4fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM1IVARBPROC, glUniform1iv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM2IVARBPROC, glUniform2iv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM3IVARBPROC, glUniform3iv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORM4IVARBPROC, glUniform4iv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORMMATRIX2FVARBPROC, glUniformMatrix2fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORMMATRIX3FVARBPROC, glUniformMatrix3fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLUNIFORMMATRIX4FVARBPROC, glUniformMatrix4fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETOBJECTPARAMETERFVARBPROC, glGetObjectParameterfv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETOBJECTPARAMETERIVARBPROC, glGetObjectParameteriv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETINFOLOGARBPROC, glGetInfoLog, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETATTACHEDOBJECTSARBPROC, glGetAttachedObjects, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETUNIFORMLOCATIONARBPROC, glGetUniformLocation, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETACTIVEUNIFORMARBPROC, glGetActiveUniform, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETUNIFORMFVARBPROC, glGetUniformfv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETUNIFORMIVARBPROC, glGetUniformiv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETSHADERSOURCEARBPROC, glGetShaderSource, glShadingLanguageSupport);

    SAFE_GET_PROC( PFNGLBINDATTRIBLOCATIONARBPROC, glBindAttribLocation, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETACTIVEATTRIBARBPROC, glGetActiveAttrib, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETATTRIBLOCATIONARBPROC, glGetAttribLocation, glShadingLanguageSupport);

    SAFE_GET_PROC( PFNGLVERTEXATTRIB1SARBPROC, glVertexAttrib1s, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB1FARBPROC, glVertexAttrib1f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB1DARBPROC, glVertexAttrib1d, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB2SARBPROC, glVertexAttrib2s, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB2FARBPROC, glVertexAttrib2f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB2DARBPROC, glVertexAttrib2d, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB3SARBPROC, glVertexAttrib3s, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB3FARBPROC, glVertexAttrib3f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB3DARBPROC, glVertexAttrib3d, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4SARBPROC, glVertexAttrib4s, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4FARBPROC, glVertexAttrib4f, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4DARBPROC, glVertexAttrib4d, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NUBARBPROC, glVertexAttrib4Nub, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB1SVARBPROC, glVertexAttrib1sv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB1FVARBPROC, glVertexAttrib1fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB1DVARBPROC, glVertexAttrib1dv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB2SVARBPROC, glVertexAttrib2sv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB2FVARBPROC, glVertexAttrib2fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB2DVARBPROC, glVertexAttrib2dv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB3SVARBPROC, glVertexAttrib3sv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB3FVARBPROC, glVertexAttrib3fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB3DVARBPROC, glVertexAttrib3dv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4SVARBPROC, glVertexAttrib4sv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4FVARBPROC, glVertexAttrib4fv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4DVARBPROC, glVertexAttrib4dv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4IVARBPROC, glVertexAttrib4iv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4BVARBPROC, glVertexAttrib4bv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4USVARBPROC, glVertexAttrib4usv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4UBVARBPROC, glVertexAttrib4ubv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4UIVARBPROC, glVertexAttrib4uiv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NBVARBPROC, glVertexAttrib4Nbv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NSVARBPROC, glVertexAttrib4Nsv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NIVARBPROC, glVertexAttrib4Niv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NUBVARBPROC, glVertexAttrib4Nubv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NUSVARBPROC, glVertexAttrib4Nusv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIB4NUIVARBPROC, glVertexAttrib4Nuiv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLVERTEXATTRIBPOINTERARBPROC, glVertexAttribPointer, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLENABLEVERTEXATTRIBARRAYARBPROC, glEnableVertexAttribArray, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLDISABLEVERTEXATTRIBARRAYARBPROC, glDisableVertexAttribArray, glShadingLanguageSupport);

    SAFE_GET_PROC( PFNGLGETVERTEXATTRIBDVARBPROC, glGetVertexAttribdv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETVERTEXATTRIBFVARBPROC, glGetVertexAttribfv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETVERTEXATTRIBIVARBPROC, glGetVertexAttribiv, glShadingLanguageSupport);
    SAFE_GET_PROC( PFNGLGETVERTEXATTRIBPOINTERVARBPROC, glGetVertexAttribPointerv, glShadingLanguageSupport);


#ifdef WIN32
    SAFE_GET_PROC( PFNGLACTIVETEXTUREPROC, glActiveTexture, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s, glMultiTextureSupport);
    SAFE_GET_PROC( PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv, glMultiTextureSupport);
#endif

#ifdef WIN32
    SAFE_GET_PROC( PFNGLTEXIMAGE3DEXTPROC, glTexImage3D, glTexture3DSupport);
    SAFE_GET_PROC( PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D, glTexture3DSupport);
    SAFE_GET_PROC( PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D, glTexture3DSupport);
#endif
  }
  else {
    //look for the ARB extensions

    if ( extensionSupported( extensions, "GL_ARB_shader_objects") ) {
      glShadingLanguageSupport = true;

      SAFE_GET_PROC_ARB( PFNGLDELETEOBJECTARBPROC, glDeleteObject, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETHANDLEARBPROC, glGetHandle, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLDETACHOBJECTARBPROC, glDetachObject, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLCREATESHADEROBJECTARBPROC, glCreateShaderObject, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLSHADERSOURCEARBPROC, glShaderSource, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLCOMPILESHADERARBPROC, glCompileShader, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLCREATEPROGRAMOBJECTARBPROC, glCreateProgramObject, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLATTACHOBJECTARBPROC, glAttachObject, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLLINKPROGRAMARBPROC, glLinkProgram, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUSEPROGRAMOBJECTARBPROC, glUseProgramObject, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLVALIDATEPROGRAMARBPROC, glValidateProgram, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM1FARBPROC, glUniform1f, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM2FARBPROC, glUniform2f, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM3FARBPROC, glUniform3f, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM4FARBPROC, glUniform4f, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM1IARBPROC, glUniform1i, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM2IARBPROC, glUniform2i, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM3IARBPROC, glUniform3i, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM4IARBPROC, glUniform4i, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM1FVARBPROC, glUniform1fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM2FVARBPROC, glUniform2fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM3FVARBPROC, glUniform3fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM4FVARBPROC, glUniform4fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM1IVARBPROC, glUniform1iv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM2IVARBPROC, glUniform2iv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM3IVARBPROC, glUniform3iv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORM4IVARBPROC, glUniform4iv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORMMATRIX2FVARBPROC, glUniformMatrix2fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORMMATRIX3FVARBPROC, glUniformMatrix3fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLUNIFORMMATRIX4FVARBPROC, glUniformMatrix4fv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETOBJECTPARAMETERFVARBPROC, glGetObjectParameterfv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETOBJECTPARAMETERIVARBPROC, glGetObjectParameteriv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETINFOLOGARBPROC, glGetInfoLog, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETATTACHEDOBJECTSARBPROC, glGetAttachedObjects, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETUNIFORMLOCATIONARBPROC, glGetUniformLocation, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETACTIVEUNIFORMARBPROC, glGetActiveUniform, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETUNIFORMFVARBPROC, glGetUniformfv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETUNIFORMIVARBPROC, glGetUniformiv, glShadingLanguageSupport);
      SAFE_GET_PROC_ARB( PFNGLGETSHADERSOURCEARBPROC, glGetShaderSource, glShadingLanguageSupport);

      if ( extensionSupported( extensions, "GL_ARB_vertex_shader") ) {
        SAFE_GET_PROC_ARB( PFNGLBINDATTRIBLOCATIONARBPROC, glBindAttribLocation, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLGETACTIVEATTRIBARBPROC, glGetActiveAttrib, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLGETATTRIBLOCATIONARBPROC, glGetAttribLocation, glShadingLanguageSupport);

        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB1SARBPROC, glVertexAttrib1s, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB1FARBPROC, glVertexAttrib1f, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB1DARBPROC, glVertexAttrib1d, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB2SARBPROC, glVertexAttrib2s, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB2FARBPROC, glVertexAttrib2f, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB2DARBPROC, glVertexAttrib2d, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB3SARBPROC, glVertexAttrib3s, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB3FARBPROC, glVertexAttrib3f, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB3DARBPROC, glVertexAttrib3d, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4SARBPROC, glVertexAttrib4s, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4FARBPROC, glVertexAttrib4f, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4DARBPROC, glVertexAttrib4d, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NUBARBPROC, glVertexAttrib4Nub, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB1SVARBPROC, glVertexAttrib1sv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB1FVARBPROC, glVertexAttrib1fv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB1DVARBPROC, glVertexAttrib1dv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB2SVARBPROC, glVertexAttrib2sv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB2FVARBPROC, glVertexAttrib2fv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB2DVARBPROC, glVertexAttrib2dv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB3SVARBPROC, glVertexAttrib3sv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB3FVARBPROC, glVertexAttrib3fv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB3DVARBPROC, glVertexAttrib3dv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4SVARBPROC, glVertexAttrib4sv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4FVARBPROC, glVertexAttrib4fv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4DVARBPROC, glVertexAttrib4dv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4IVARBPROC, glVertexAttrib4iv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4BVARBPROC, glVertexAttrib4bv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4USVARBPROC, glVertexAttrib4usv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4UBVARBPROC, glVertexAttrib4ubv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4UIVARBPROC, glVertexAttrib4uiv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NBVARBPROC, glVertexAttrib4Nbv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NSVARBPROC, glVertexAttrib4Nsv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NIVARBPROC, glVertexAttrib4Niv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NUBVARBPROC, glVertexAttrib4Nubv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NUSVARBPROC, glVertexAttrib4Nusv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIB4NUIVARBPROC, glVertexAttrib4Nuiv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLVERTEXATTRIBPOINTERARBPROC, glVertexAttribPointer, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLENABLEVERTEXATTRIBARRAYARBPROC, glEnableVertexAttribArray, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLDISABLEVERTEXATTRIBARRAYARBPROC, glDisableVertexAttribArray, glShadingLanguageSupport);

        SAFE_GET_PROC_ARB( PFNGLGETVERTEXATTRIBDVARBPROC, glGetVertexAttribdv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLGETVERTEXATTRIBFVARBPROC, glGetVertexAttribfv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLGETVERTEXATTRIBIVARBPROC, glGetVertexAttribiv, glShadingLanguageSupport);
        SAFE_GET_PROC_ARB( PFNGLGETVERTEXATTRIBPOINTERVARBPROC, glGetVertexAttribPointerv, glShadingLanguageSupport);
      }
      else {
        //no vertex shader support
        glShadingLanguageSupport = false;
      }

      if ( extensionSupported( extensions, "GL_ARB_fragment_shader") ) {
        //nothing presently
      }
      else {
        //no fragment shader support
        glShadingLanguageSupport = false;
      }
      
    }

    if ( extensionSupported( extensions, "GL_ARB_vertex_program") && extensionSupported( extensions, "GL_ARB_fragment_program")) {
      glAsmProgramSupport = true;
      SAFE_GET_PROC( PFNGLPROGRAMSTRINGARBPROC, glProgramStringARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLBINDPROGRAMARBPROC, glBindProgramARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLDELETEPROGRAMSARBPROC, glDeleteProgramsARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGENPROGRAMSARBPROC, glGenProgramsARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMENVPARAMETER4DARBPROC, glProgramEnvParameter4dARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMENVPARAMETER4DVARBPROC, glProgramEnvParameter4dvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMENVPARAMETER4FARBPROC, glProgramEnvParameter4fARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMENVPARAMETER4FVARBPROC, glProgramEnvParameter4fvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMLOCALPARAMETER4DARBPROC, glProgramLocalParameter4dARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMLOCALPARAMETER4DVARBPROC, glProgramLocalParameter4dvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMLOCALPARAMETER4FARBPROC, glProgramLocalParameter4fARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLPROGRAMLOCALPARAMETER4FVARBPROC, glProgramLocalParameter4fvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGETPROGRAMENVPARAMETERDVARBPROC, glGetProgramEnvParameterdvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGETPROGRAMENVPARAMETERFVARBPROC, glGetProgramEnvParameterfvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC, glGetProgramLocalParameterdvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC, glGetProgramLocalParameterfvARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGETPROGRAMIVARBPROC, glGetProgramivARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLGETPROGRAMSTRINGARBPROC, glGetProgramStringARB, glAsmProgramSupport);
      SAFE_GET_PROC( PFNGLISPROGRAMARBPROC, glIsProgramARB, glAsmProgramSupport);
    }
    else {
      glAsmProgramSupport = false;
    }

    if ( ver >= 130) {
      glTexture3DSupport = true;
      glMultiTextureSupport = true;

#ifdef WIN32
      SAFE_GET_PROC( PFNGLACTIVETEXTUREPROC, glActiveTexture, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s, glMultiTextureSupport);
      SAFE_GET_PROC( PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv, glMultiTextureSupport);
#endif

#ifdef WIN32
      SAFE_GET_PROC( PFNGLTEXIMAGE3DEXTPROC, glTexImage3D, glTexture3DSupport);
      SAFE_GET_PROC( PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D, glTexture3DSupport);
      SAFE_GET_PROC( PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D, glTexture3DSupport);
#endif
    }
    else {
      
      if (extensionSupported( extensions, "GL_ARB_multitexture")) {
        glMultiTextureSupport = true;

#ifdef WIN32
        SAFE_GET_PROC_ARB( PFNGLACTIVETEXTUREPROC, glActiveTexture, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s, glMultiTextureSupport);
        SAFE_GET_PROC_ARB( PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv, glMultiTextureSupport);
#endif
      }

      if (extensionSupported( extensions, "GL_EXT_texture3D")) {
        glTexture3DSupport = true;
#ifdef WIN32
        SAFE_GET_PROC_EXT( PFNGLTEXIMAGE3DEXTPROC, glTexImage3D, glTexture3DSupport);
        SAFE_GET_PROC_EXT( PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D, glTexture3DSupport);
        SAFE_GET_PROC_EXT( PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D, glTexture3DSupport);
#endif
      }
    }

    //search for point parameters and Blend Equation
    if ( ver >= 140) {
      glPointParametersSupport = true;
      glBlendEquationSupport = true;
#ifndef WIN32
	  // Comment out temporarily to avoid crash on Linux.
	  glSecondaryColorSupport = false;
#endif
      SAFE_GET_PROC( PFNGLPOINTPARAMETERFPROC, glPointParameterf, glPointParametersSupport);
      SAFE_GET_PROC( PFNGLPOINTPARAMETERFVPROC, glPointParameterfv, glPointParametersSupport);

#ifdef WIN32
      SAFE_GET_PROC( PFNGLBLENDEQUATIONPROC, glBlendEquation, glBlendEquationSupport);
#endif

      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3BPROC, glSecondaryColor3b, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3BVPROC, glSecondaryColor3bv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3DPROC, glSecondaryColor3d, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3DVPROC, glSecondaryColor3dv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3FPROC, glSecondaryColor3f, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3FVPROC, glSecondaryColor3fv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3IPROC, glSecondaryColor3i, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3IVPROC, glSecondaryColor3iv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3SPROC, glSecondaryColor3s, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3SVPROC, glSecondaryColor3sv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3UBPROC, glSecondaryColor3ub, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3UBVPROC, glSecondaryColor3ubv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3UIPROC, glSecondaryColor3ui, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3UIVPROC, glSecondaryColor3uiv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3USPROC, glSecondaryColor3us, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLOR3USVPROC, glSecondaryColor3usv, glSecondaryColorSupport);
      SAFE_GET_PROC( PFNGLSECONDARYCOLORPOINTERPROC, glSecondaryColorPointer, glSecondaryColorSupport);
    }

	// This should be set based on the existence of > version 1.4, but
	// for now explicitly check for the extension as there are some issues
	// with ATI drivers emulating mipmaps of NPOTS in software.
	if (extensionSupported(extensions, "GL_ARB_texture_non_power_of_two"))
	{
		glTextureNonPowerOfTwo = true;
	}

  }

  extensionsAvailable = glShadingLanguageSupport && glMultiTextureSupport && glAsmProgramSupport && glTexture3DSupport;

  return extensionsAvailable;
}

