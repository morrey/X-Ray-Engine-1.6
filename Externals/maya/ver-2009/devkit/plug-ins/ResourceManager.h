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
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>

#include "glExtensions.h"

//this class is a static place holder for now, it may need to be a singleton
//Presently it only manages the destruction of resources, it should also
//manage a resource pool, so that shader nodes can share texture instances.
class ResourceManager {
  public:

    //these mark GL objects for deletion, since a context might not be available
    static void destroyTexture( GLuint tex);
    static void destroyAsmProgram( GLuint prog);
    static void destroyProgram( GLuint prog);
    static void destroyShader( GLuint shad);

    //clean up the resources we have been unable to previously
    static void recover();

  private:

    static std::vector<GLuint> sTextureList;
    static std::vector<GLuint> sAsmProgramList;
    static std::vector<GLuint> sProgramList;
    static std::vector<GLuint> sShaderList;

    //prevent construction
    ResourceManager() {};
};



#endif //RESOURCE_MANAGER_H

