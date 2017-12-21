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

#include "DefaultShader.h"

//
// Simple default GLSL shader that computes a directional light on a checker
// pattern. The front and back colors are different, to help identify the surface.
//
////////////////////////////////////////////////////////////////////////////////
	const char defaultShader::vShader[] =
		"varying vec3 eyeNormal;\n"
		"\n"
		"void main() {\n"
		"	gl_Position = ftransform();\n"
		"	eyeNormal = normalize(gl_NormalMatrix*gl_Normal);\n"
		"	gl_FrontColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
		"	gl_BackColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"	gl_TexCoord[0] = gl_MultiTexCoord0*4.0;\n"
		"}\n\0";

	const char defaultShader::fShader[] =
		"varying vec3 eyeNormal;\n"
		"\n"
		"void main(){ \n"
		"\n"
		"vec3 lightDirection = vec3( 0.5, 0.5, 0.5 );\n"
		"vec3 halfVector = normalize( lightDirection + vec3( 0.0, 0.0, 1.0 ));\n"
		"vec4 col = step(0.5,mod(gl_TexCoord[0],1.0));\n"
		"vec3 color = (abs(1.0-(col.r+col.g))==0.0) ? gl_Color.xyz : vec3(1.0);\n"
		"\n"
		"vec3 normal = normalize(eyeNormal);\n"
		"float dif = abs(dot(normal, lightDirection));\n"
		"dif = min( dif+0.2, 1.0);\n"
		"float spec = clamp( abs( dot( normal, halfVector) ), 0.0, 1.0);\n"
		"spec = pow(spec, 24.0);\n"
		"\n"
		"gl_FragColor = vec4( color*dif+spec, 1.0);\n"
		"}\n\0";

//
// defaultShader constructor
//
//  This constructor actually compiles and links the GLSL shader,
// so it must be called with a current context active.
////////////////////////////////////////////////////////////////////////////////
defaultShader::defaultShader() : m_program(0), m_fShader(0), m_vShader(0) {

  if (glShadingLanguageSupport) {
  m_program = glCreateProgramObject();
  m_vShader = glCreateShaderObject( GL_VERTEX_SHADER);
  m_fShader = glCreateShaderObject( GL_FRAGMENT_SHADER);
  glAttachObject( m_program, m_vShader);
  glAttachObject( m_program, m_fShader);

  const char *temp = vShader;
  glShaderSource( m_vShader, 1, &temp, NULL);
  temp = fShader;
  glShaderSource( m_fShader, 1, &temp, NULL);

  GLint success;
  glCompileShader( m_vShader);
  glGetObjectParameteriv( m_vShader, GL_COMPILE_STATUS, &success);
  if (! success) {
    //figure out why we didn't compile
    char log[256];
    //printf("Failed to compile vertex shader\n");
    glGetInfoLog( m_vShader, 256, NULL, log);
    //printf(" Infolog: %s\n", log);
  }

  glCompileShader( m_fShader);
  glGetObjectParameteriv( m_fShader, GL_COMPILE_STATUS, &success);
  if (! success) {
    //figure out why we didn't compile
    char log[256];
    //printf("Failed to compile fragment shader\n");
    glGetInfoLog( m_fShader, 256, NULL, log);
    //printf(" Infolog: %s\n", log);
  }

  glLinkProgram( m_program);
  glGetObjectParameteriv( m_program, GL_LINK_STATUS, &success);
  if (! success) {
    //figure out why we didn't link
    char log[256];
    //printf("Failed to link\n");
    glGetInfoLog( m_program, 256, NULL, log);
    //printf(" Infolog: %s\n", log);
  }  
}
}

//
//
////////////////////////////////////////////////////////////////////////////////
void defaultShader::bind() {
  if (glShadingLanguageSupport)
    glUseProgramObject(m_program);
}

////////////////////////////////////////////////////////////////////////////////
void defaultShader::setShapeDependentState() {
}

//
//
////////////////////////////////////////////////////////////////////////////////
void defaultShader::unbind() {
  if (glShadingLanguageSupport)
    glUseProgramObject(0);
}
