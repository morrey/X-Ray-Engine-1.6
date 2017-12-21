// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

/*****************************************************************************
 * This example takes the mental ray maya_illum_phong devkit example and 
 * adds support for a subset of the Maya render passes. This differs from the
 * MayaPhong example in that here we define the light loop ourselves, while in
 * MayaPhong the AdskShaderSDK light loop is used and we only implement the
 * specular shading component.
 *
 * Because we write our own light loop, we are also responsible for
 * contributing to the appropriate render passes. See the "RENDER PASS
 * SPECIFIC" sections below. We contribute to ambient material color, diffuse
 * material color, diffuse, direct irradiance, specular, indirect and beauty
 * passes. Support for other passes could easily be added by computing the
 * correct value and contributing in the same manner. See adskShader.h for
 * more details on the other passes.
 *
 * This shader does not support per-light contributions defined by pass
 * contribution maps, however it does support per-object contributions as long
 * as the shader's shading group is exported with the Maya Shading Engine. For
 * details on supporting per-light contributions see adskShader.h
 *****************************************************************************/

#include "adskShader.h"

// Parameters struct
struct CustomPhongParameters {
	ADSK_BASE_SHADER_PARAMETERS
	miColor     ambience;
	miColor     ambient;
	miColor     diffuse;
	miColor     specular;
	miScalar    exponent;
};

const unsigned int CUSTOMPHONG_VERSION = 1;
typedef ShaderHelper<CustomPhongParameters> BaseShaderHelperType;

/*****************************************************************************
 * Wrapper class for custom phong shader, as an extension of the base
 * Material template.
 *****************************************************************************/
class CustomPhongClass : public Material<CustomPhongParameters, BaseShaderHelperType, CUSTOMPHONG_VERSION>
{
public:
	// constructor, initialize any per-instance shader data here
	CustomPhongClass(miState *pState, CustomPhongParameters *pParameters);
	// destructor, de-initialize any per-instance shader data here
	~CustomPhongClass();

	// static initializer, called once per render
	static void init(miState *pState, CustomPhongParameters *pParameters);
	// static deinitializer, called once per render
	static void exit(miState *pState, CustomPhongParameters *pParameters);

	// main shading function called for shader samples
	miBoolean operator()(miColor *pResult, miState *pState, CustomPhongParameters *pParameters);

private:
	// short cut definition for base class
	typedef Material<CustomPhongParameters, BaseShaderHelperType, CUSTOMPHONG_VERSION> MaterialBase;
};

CustomPhongClass::CustomPhongClass(miState *pState, CustomPhongParameters *pParameters) :
	Material<CustomPhongParameters, BaseShaderHelperType, CUSTOMPHONG_VERSION>(pState, pParameters)
{
	// Initialize any instance specific shader data here.

	// This is equivalent to the standard init() shader function when it
	// is called with non-NULL parameters.
}

CustomPhongClass::~CustomPhongClass()
{
	// Deinitialize any instance specific shader data here.

	// This is equivalent to the standard exit() shader function when it
	// is called with non-NULL parameters.

	// MaterialBase::mDestructorState and MaterialBase::mDestructorParameters
	// will be defined correctly when this is called if you need access to the
	// shading state or the parameters.
}

void CustomPhongClass::init(miState *pState, CustomPhongParameters *pParameters)
{
	// Initialize any static shader data here.

	// This is equivalent to the standard init() shader function when it
	// is called with NULL parameters.
}

void CustomPhongClass::exit(miState *pState, CustomPhongParameters *pParameters)
{
	// Deinitialize any static shader data here.

	// This is equivalent to the standard exit() shader function when it
	// is called with NULL parameters.
}

