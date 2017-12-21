// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

/*****************************************************************************
 * This example implements a standard Phong material by defining a custom
 * specular component and passing that to the Material template defined by
 * the AdskShaderSDK in adskShader.h. All other aspects of the shader
 * (including full support for render passes) are handled by the default
 * implementations of the other components and by the light loop defined in
 * adskShader.h.
 *
 * For an example that defines a custom light loop, see CustomPhong.
 *****************************************************************************/

#include "adskShader.h"

struct MayaPhongParameters {
	ADSK_REFLECTIVE_MATERIAL_PARAMETERS
	miScalar cosPower;
};

//-----------------------------------------------------------------------------
// CLASS MayaPhongSpecularComponent
//
// Description: Implementation of the specular reflection component of a Phong
// material. This is used by the light loop in adskShader.h to determine the
// specular component of the material for the current sample. It is
// instantiated as a local variable to the main shading function and any
// particular instance is not shared between threads.
// 

template <typename ParameterType,
		  typename ShaderHelper>
class MayaPhongSpecularComponent
{
public:
	MayaPhongSpecularComponent(miState *state, ParameterType *paras);

	~MayaPhongSpecularComponent() {};

	// Called from the light loop in adskShader.h to determine the specular
	// component for the current sample.
	miColor operator()(miState *state,
					   ParameterType *paras,
					   ShaderHelper &helper,
					   miVector &pLightDirection,
					   miVector &pReflectionDirection,
					   miScalar pDotNL,
					   miVector &pBumpNormal);
public:
	miColor materialSpecularColor;
	miScalar specularExponent;
	miScalar reflectionSpecularity;	
};

template<typename ParameterType,
		 typename ShaderHelper>
MayaPhongSpecularComponent<ParameterType, ShaderHelper>::MayaPhongSpecularComponent(miState *state, ParameterType *paras)
{
	// pre-compute stuff that doesn't change inside light loop
	materialSpecularColor = *mi_eval_color(&paras->specularColor); 
	specularExponent = *mi_eval_scalar(&paras->cosPower);
	reflectionSpecularity = *mi_eval_scalar(&paras->reflectionSpec);
}

template<typename ParameterType,
		 typename ShaderHelper>
miColor MayaPhongSpecularComponent<ParameterType, ShaderHelper>::operator()(miState *state,
                                                                            ParameterType *paras,
                                                                            ShaderHelper &helper,
                                                                            miVector &pLightDirection,
                                                                            miVector &pReflectionDirection,
                                                                            miScalar pDotNL,
                                                                            miVector &pBumpNormal)
{
	miColor resSpecular = MAYA_BLACK;
	if (pDotNL > 0.0f) {
		miScalar phongSpecular = compute_phong_specular(&pLightDirection,
                                                        specularExponent,
                                                        reflectionSpecularity,
                                                        &pReflectionDirection,
                                                        state);
		if (phongSpecular > 0.0f) {
			resSpecular = phongSpecular * materialSpecularColor;
		}
	}

	return resSpecular;
}

// Use the SpecularShaderHelper to correctly compute reflections and
// attenuation for specular materials
typedef SpecularShaderHelper<MayaPhongParameters> SpecularShaderHelperType;

// Definition MayaPhongClass as a specialization of the Surface template.
// Except for the above specular component we use the default implementations
// of all other componenets.
typedef Surface<
	MayaPhongParameters,   
	SurfaceShaderReturnType,
	SpecularShaderHelperType,
	DefaultAmbientMaterialColorComponent<MayaPhongParameters, SpecularShaderHelperType>, 
	DefaultAmbientComponent<MayaPhongParameters, SpecularShaderHelperType>,
	DefaultDiffuseMaterialColorComponent<MayaPhongParameters, SpecularShaderHelperType>,
	DefaultDiffuseComponent<MayaPhongParameters, SpecularShaderHelperType>,
	MayaPhongSpecularComponent<MayaPhongParameters, SpecularShaderHelperType>,
	DefaultSpecularReflectionComponent<MayaPhongParameters, SpecularShaderHelperType>
> MayaPhongClass;

// Use the EXPOSE macro to create Mental Ray compliant shader functions
EXPOSE_CUSTOM_SURFACE(MayaPhong);

