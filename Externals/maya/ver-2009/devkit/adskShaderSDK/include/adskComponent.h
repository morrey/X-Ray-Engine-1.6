// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

/*!
  \file
  \brief Component template classes
*/

#ifndef ADSK_COMPONENT_H
#define ADSK_COMPONENT_H

#if defined __cplusplus

#ifndef ADSK_UTILITIES_H
#include "adskUtilities.h"
#endif

#ifndef SHADER_H
#include <shader.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"


/*!
  \defgroup components Render Pass Components
*/

/*!
  \ingroup components
  \defgroup ambient Ambient Passes
*/

/*!
  \ingroup ambient

  \brief Default ambient material color component.

  The ambient material color is the ambient color, independant of any
  light interactions.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultAmbientMaterialColorComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultAmbientMaterialColorComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultAmbientMaterialColorComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper);
    };

/*!
  \ingroup ambient

  \brief Default ambient component.

  The ambient component computes the contribution of the ambient
  material color given the amount of ambient irradiance.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultAmbientComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultAmbientComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultAmbientComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pColor The material color
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       const miColor& pColor);
    };

/*!
  \ingroup components
  \defgroup diffuse Diffuse Passes
*/


/*!
  \ingroup diffuse

  \brief Default diffuse material color component.

  The diffuse material color is the diffuse color, independant of any
  light interactions.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultDiffuseMaterialColorComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultDiffuseMaterialColorComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultDiffuseMaterialColorComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.

      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper);
    };

/*!
  \ingroup diffuse

  \brief Default diffuse component.

  The diffuse component computes the contribution of the diffuse
  material color given the direct lighting in the scene.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultDiffuseComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultDiffuseComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultDiffuseComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pMaterialColor The material color
      \param[in] pLightDirection The direction of the light
      \param[in] pDotNL The dot product of the light direction and
      surface normal at the shading point.
      \param[in] pLightBlindData The light blind data for the current light

      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       miColor &pMaterialColor,
                       miVector &pLightDirection,
                       miScalar pDotNL,
                       void *pLightBlindData);
    };

/*!
  \ingroup components
  \defgroup specular Specular Passes
*/

/*!
  \ingroup specular

  \brief Default specular component.

  The default specular component does not compute anything since the
  default material is Lambertian, and therefore has no specular
  reflections.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultSpecularComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultSpecularComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultSpecularComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.

      \param[in,out] pParameters The shader parameters.

      \param[in,out] pHelper The shader helper for this shader.

      \param[in,out] pLightDirection The (normalized) direction towards the light.

      \param[in] pReflectionDirection The (normalized) direction towards the reflection.

      \param[in] pDotNL The dot product of the direction from the current intersection
      point in the state to the light and the normal in the state

      \param[in] pBumpNormal Uninverted normal, for lighting in mi_sample_light()
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       miVector &pLightDirection,
                       miVector &pReflectionDirection,
                       miScalar pDotNL,
                       miVector &pBumpNormal);
    };

/*!
  \ingroup components
  \defgroup reflection Reflection Passes
*/

/*!
  \ingroup reflection

  \brief Reflection component for lambertian materials.
  
  This component computes the reflected light arriving at the shading
  point.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultReflectionComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultReflectionComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultReflectionComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pReflectionDirection The reflection direction
      \param[in] pHideSource Is the source object hidden
      \param[in] pGlowIntensity The glow intensity
      \param[in] pNumberOfFrameBuffers The number of frame buffers
      \param[in,out] pFrameBufferInfo The array of frame buffer info structs
      \param[in] pPassTypeInfo The array of pass type info structs
      \param[in] pFrameBufferScale Scale factor applied to frame buffer contributions

      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       miVector &pReflectionDirection,
                       miBoolean pHideSource,
                       miScalar &pGlowIntensity,
                       unsigned int pNumberOfFrameBuffers,
                       FrameBufferInfo* pFrameBufferInfo,
                       PassTypeInfo* pPassTypeInfo,
                       const miScalar& pFrameBufferScale);
    };

/*!
  \ingroup reflection

  \brief Reflection component for specular materials.
  
  This component computes the reflected light arriving at the shading
  point.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultSpecularReflectionComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultSpecularReflectionComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultSpecularReflectionComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pReflectionDirection The reflection direction
      \param[in] pHideSource Is the source object hidden
      \param[in] pGlowIntensity The glow intensity
      \param[in] pNumberOfFrameBuffers The number of frame buffers
      \param[in,out] pFrameBufferInfo The array of frame buffer info structs
      \param[in] pPassTypeInfo The array of pass type info structs
      \param[in] pFrameBufferScale Scale factor applied to frame buffer contributions
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       miVector &pReflectionDirection,
                       miBoolean pHideSource,
                       miScalar &pGlowIntensity,
                       unsigned int pNumberOfFrameBuffers,
                       FrameBufferInfo* pFrameBufferInfo,
                       PassTypeInfo* pPassTypeInfo,
                       const miScalar& pFrameBufferScale);
    };

/*!
  \ingroup components
  \defgroup refraction Refraction Passes
*/

