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
#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

#include "glExtensions.h"

#include "Shader.h"

class defaultShader : public shader {

  public:
    defaultShader();

    //no GL cleanup, because we may not have a context at shutdown
    virtual ~defaultShader() {};

    virtual bool valid() {return true;};
    virtual int passCount() {return 1;};
    virtual int techniqueCount() {return 1;};
    virtual const char* techniqueName( int n) { return NULL;};
    virtual bool build() { return true;};
    virtual void bind();
	virtual void setShapeDependentState();
    virtual void unbind();
    virtual void setTechnique( int t) {};
    virtual void setPass( int p) {};
    virtual const char* getVertexShader( int pass) {return NULL;};
    virtual const char* getPixelShader( int pass) {return NULL;};

    virtual int uniformCount() {return 0;};
    virtual int samplerCount() {return 0;};
    virtual int attributeCount() {return 0;};
    virtual const char* uniformName(int i) {return NULL;};
    virtual DataType uniformType(int i) { return dtUnknown;};
    virtual Semantic uniformSemantic(int i) { return smNone;};
    virtual float* uniformDefault(int i) { return NULL;};
    virtual const char* samplerName(int i) {return NULL;};
    virtual SamplerType samplerType(int i) {return stUnknown;};
    virtual const char* attributeName(int i) {return NULL;};
    virtual DataType attributeType(int i) {return dtUnknown;};
    virtual int attributeHandle(int i) {return 0;};

    //need set functions for current values
    virtual void updateUniformBool( int i, bool val) {};
    virtual void updateUniformInt( int i, int val) {};
    virtual void updateUniformFloat( int i, float val) {};
    virtual void updateUniformBVec( int i, const bool* val) {};
    virtual void updateUniformIVec( int i, const int* val) {};
    virtual void updateUniformVec( int i, const float* val) {};
    virtual void updateUniformMat( int i, const float* val) {};
    virtual void updateUniformMat( int i, const double* val) {};
    virtual void updateSampler( int i, unsigned int val) {};

    //predefined attributes
    virtual bool usesColor() {return false;};
    virtual bool usesNormal() {return true;};
    virtual bool usesTexCoord( int set) {return set==0;};
    virtual bool usesTangent() {return false;};
    virtual bool usesBinormal() {return false;};
    virtual int tangentSlot() {return 0;};
    virtual int binormalSlot() {return 0;};

    //error reporting
    virtual const char* errorString() { return "";};

  private:

    static const char vShader[];
    static const char fShader[];

    GLuint m_program;
    GLuint m_fShader;
    GLuint m_vShader;
};

#endif //DEFAULT_SHADER_H


