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
#ifndef GLSL_FX_SHADER_H
#define GLSL_FX_SHADER_H

#include <vector>
#include <string>

#include <IAshliFX.h>

#include "Shader.h"
#include "Observer.h"
#include "glExtensions.h"


class glslFXShader : public shader {
  public:

    glslFXShader( );
    virtual ~glslFXShader();

  //
  // Shader loading and management routines
  //
  //  These routines are intended to deal with the realities of deferred processing
  // in the Maya environemnt. The shader file ideally needs to be parsed and parameters
  // extracted prior to the availability of a GL context. This forces shader compilation
  // to be defered until first use.
  //
    bool createFromFile( const char *filename);
    bool createFromFX( IAshliFX *fx);
  protected:
    bool parseParameters( const IAshliFX *fx);
    DataType parseUniformType( const char *type);
    Semantic parseUniformSemantic( const char *semantic);
    SamplerType parseSamplerType( const char *type);
    void updateHandles(); //configure the handles for the uniforms, etc.
    bool buildShaders(); //build the shaders that we had to defer compilation on
    const char* getVertexShader( int pass);
    const char* getPixelShader( int pass);

  public:
    virtual bool valid();
    virtual int passCount();
    virtual int techniqueCount();
    virtual const char* techniqueName( int n);
    virtual bool build();
    virtual void bind();
	virtual void setShapeDependentState();
    virtual void unbind();
    virtual void setTechnique( int t);
    virtual void setPass( int p);

    //need to have queries for attribs and uniforms
    virtual int uniformCount();
    virtual int samplerCount();
    virtual int attributeCount();
    virtual const char* uniformName(int i);
    virtual DataType uniformType(int i);
    virtual Semantic uniformSemantic(int i);
    virtual float* uniformDefault(int i);
    virtual const char* samplerName(int i);
    virtual SamplerType samplerType(int i);
    virtual const char* attributeName(int i);
    virtual DataType attributeType(int i);
    virtual int attributeHandle(int i);

    //need set functions for current values
    virtual void updateUniformBool( int i, bool val);
    virtual void updateUniformInt( int i, int val);
    virtual void updateUniformFloat( int i, float val);
    virtual void updateUniformBVec( int i, const bool* val);
    virtual void updateUniformIVec( int i, const int* val);
    virtual void updateUniformVec( int i, const float* val);
    virtual void updateUniformMat( int i, const float* val);
    virtual void updateUniformMat( int i, const double* val);
    virtual void updateSampler( int i, unsigned int val);

    //predefined attributes
    virtual bool usesColor();
    virtual bool usesNormal();
    virtual bool usesTexCoord( int set);
    virtual bool usesTangent();
    virtual bool usesBinormal();
    virtual int tangentSlot();
    virtual int binormalSlot();

    //error reporting
    virtual const char* errorString();

  private:

    void deleteShaders();

    //IAshliFX *m_fx;
    std::vector<GLuint> m_programList;
    std::vector<GLuint> m_fShaderList;
    std::vector<GLuint> m_vShaderList;

    //these are to hold the ASHLIFX data
    int m_techniqueCount;
    std::vector<std::string> m_techniqueNames;
    std::vector<int> m_passCount; //per technique
    std::vector<int> m_techniqueOffset; //where does this technique begin
    std::vector<std::string> m_vertexShaders; // vertex shader strings
    std::vector<std::string> m_fragmentShaders; // fragment shader strings
    std::vector<passState*> m_stateList;

    bool m_valid;


    int m_activePass;
    int m_activeTechnique;

    struct uniform {
      std::string name; 
      DataType type;
      Semantic usage; //handles semantic values
      std::vector<GLint> handle; //will need to switch to a vector to handle Multipass
      union {
        float fVal[16];
        int iVal[4];
      };
      union {
        float fDefault[16];
        int iDefault[4];
      };
      bool dirty;
    };

    struct attribute {
      std::string name;
      DataType type;
      std::vector<int> handle;
    };

    struct sampler {
      std::string name;
      SamplerType type;
      std::vector<GLint> handle; //will need to switch to a vector to handle Multipass
      GLuint texObject; 
      std::vector<int> texUnit; //will need to switch to a vector to handle Multipass
      bool dirty;
    };

    std::vector<uniform> m_uniformList;
    std::vector<attribute> m_attributeList;
    std::vector<sampler> m_samplerList;

    bool m_stale;

    bool m_color;
    bool m_normal;
    bool m_tangent;
    bool m_binormal;
    unsigned int m_texMask;

    int m_tangentSlot;
    int m_binormalSlot;

    std::string m_error;

    void parseExpression( uniform &u, const char *exp);

};


#endif //GLSL_FX_SHADER_H