/*!
  \ingroup refraction

  \brief Refraction component.
  
  This component computes the refracted light arriving at the shading
  point. Also fills in transparency.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultRefractionComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultRefractionComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultRefractionComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[out] pResultTransparency The transparency result
      \param[in,out] pTransparency The transparency at the point
      \param[in] pHideSource Is the source object hidden
      \param[in] pRefractions Are refractions activated
      \param[in] pNumberOfFrameBuffers The number of frame buffers
      \param[in,out] pFrameBufferInfo The array of frame buffer states
      \param[in] pPassTypeInfo The array of render pass type information
      \param[in] pFrameBufferScale Scale factor applied to frame buffer contributions

      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       miColor &pResultTransparency,
                       miColor &pTransparency,
                       miBoolean pHideSource,
                       miBoolean pRefractions,
                       unsigned int pNumberOfFrameBuffers,
                       FrameBufferInfo* pFrameBufferInfo,
                       PassTypeInfo* pPassTypeInfo,
                       const miScalar& pFrameBufferScale);
    };

/*!
  \ingroup components
  \defgroup scatter Scatter Passes
*/

/*!
  \ingroup scatter

  \brief Scatter component.
  
  This component computes the scattered light arriving at the shading
  point.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultScatterComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultScatterComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultScatterComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in,out] pScatterData Pointer to memory area for scatter data
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       void** pScatterData);
    };


/*!
  \ingroup components
  \defgroup indirect Indirect Illumination Passes
*/

/*!
  \ingroup indirect

  \brief Default indirect component.
  
  This component computes the indirect light arriving at the shading
  point.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultIndirectComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultIndirectComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultIndirectComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pColor The diffuse color of the material.
      \param[in] pTransparency The transparency of the material.
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper,
                       miColor &pColor,
                       miColor &pTransparency);
    };

/*!
  \ingroup components
  \defgroup incandescence Incandescence Passes
*/

/*!
  \ingroup incandescence

  \brief Incandescence component.
  
  This component computes the incandescent light at the shading point.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ShaderHelper>
    class DefaultIncandescenceComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultIncandescenceComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultIncandescenceComponent() {};
    /*!
      \brief Function object operator.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      
      \return The color corresponding to this component.
    */
    miColor operator()(miState *pState,
                       ParameterType *pParameters,
                       ShaderHelper& pHelper);
    };

/*!
  \ingroup components
  \defgroup custom Custom Passes
*/

