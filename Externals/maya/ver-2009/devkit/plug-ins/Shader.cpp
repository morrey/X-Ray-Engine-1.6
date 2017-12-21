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

#include "Shader.h"
#include "glslFXShader.h"
#include "hlslFXShader.h"
#include "hlslSm3FXShader.h"

std::string shader::sError;
bool shader::sSupportSM3 = false;

//
//
//////////////////////////////////////////////////////////////////////
shader* shader::create( const char *filename) {

  sError.clear();
  if (glShadingLanguageSupport && glAsmProgramSupport) {
    //create an AshliFX for this file and attempt to read it
    //after parsing, the type can be checked to determine which type of shader node to create
    IAshliFX *fx = new IAshliFX;
    fx->init();
    fx->setFX( filename);

    try {
      if (fx->parse()) {
        if (fx->getBinding() == IAshliFX::GLSL) {
          glslFXShader *s = new glslFXShader;
          s->createFromFX( fx);
	      // Commented out as this causes a access violation.
          //delete fx;
          return s;
        }
        if (fx->getBinding() == IAshliFX::DXSL) {
          if ( sSupportSM3) {
            hlslSm3FXShader *s = new hlslSm3FXShader;
            s->createFromFX( fx);
	        // Commented out as this causes a access violation.
            //delete fx;
            return s;
          }
          else {
          hlslFXShader *s = new hlslFXShader;
            if (! s->createFromFX( fx)) {
              sError = s->errorString();
              delete s;
            }
            else {
	      // Commented out as this causes a access violation.
          //delete fx;
          return s;
        }
      }
        }
      }
      else {
        sError = fx->getError();
      }
    } catch(...) {
      printf("Unexpected Error!!\n");
    }
    delete fx;
  }
  //how should we treat an error? there is no convenient way to report an error message

  

  return NULL;
}