miBoolean CustomPhongClass::operator()(miColor *pResult, miState *pState, CustomPhongParameters *pParameters)
{
	miColor *ambi, *diff, *spec;
	miTag *lights;                          // tag of light instance
	int numLights;                           // # of lights source

	miColor color;                         // color from light source
	miColor diffSum, specSum;              // component accumulators
	miVector dir;                          // direction towards light
	miScalar dot_nl;                       // dot prod of normal and dir
	miScalar expo;                         // Phong exponent (cosine power)
	miScalar s;                            // amount of specular reflection
	miScalar inv;                          // multiplier for inverse samples
    LightDataArray *inLightData;			 

    // For mental images macros
    miState * &state = pState;

	MBS_SETUP(state)

	// MAYA-SPECIFIC
	//   Pointers to access the shader state, and actual values.
	miBoolean *diffuse = NULL, *specular = NULL;
	miBoolean emitDiffuse = miTRUE;  // default emits diffuse
	miBoolean emitSpecular = miTRUE; // default emits specular

	// RENDER PASS SPECIFIC
	//   Access frame buffers for render passes
    PassTypeInfo* passTypeInfo;
    FrameBufferInfo* frameBufferInfo;
    unsigned int numberOfFrameBuffers = getFrameBufferInfo(state, passTypeInfo, frameBufferInfo);

	// check for illegal calls
	if (state->type == miRAY_SHADOW || state->type == miRAY_DISPLACE ) {
		return(miFALSE);
	}
 
	ambi =  mi_eval_color(&pParameters->ambient);
	diff =  mi_eval_color(&pParameters->diffuse);
	spec =  mi_eval_color(&pParameters->specular);
	expo = *mi_eval_scalar(&pParameters->exponent);

	*pResult    = *mi_eval_color(&pParameters->ambience); // ambient term
	pResult->r *= ambi->r;
	pResult->g *= ambi->g;
	pResult->b *= ambi->b;

	// RENDER PASS SPECIFIC
	//   Write values to non-light dependant frame buffers
    if (numberOfFrameBuffers && MaterialBase::mFrameBufferWriteOperation)
    {
		MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, opaqueColor(*ambi), AMBIENT_MATERIAL_COLOR, false);
        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, opaqueColor(*diff), DIFFUSE_MATERIAL_COLOR, false);
    }

	inLightData = &MBS->lightData;
    miColor  *preShadowColor = &inLightData->preShadowColor;

	/* Get instance light list. */
    mi_instance_lightlist(&numLights, &lights, state);
    /* Evaluate all lights in the list. */
    for ( ; numLights--; lights++)         
	{
		int    numSamples = 0;
		diffSum.r = diffSum.g = diffSum.b = 0;
		specSum.r = specSum.g = specSum.b = 0;

		// Function that initialize light sample accumulators which need to be called before the sample loop.
		sampleLightBegin(numberOfFrameBuffers, frameBufferInfo);

		while (mi_sample_light(
                &color, &dir, &dot_nl,
                state, *lights, &numSamples)) {
	
			// Call to enable renderpass contributions for light shaders that were not developped using the AdskShaderSDK.    
			handleNonAdskLights(numberOfFrameBuffers, frameBufferInfo, color, *lights, state);

			// MAYA-SPECIFIC
			//
			//   Get custom Maya light properties.
			//
			//   mayabase_stateitem_get returns pointer to
			//   specified MbStateItem in the shader state.
			//   MBSI_LIGHTDIFFUSE and MBSI_LIGHTSPECULAR
			//   contains information whether the last sampled
			//   light emits diffuse and/or specular.
			//   The variable-length parameter should terminated
			//   with MBSI_NULL.
			//
			//   mayabase light shaders always set the shader state
			//   value to inform that whether the light shader emits
			//   diffuse and specular lights.
			if (mayabase_stateitem_get(state,
					MBSI_LIGHTDIFFUSE, &diffuse,
					MBSI_LIGHTSPECULAR, &specular,
					MBSI_NULL)) {
				emitDiffuse = *diffuse;
				emitSpecular = *specular;
			}

			// Add diffuse component
			// only if the light emits diffuse lights
			miColor unlitDiffuse = BLACK;
			if (emitDiffuse && dot_nl > 0) {
				unlitDiffuse = opaqueColor(dot_nl*(*diff));
				// Lambert's cosine law
				if (numberOfFrameBuffers && MaterialBase::mFrameBufferWriteOperation)
				{
					MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, unlitDiffuse, DIFFUSE, true);
					MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, opaqueColor(dot_nl*WHITE), DIRECT_IRRADIANCE, true);
				}

				//Compute values for the master beauty pass
				diffSum = diffSum + unlitDiffuse * color;
			}

			// Add specular component
			// only if the light emits specular lights
			miColor unlitSpecular = BLACK;
			if (emitSpecular) {
				// Phong's cosine power
				s = mi_phong_specular(expo, state, &dir);
				if (s > 0.0) {
					unlitSpecular = opaqueColor(s*(*spec));
					if (numberOfFrameBuffers && MaterialBase::mFrameBufferWriteOperation)
					{
						MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, unlitSpecular, SPECULAR, true);
					}
					specSum = specSum + unlitSpecular * color;
				}
			}

			miColor unlitBeauty = opaqueColor(unlitSpecular+unlitDiffuse);

            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                unlitBeauty, SHADOW, true, preShadowColor);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                MAYA_LUMINANCE(unlitBeauty), SHADOW_MONO, true, preShadowColor);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                unlitBeauty, BEAUTY, true );
		}

		// Function that take care of combining sample values into the material frame buffer values, 
		//    called after light sampling loop.
		sampleLightEnd(state,
			   numberOfFrameBuffers,
			   frameBufferInfo,
			   numSamples,
			   MaterialBase::mFrameBufferWriteOperation,
			   MaterialBase::mFrameBufferWriteFlags,
			   MaterialBase::mFrameBufferWriteFactor);

		if (numSamples > 0) {
			inv = 1.0f / numSamples;

			diffSum.r *= inv;
			diffSum.g *= inv;
			diffSum.b *= inv;

			specSum.r *= inv;
			specSum.g *= inv;
			specSum.b *= inv;

			pResult->r += diffSum.r + specSum.r;
			pResult->g += diffSum.g + specSum.g;
			pResult->b += diffSum.b + specSum.b;
		}
	} /* for ( ; numLights--; lights++) */

	// add contribution from indirect illumination (caustics)
	mi_compute_irradiance(&color, state);
	pResult->r += color.r * diff->r;
	pResult->g += color.g * diff->g;
	pResult->b += color.b * diff->b;
	pResult->a  = 1;

	// RENDER PASS SPECIFIC
	//   Write indirect illumination and final beauty to frame buffers
    if (numberOfFrameBuffers && MaterialBase::mFrameBufferWriteOperation)
    {
		MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, opaqueColor(color), INDIRECT, false);
		MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, opaqueColor(color*(*diff)), BEAUTY, false);
    }

	return(miTRUE);
}

// Use the EXPOSE macro to create Mental Ray compliant shader functions
//----------------------------------------------------------------------
EXPOSE(CustomPhong, miColor, );