/*!
  \ingroup custom

  \brief Custom component.
  
  This component is for computing custom results outside the normal
  set of results for surface shaders. It is called at multiple points
  in the light loop to allow for one or many custom results to be
  determined.

  \tparam ParameterType The structure used in the shader declaration
  to represent the shader parameters.

  \tparam ResultType The result structure for the shader.

  \tparam ShaderHelper The class used in the shader declaration to
  represent the shader helper. See \c ShaderHelper for details on the
  required methods.
*/
template <typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    class DefaultCustomComponent {
  public:
    /*!
      \brief Component constructor.

      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
    */
    DefaultCustomComponent(miState *pState, ParameterType *pParameters);
    /*!
      \brief Component destructor.
    */
    ~DefaultCustomComponent() {};
    /*!
      \brief Called at beginning of shading call, can stop shading.
      
      This is called before anything else in the main shading
      function, returning true will cause shading to stop and return
      the result found in shaderResult. Use to prevent full light loop
      and shading in special cases. Can fill in results in result.
      
      \param[in,out] pState The mental ray rendering state.
      \param[in] pParameters The shader parameters.
      \param[in,out] pResult The result structure for the shader
      \param[out] pShaderResult What the shader should return if short circuiting
    */
    miBoolean shortCircuitShading(miState* pState,
                                  ParameterType *pParameters,
                                  ResultType *pResult,
                                  miBoolean *pShaderResult);
    /*!
      \brief Function object operator. Called for each sample on each light.

      \param[in,out] pState The mental ray rendering state.
      \param[in,out] pParameters The shader parameters.
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pMaterialColor The raw material color of the surface, evaluated 
      at the current intersection
      \param[in] pLightDirection The direction of incoming light
      \param[in] pDotNL The dot product of the direction from the current intersection
      point in the state to the light and the normal in the state
    */
    void operator()(miState *pState,
                    ParameterType *pParameters,
                    ShaderHelper& pHelper,
                    const miColor& pMaterialColor,
                    const miVector& pLightDirection,
                    miScalar pDotNL);
    /*!
      \brief Adjust results for number of samples from a light.
      
      Called after all samples have been accumulated to allow the results to be
      adjusted based on the number of samples for the current light.
      
      \param[in,out] pHelper The shader helper for this shader.
      \param[in] pNumberOfSamples The number of samples taken for the light
    */
    void adjustForSamples(ShaderHelper &pHelper, int pNumberOfSamples);

    /*!
      \brief Modify the color to add to custom beauty passes

      \param[in,out] pState The mental ray rendering state
      \param[in] pParameters The shader parameters
      \param[in,out] pHelper The shader helper for this shader.      
      \param[in,out] pBeautyColor The standard beauty result to modify
    */
    void adjustBeautyResult(miState *pState,
                            ParameterType *pParameters,
                            ShaderHelper &pHelper,
                            miColor &pBeautyColor);
    /*!
      \brief Set custom results in result structure after light loop

      \param[in,out] pState The mental ray rendering state
      \param[in] pParameters The shader parameters
      \param[in,out] pResult The result structure for the shader
      \param[in,out] pHelper The shader helper for this shader.      
    */
    void adjustFinalResult(miState *pState,
                           ParameterType *pParameters,
                           ResultType *pResult,
                           ShaderHelper &pHelper);
    };

// ********** Implementation **********

// Ambient Material Color
template<typename ParameterType,
    typename ShaderHelper>
    DefaultAmbientMaterialColorComponent<ParameterType, ShaderHelper>::DefaultAmbientMaterialColorComponent(miState *pState,
                                                                                                            ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultAmbientMaterialColorComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                                          ParameterType *pParameters,
                                                                                          ShaderHelper& pHelper){
    miState* const &state = pState; //required by the mi_eval_color macro
    miColor materialAmbientColor = *mi_eval_color(&pParameters->ambientColor);

    return materialAmbientColor;
}

// Ambient
template<typename ParameterType,
    typename ShaderHelper>
    DefaultAmbientComponent<ParameterType, ShaderHelper>::DefaultAmbientComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultAmbientComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                             ParameterType *pParameters,
                                                                             ShaderHelper& pHelper,
                                                                             const miColor &pColor){

    return pColor;
}


// Diffuse Material Color
template<typename ParameterType,
    typename ShaderHelper>
    DefaultDiffuseMaterialColorComponent<ParameterType, ShaderHelper>::DefaultDiffuseMaterialColorComponent(miState *pState,
                                                                                                            ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultDiffuseMaterialColorComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                                          ParameterType *pParameters,
                                                                                          ShaderHelper& pHelper){

    miState* const &state = pState; //required by the mi_eval_color macro
    miColor materialDiffuseColor = *mi_eval_color(&pParameters->color);
    return materialDiffuseColor;
}

// Diffuse
template<typename ParameterType,
    typename ShaderHelper>
    DefaultDiffuseComponent<ParameterType, ShaderHelper>::DefaultDiffuseComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultDiffuseComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                             ParameterType *pParameters,
                                                                             ShaderHelper& pHelper,
                                                                             miColor &pMaterialColor,
                                                                             miVector &pLightDirection,
                                                                             miScalar pDotNL,
                                                                             void *pLightBlindData){
    miState* const &state = pState; //required by the mi_eval_scalar macro

    if (pDotNL < 0.f){
        return BLACK;
    }

    miScalar diffuse = *mi_eval_scalar(&pParameters->diffuse);

    // compute the diffuse contribution
    return pMaterialColor * pDotNL * diffuse;
}


