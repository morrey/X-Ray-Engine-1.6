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

#include "ResourceManager.h"


std::vector<GLuint> ResourceManager::sTextureList;
std::vector<GLuint> ResourceManager::sAsmProgramList;
std::vector<GLuint> ResourceManager::sProgramList;
std::vector<GLuint> ResourceManager::sShaderList;


//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::recover() 
{
	if (sTextureList.size())
		glDeleteTextures( (GLsizei) sTextureList.size(), &(*sTextureList.begin()));

	if (sAsmProgramList.size())
		glDeleteProgramsARB( (GLsizei) sAsmProgramList.size(), &(*sAsmProgramList.begin()));


	for (std::vector<GLuint>::iterator it=sProgramList.begin(); it<sProgramList.end(); it++) {
		glDeleteObject( *it); 
	}
	{
		for (std::vector<GLuint>::iterator it=sShaderList.begin(); it<sShaderList.end(); it++) {
			glDeleteObject( *it); 
		}
	}

	sTextureList.clear();
	sAsmProgramList.clear();
	sProgramList.clear();
	sShaderList.clear();
	
	GL_CHECK;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyTexture( GLuint tex) {
  sTextureList.push_back(tex);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyAsmProgram( GLuint prog) {
  sAsmProgramList.push_back(prog);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyProgram( GLuint prog) {
  sProgramList.push_back(prog);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyShader( GLuint shad){
  sShaderList.push_back(shad);
}