// Specular
template<typename ParameterType,
    typename ShaderHelper>
    DefaultSpecularComponent<ParameterType, ShaderHelper>::DefaultSpecularComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultSpecularComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                              ParameterType *pParameters,
                                                                              ShaderHelper& pHelper,
                                                                              miVector &pLightDirection,
                                                                              miVector &pReflectionDirection,
                                                                              miScalar pDotNL,
                                                                              miVector &pBumpNormal){
    // default implementation has no specularities
    return BLACK;
}

// Reflection
template<typename ParameterType,
    typename ShaderHelper>
    DefaultReflectionComponent<ParameterType, ShaderHelper>::DefaultReflectionComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultReflectionComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                                ParameterType *pParameters,
                                                                                ShaderHelper& pHelper,
                                                                                miVector &pReflectionDirection,
                                                                                miBoolean pHideSource,
                                                                                miScalar &pGlowIntensity,
                                                                                unsigned int pNumberOfFrameBuffers,
                                                                                FrameBufferInfo* pFrameBufferInfo,
                                                                                PassTypeInfo* pPassTypeInfo,
                                                                                const miScalar& pFrameBufferScale){
    // do nothing in default case
    return BLACK;
}

// Specular Reflection
template<typename ParameterType,
    typename ShaderHelper>
    DefaultSpecularReflectionComponent<ParameterType, ShaderHelper>::DefaultSpecularReflectionComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultSpecularReflectionComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                                        ParameterType *pParameters,
                                                                                        ShaderHelper& pHelper,
                                                                                        miVector &pReflectionDirection,
                                                                                        miBoolean pHideSource,
                                                                                        miScalar &pGlowIntensity,
                                                                                        unsigned int pNumberOfFrameBuffers,
                                                                                        FrameBufferInfo* pFrameBufferInfo,
                                                                                        PassTypeInfo* pPassTypeInfo,
                                                                                        const miScalar& pFrameBufferScale){
    miState* const &state = pState; // required by the mi_eval_* macros

    miColor resRefl = BLACK;
    miColor specularColor = *mi_eval_color(&pParameters->specularColor);
    if (!MAYA_ISBLACK(specularColor)) {
        miScalar reflectivity = *mi_eval_scalar(&pParameters->reflectivity);

        if (reflectivity > 0.0f) {
            compute_reflection(&resRefl,
                               reflectivity,
                               &specularColor,
                               pGlowIntensity,
                               &pParameters->reflectedColor,
                               &pParameters->reflectionLimit,
                               &pParameters->reflectionBlur,
                               &pParameters->reflectionBlurLimit,
                               &pParameters->reflectionRays,
                               pHideSource,
                               &pState->normal,
                               pState->dot_nd,
                               pState,
                               pNumberOfFrameBuffers,
                               pFrameBufferInfo,
                               pPassTypeInfo,
                               pFrameBufferScale);
            resRefl.r *= specularColor.r * reflectivity;
            resRefl.g *= specularColor.g * reflectivity;
            resRefl.b *= specularColor.b * reflectivity;
        }
    }

    return resRefl;
}

// Refraction
template<typename ParameterType,
    typename ShaderHelper>
    DefaultRefractionComponent<ParameterType, ShaderHelper>::DefaultRefractionComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultRefractionComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                                ParameterType *pParameters,
                                                                                ShaderHelper& pHelper,
                                                                                miColor &pResultTransparency,
                                                                                miColor &pTransparency,
                                                                                miBoolean pHideSource,
                                                                                miBoolean pRefractions,
                                                                                unsigned int pNumberOfFrameBuffers,
                                                                                FrameBufferInfo* pFrameBufferInfo,
                                                                                PassTypeInfo* pPassTypeInfo,
                                                                                const miScalar& pFrameBufferScale){
    miColor resRefr = BLACK;
    pResultTransparency = BLACK;
    compute_refraction(&resRefr,
                       &pResultTransparency,
                       &pParameters->refractionLimit,
                       &pParameters->refractiveIndex,
                       pRefractions,
                       &pTransparency,
                       pHideSource,
                       &pParameters->refractionBlur,
                       &pParameters->refractionBlurLimit,
                       &pParameters->refractionRays,
                       &pParameters->surfaceThickness,
                       &pParameters->transparencyDepth,
                       &pParameters->lightAbsorbance,
                       &pParameters->chromaticAberration,
                       &pState->normal,
                       pState->dot_nd,
                       pState,
                       pNumberOfFrameBuffers,
                       pFrameBufferInfo,
                       pPassTypeInfo,
                       pFrameBufferScale);
    return resRefr;
}

// Scatter
template<typename ParameterType,
    typename ShaderHelper>
    DefaultScatterComponent<ParameterType, ShaderHelper>::DefaultScatterComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultScatterComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                             ParameterType *pParameters,
                                                                             ShaderHelper& pHelper,
                                                                             void** pScatterData){
    miColor resScatter = BLACK;
    compute_scatter(&resScatter,
                    &pParameters->scatterColor,
                    &pParameters->scatterRadius,
                    &pParameters->scatterAccuracy,
                    &pParameters->scatterFalloff,
                    &pParameters->scatterLimit,
                    &pParameters->scatterCache,
                    &pParameters->diffuse,
                    &pParameters->color,
                    &pParameters->translucence,
                    &pParameters->translucenceFocus,
                    &pParameters->translucenceDepth,
                    &pParameters->normalCamera,
                    &pParameters->irradiance,
                    &pParameters->irradianceColor,
                    pState,
                    pScatterData);
    return resScatter;
}

// Indirect
template<typename ParameterType,
    typename ShaderHelper>
    DefaultIndirectComponent<ParameterType, ShaderHelper>::DefaultIndirectComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultIndirectComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                              ParameterType *pParameters,
                                                                              ShaderHelper& pHelper,
                                                                              miColor &pColor,
                                                                              miColor &pTransparency){

    miState* const &state = pState; // required by the mi_eval_scalar macro

    miScalar diffuse = *mi_eval_scalar(&pParameters->diffuse);
    miScalar glowIntensity = *mi_eval_scalar(&pParameters->glowIntensity);
    miColor indirectIllumination;

    compute_irradiance(
        &indirectIllumination,
        &pParameters->irradianceColor,
        diffuse,
        &pColor,
        &pTransparency,
        glowIntensity,
        &pParameters->irradiance,
        pState);

    return indirectIllumination;
}

// Incandescence
template<typename ParameterType,
    typename ShaderHelper>
    DefaultIncandescenceComponent<ParameterType, ShaderHelper>::DefaultIncandescenceComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ShaderHelper>
    miColor DefaultIncandescenceComponent<ParameterType, ShaderHelper>::operator()(miState *pState,
                                                                                   ParameterType *pParameters,
                                                                                   ShaderHelper& pHelper){
    miState* const &state = pState; // required by the mi_eval_color macro
    return *mi_eval_color(&pParameters->incandescence);
}

// Custom
template<typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    DefaultCustomComponent<ParameterType, ResultType, ShaderHelper>::DefaultCustomComponent(miState *pState, ParameterType *pParameters){
}

template<typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    miBoolean DefaultCustomComponent<ParameterType, ResultType, ShaderHelper>::shortCircuitShading(miState* pState,
                                                                                                   ParameterType *pParameters,
                                                                                                   ResultType *pResult,
                                                                                                   miBoolean *pShaderResult){
    // don't short circuit
    if (pShaderResult)
    {
        (*pShaderResult) = miTRUE;
    }
    return miFALSE;
}

template<typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    void DefaultCustomComponent<ParameterType, ResultType, ShaderHelper>::operator()(miState *pState,
                                                                                     ParameterType *pParameters,
                                                                                     ShaderHelper &pHelper,
                                                                                     const miColor& pMaterialColor,
                                                                                     const miVector& pLightDirection,
                                                                                     miScalar pDotNL){
}

template<typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    void DefaultCustomComponent<ParameterType, ResultType, ShaderHelper>::adjustForSamples(ShaderHelper &pHelper,
                                                                                           int pNumberOfSamples){
}

template<typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    void DefaultCustomComponent<ParameterType, ResultType, ShaderHelper>::adjustBeautyResult(miState *pState,
                                                                                             ParameterType *pParameters,
                                                                                             ShaderHelper &pHelper,
                                                                                             miColor &pBeautyColor){
}

template<typename ParameterType,
    typename ResultType,
    typename ShaderHelper>
    void DefaultCustomComponent<ParameterType, ResultType, ShaderHelper>::adjustFinalResult(miState *pState,
                                                                                            ParameterType *pParameters,
                                                                                            ResultType *pResult,
                                                                                            ShaderHelper &pHelper){
}

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif  // __cpluplus
#endif  // ADSK_COMPONENT_H

