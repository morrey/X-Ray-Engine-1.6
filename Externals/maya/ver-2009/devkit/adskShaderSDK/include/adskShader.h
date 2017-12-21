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
  \brief Main shader base classes, and helper classes.

  The Autodesk Shader Software Development Kit allows you to easily
  write new shaders which automatically support the latest features of
  Maya 2009, including render passes.
*/

#ifndef ADSK_SHADER_H
#define ADSK_SHADER_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

#ifndef GEOSHADER_H
#include <geoshader.h>
#endif

#ifndef ADSK_COLOR_H
#include "adskColor.h"
#endif

#ifndef ADSK_UTILITIES_H
#include "adskUtilities.h"
#endif

#ifndef ADSK_COMPONENT_H
#include "adskComponent.h"
#endif

#ifndef ADSK_MI_WRAPPER_H
#include "adskMIWrapper.h"
#endif

#ifndef ADSK_RENDER_PASS_TYPES_H
#include "adskRenderPassTypes.h"
#endif

#ifndef ADSK_MAYASTATE_H
#include "adskMayaState.h"
#endif

#ifndef ADSK_TRAVERSAL_H
#include "adskTraversal.h"
#endif

#ifndef ADSK_SCATTER_H
#include "adskScatter.h"
#endif

#include "mayaapi.h"

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

#if defined(ADSKSHADERSDK_DLL)
#define DEFAULT_SHADER_VERSION ADSK_SHADER_VERSION
#else
#define DEFAULT_SHADER_VERSION 1
#endif

//! \cond DOCUMENT_SHADER_DEFINES
#define ADSK_BASE_SHADER_PARAMETERS                                     \
    miInteger         FrameBufferWriteOperation; /*!< The operation to be performed on the frame buffer. */ \
    miInteger         FrameBufferWriteFlags;     /*!< The write flags to be used for the frame buffer. */ \
    miScalar          FrameBufferWriteFactor;    /*!< If scaling, the scaling factor to be applied before writing to the frame buffer. */

#define ADSK_BASE_MATERIAL_PARAMETERS                                   \
    ADSK_BASE_SHADER_PARAMETERS                                         \
    miColor           color;                    /*!< The basic color of the surface. */ \
    miColor           transparency;             /*!< How transparent or opaque the material is. Black is opaque, white is completely transparent. */

#define ADSK_SIMPLE_MATERIAL_PARAMETERS                                 \
    ADSK_BASE_MATERIAL_PARAMETERS                                       \
    miColor           glowColor;                /*!< The final output glow color. */

#define ADSK_MATTE_MATERIAL_PARAMETERS                                  \
    ADSK_BASE_MATERIAL_PARAMETERS                                       \
    miInteger         matteOpacityMode;         /*!< Controls how the system will use the \c matteOpacity. Valid options are opacity gain, solid matte, and black hole. */ \
    miScalar          matteOpacity;             /*!< This is used to affect how the matte for this material will be calculated. */

#define ADSK_GLOW_MATERIAL_PARAMETERS                                   \
    miScalar          glowIntensity;            /*!< The strengh of the glow. */

#define ADSK_LAMBERTIAN_MATERIAL_PARAMETERS                             \
    ADSK_MATTE_MATERIAL_PARAMETERS                                      \
    ADSK_GLOW_MATERIAL_PARAMETERS                                       \
    miInteger         refractionLimit;          /*!< Ray depth limit. */ \
    miScalar          refractiveIndex;          /*!< Determines how much a ray of light will bend when it passes through an object. */ \
    miBoolean         refractions;              /*!< True if the object refracts light. */ \
    miScalar          diffuse;                  /*!< Controls how much of the light in the scene is reflected from the object. */ \
    miColor           ambientColor;             /*!< As the ambient color becomes brighter, it affects the material's color by lightening it and blending the two colors */ \
    miColor           incandescence;            /*!< Makes a surface appear to emit light. */ \
    miScalar          translucence;             /*!< Simulates the way light diffusely penetrates through translucent objects. */ \
    miScalar          translucenceFocus;        /*!< Simulates the way light scatters more in a forward direction through translucent objects. */ \
    miScalar          translucenceDepth;        /*!< The depth of penetration into an object at which translucence decays to nothing. */ \
    miScalar          opacityGain;              /*!< The Opacity Gain value is used as a multiplier on the matte value produced by this material. */ \
    miBoolean         hideSource;               /*!< When on (and glow intensity is not zero), then the glowing object will be hidden, but its glowing halo will still be rendered. */ \
    miScalar          surfaceThickness;         /*!< The simulated thickness (in world space units) of transparent objects that are made from single surfaces. */ \
    miScalar          shadowAttenuation;        /*!< Causes shadows of transparent objects to be brighter in the center, simulating the focusing of light. */ \
    miScalar          transparencyDepth;        /*!< This should be used for backwards compatability when rendering data from Studio - Maya users should use Absorbance instead. */ \
    miScalar          lightAbsorbance;          /*!< The light absorbance of the material. A material with an absorbance of 0 will transmitt completely. The higher the absorbance, the less light will pass through. */ \
    miBoolean         chromaticAberration;      /*!< Causes different wavelengths of light to refract at different angles when passing through a transparent surface. */ \
    miVector          normalCamera;             /*!< The surface normal in camera space. */ \
    miColor           irradiance;               /*!< Port to map indirect illumination from a texture instead of computing it. */ \
    miColor           irradianceColor;          /*!< Scale the indirect illumination by this color before applying. */ \
    miScalar          refractionBlur;           /*!< Enable refraction blur by shooting more refraction rays. A value of zero implies a perfectly specular interaction, a value of 90 a perfectly diffuse refraction. */ \
    miInteger         refractionBlurLimit;      /*!< Determines the blurriness of secondary refractions. The higher the limit, the more the secondary refractions are blurred. */ \
    miInteger         refractionRays;           /*!< Specifies how many rays to use to sample the random deviation from the perfect specular direction. */ \
    miColor           scatterColor;             /*!< Determines the color of the scatter component of the shader. */ \
    miScalar          scatterRadius;            /*!< Determines how far light scatters under a surface. */ \
    miInteger         scatterAccuracy;          /*!< Determines how many samples from within the Scatter Radius are taken to blur the diffuse component of the shader. */ \
    miInteger         scatterFalloff;           /*!< Determines how quickly light diminishes along the scatter path. Modes can be none, linear, quadratic, or exponential. */ \
    miInteger         scatterLimit;             /*!< Determines a limit for the total number of refractions and reflections in the current surface point. */ \
    miInteger         scatterCache;             /*!< Determines the number of scatter samples that are internally cached to improve efficiency. */

#define ADSK_REFLECTIVE_MATERIAL_PARAMETERS                             \
    ADSK_LAMBERTIAN_MATERIAL_PARAMETERS                                 \
    miInteger         reflectionLimit;          /*!< Determines the blurriness of reflections or refractions. The higher the limit, the more the secondary reflections are blurred. */ \
    miColor           specularColor;            /*!< The color of shiny highlights on the surface. */ \
    miColor           reflectedColor;           /*!< Represents the color of light reflected from the material. */ \
    miScalar          reflectivity;             /*!< Gives the surface the ability to reflect its surroundings or the reflected color. */ \
    miScalar          reflectionSpec;           /*!< Reduce this value to avoid highlight aliasing artifacts produced in reflections during raytracing because of very thin or small highlights. */ \
    miScalar          reflectionBlur;           /*!< Enable reflection blur by shooting more reflection rays. A value of zero implies a perfectly specular interaction, a value of 90 a perfectly diffuse reflection. */ \
    miInteger         reflectionBlurLimit;      /*!< Determines the blurriness of secondary reflections. The higher the limit, the more the secondary reflections are blurred.*/ \
    miInteger         reflectionRays;           /*!< Specifies how many rays to use to sample the random deviation from the perfect specular direction. */

//! \endcond

//! Parameters common to all shaders
struct BaseShaderParameters {
    ADSK_BASE_SHADER_PARAMETERS
};

struct BaseMaterialParameters {
    ADSK_BASE_MATERIAL_PARAMETERS
};

struct SimpleMaterialParameters {
    ADSK_SIMPLE_MATERIAL_PARAMETERS
};

struct MatteMaterialParameters {
    ADSK_MATTE_MATERIAL_PARAMETERS
};

struct GlowMaterialParameters {
    ADSK_GLOW_MATERIAL_PARAMETERS
};

struct LambertianMaterialParameters {
    ADSK_LAMBERTIAN_MATERIAL_PARAMETERS
};

struct ReflectiveMaterialParameters {
    ADSK_REFLECTIVE_MATERIAL_PARAMETERS
};

/*!
  \brief Shader helper class.

  This class has several methods which can be used to override the
  default shading behaviour.

  \tparam ShaderParameters The shader parameter structure.
*/
template<typename ShaderParameters>
class ShaderHelper {
  public:

    /*!
      \brief Constructor for shader helper.

      This will be called once per evaluation of the main shading function
      for the shader.

      \param[in,out] pState A pointer to the mental ray state structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    ShaderHelper(miState *pState, ShaderParameters *pParameters) {};

    /*!
      \brief Deconstructor for shader helper.
      
      This will be called once per evaluation of the main shading function
      for the shader.
    */
    ~ShaderHelper() {};

    /*!
      \brief Adjust normal for Maya's bump mapping.

      This function adjusts state->normal to account for bump mapping. Override
      it to change how bump mapping works.
    */
    inline void setupMayaBumpMapping() const {};

    /*!
      \brief Determine if source should be hidden.

      Most Maya shaders define the hideSource attribute to determine if the
      source geometry should be hidden (often used with glow). Override this
      to tell the main shading function whether or not the source should be
      hidden.

      \return True if source should be hidden, false otherwise.
    */
    inline miBoolean computeHideSource() const
    {
        return miFALSE;
    }

    /*!
      \brief Computes transparency for shadow rays.
      
      This function computes the transparency of the shader when hit by
      a shadow ray.
      
      \param[out] pResTransp The resulting transparency.

      \param[in] pHideSource True if the source is hidden.
    */
    inline void computeTransparencyForShadow(miColor &pResTransp,
                                             miBoolean pHideSource) const
    {
        pResTransp = BLACK;
    }

    /*!
      \brief Evaluates shader parameters necessary for later computations.
      
      This function is called after other initialization to give the helper
      a chance to evaluate any parameters necessary for later computations.
    */
    inline void evaluateParameters() {};

    /*!
      \brief Computes transparency parameters for non-shadow rays.

      This function is called to evaluate the transparency parameters for
      the shader on non-shadow rays.

      \return The transparency color for use in later computations.
    */
    inline miColor computeTransparency() const
    {
        return BLACK;
    }

    /*!
      \brief Computes the specular glow parameters for the shader.

      This function is called to evaluate any specular glow parameters to
      the shader for use in later computations.

      \return The amount of specular glow.
    */
    inline miScalar computeSpecularGlow() const
    {
        return 0.0f;
    }

    /*!
      \brief Set the ASQ weight for this shader call.

      This function adjusts the ASQ weight according to the light loop's
      impact on the final shader result.

      \param[in,out] MBS The current Maya state.

      \param[in] bc BRDF component information.

      \param[in] pColor The diffuse color for the shader.

      \param[in] pTransparency The transparency for the shader.

      \param[in] pGlowIntensity The glow intensity for the shader.
    */
    inline void setASQWeight(MayabaseState * &MBS,
                             BRDFComponent &bc,
                             const miColor &pColor,
                             const miColor &pTransparency,
                             miScalar &pGlowIntensity) const {};

    /*!
      \brief Computes the ambient result color.

      This function computes the color returned in the ambient channel
      of the shader result structure.

      \param[in] pAmbientColor The ambient color of the material.

      \param[in] pColor The diffuse color of the material.

      \return The ambient result.
    */
    inline miColor computeAmbientResult(const miColor &pAmbientColor,
                                        const miColor &pColor) const
    {
        return BLACK;
    }

    /*!
      \brief Computes the translucence result for the shader.

      This function computes the translucence result for the shader given
      various parameters. This result is combined with the diffuse component
      to produce the diffuse result.

      \param[in] pDotNL The dot product between the light vector and the normal.

      \param[in] pLightDirection The light vector.

      \param[in] pTranslucence The amount of translucence for the material.

      \param[in] pTranslucenceFocus The translucence focus for the material.

      \param[in] pTranslucenceDepth The translucence depth for the material.

      \param[in] pLightBlindData Custom light shader data.

      \return The translucence result for the shader.
    */
    inline miScalar computeTranslucence(miScalar pDotNL,
                                        miVector &pLightDirection,
                                        miScalar pTranslucence,
                                        miScalar pTranslucenceFocus,
                                        miScalar pTranslucenceDepth,
                                        void *pLightBlindData) const
    {
        return 0.0f;
    }

    /*!
      \brief Computes the diffuse factor for area lights.

      This function computes the diffuse factor for area lights.

      \param[in] pBumpNormal The normal after bump adjustments.

      \param[in] pLightBlindData Custom light shader data.

      \return The diffuse factor for area lights.
    */
    inline float computeDiffuseAreaLightFactor(miVector &pBumpNormal,
                                               void *pLightBlindData) const
    {
        return 0.0f;
    }

    /*!
      \brief Computes the specular factor for area lights.

      This function computes the specular factor for area lights.

      \param[in] pBumpNormal The normal after bump adjustments.

      \param[in] pLightBlindData Custom light shader data.

      \return The specular factor for area lights.
    */
    inline float computeSpecularAreaLightFactor(miVector &pBumpNormal,
                                                void *pLightBlindData) const
    {
        return 0.0f;
    }

    /*!
      \brief Return the reflected color for this shader.

      Return the reflected color for this shader.

      \return The reflected color for this shader.
    */
    inline miColor getReflectedColor() const
    {
        return BLACK;
    }
};


/*!
  \brief Lambertian shader helper class.

  This class implements the same set of methods as the base ShaderHelper
  class for use with Lambertian materials.

  \tparam ShaderParameters The shader parameter structure.
*/
template<typename ShaderParameters>
class LambertianShaderHelper {
  public:

    /*!
      \brief Constructor for lambertian shader helper.

      This will be called once per evaluation of the main shading function
      for the shader. This stores the state and the parameters for use in
      various functions.

      \param[in,out] pState A pointer to the mental ray state structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    LambertianShaderHelper(miState *pState, ShaderParameters *pParameters) : state(pState),
                                                                             params(pParameters){};

    /*!
      \brief Deconstructor for lambertian shader helper.
      
      This will be called once per evaluation of the main shading function
      for the shader.
    */
    ~LambertianShaderHelper() {};

    /*!
      \brief Adjust normal for Maya's bump mapping.

      This function adjusts state->normal to account for bump mapping. Override
      it to change how bump mapping works.
    */
    inline void setupMayaBumpMapping(){
        if (MAYA_CONNECTED(&params->normalCamera))
        {
            float dot_nn;
            state->normal = *mi_eval_vector(&params->normalCamera);
            dot_nn = mi_vector_dot(&state->normal, &state->normal_geom);
            if (dot_nn < 0.0f)
            {
                dot_nn = -dot_nn+0.0015f; // Large epsilon!
                state->normal.x += dot_nn * state->normal_geom.x;
                state->normal.y += dot_nn * state->normal_geom.y;
                state->normal.z += dot_nn * state->normal_geom.z;
                mi_vector_normalize(&state->normal);
            }
            state->dot_nd = mi_vector_dot(&state->normal, &state->dir);
        }
    }

    /*!
      \brief Determine if source should be hidden.

      Most Maya shaders define the hideSource attribute to determine if the
      source geometry should be hidden (often used with glow). Override this
      to tell the main shading function whether or not the source should be
      hidden.

      \return True if source should be hidden, false otherwise.
    */
    inline miBoolean computeHideSource() const
    {
        return *mi_eval_boolean(&params->hideSource);
    }

    /*!
      \brief Computes transparency for shadow rays.
      
      This function computes the transparency of the shader when hit by
      a shadow ray.
      
      \param[out] pResTransp The resulting transparency.

      \param[in] pHideSource True if the source is hidden.
    */
    inline void computeTransparencyForShadow(miColor &pResTransp, miBoolean pHideSource) const
    {
        if (pHideSource)
        {
            pResTransp = WHITE;
        }
        else
        {
            pResTransp = *mi_eval_color(&params->transparency);
        }
    }

    /*!
      \brief Evaluates shader parameters necessary for later computations.
      
      This function is called after other initialization to give the helper
      a chance to evaluate any parameters necessary for later computations.
    */
    inline void evaluateParameters() {};

    /*!
      \brief Computes transparency parameters for non-shadow rays.

      This function is called to evaluate the transparency parameters for
      the shader on non-shadow rays.

      \return The transparency color for use in later computations.
    */
    inline miColor computeTransparency() const
    {
        return *mi_eval_color(&params->transparency);
    }

    /*!
      \brief Computes the specular glow parameters for the shader.

      This function is called to evaluate any specular glow parameters to
      the shader for use in later computations.

      \return The amount of specular glow.
    */
    inline miScalar computeSpecularGlow() const
    {
        return *mi_eval_scalar(&params->glowIntensity);
    }

    /*!
      \brief Set the ASQ weight for this shader call.

      This function adjusts the ASQ weight according to the light loop's
      impact on the final shader result.

      \param[in,out] MBS The current Maya state.

      \param[in] bc BRDF component information.

      \param[in] pColor The diffuse color for the shader.

      \param[in] pTransparency The transparency for the shader.

      \param[in] pGlowIntensity The glow intensity for the shader.
    */
    inline void setASQWeight(MayabaseState * &MBS,
                             BRDFComponent &bc,
                             const miColor &pColor,
                             const miColor &pTransparency,
                             miScalar &pGlowIntensity) const
    {
        if (!BC_HAS_LIGHT_SHADOW)
        {
            MBS->asqWeight.r *= pColor.r * (1.0f - pTransparency.r);
            MBS->asqWeight.g *= pColor.g * (1.0f - pTransparency.g);
            MBS->asqWeight.b *= pColor.b * (1.0f - pTransparency.b);
            if (pGlowIntensity > 1.0f)
            {
                MBS->asqWeight.r *= pGlowIntensity;
                MBS->asqWeight.g *= pGlowIntensity;
                MBS->asqWeight.b *= pGlowIntensity;
            }
        }
    }

    /*!
      \brief Computes the ambient result color.

      This function computes the color returned in the ambient channel
      of the shader result structure.

      \param[in] pAmbientColor The ambient color of the material.

      \param[in] pColor The diffuse color of the material.

      \return The ambient result.
    */
    inline miColor computeAmbientResult(const miColor &pAmbientColor,
                                        const miColor &pColor) const
    {
        return pAmbientColor * pColor;
    }

    /*!
      \brief Computes the translucence result for the shader.

      This function computes the translucence result for the shader given
      various parameters. This result is combined with the diffuse component
      to produce the diffuse result.

      \param[in] pDotNL The dot product between the light vector and the normal.

      \param[in] pLightDirection The light vector.

      \param[in] pTranslucence The amount of translucence for the material.

      \param[in] pTranslucenceFocus The translucence focus for the material.

      \param[in] pTranslucenceDepth The translucence depth for the material.

      \param[in] pLightBlindData Custom light shader data.

      \return The translucence result for the shader.
    */
    inline miScalar computeTranslucence(miScalar pDotNL,
                                        miVector &pLightDirection,
                                        miScalar pTranslucence,
                                        miScalar pTranslucenceFocus,
                                        miScalar pTranslucenceDepth,
                                        void *pLightBlindData) const
    {
        return compute_lambert_translucence(state,
                                            pDotNL,
                                            &pLightDirection,
                                            pTranslucence,
                                            pTranslucenceFocus,
                                            pTranslucenceDepth,
                                            pLightBlindData);
    }

    /*!
      \brief Computes the diffuse factor for area lights.

      This function computes the diffuse factor for area lights.

      \param[in] pBumpNormal The normal after bump adjustments.

      \param[in] pLightBlindData Custom light shader data.

      \return The diffuse factor for area lights.
    */
    inline float computeDiffuseAreaLightFactor(miVector &pBumpNormal,
                                               void *pLightBlindData) const
    {
        return arealight_lambertian_reflect(&state->point, &pBumpNormal, pLightBlindData);
    }

    /*!
      \brief Computes the specular factor for area lights.

      This function computes the specular factor for area lights.

      \param[in] pBumpNormal The normal after bump adjustments.

      \param[in] pLightBlindData Custom light shader data.

      \return The specular factor for area lights.
    */
    inline float computeSpecularAreaLightFactor(miVector &pBumpNormal,
                                                void *pLightBlindData) const
    {
        return 0.0f;
    }

    /*!
      \brief Return the reflected color for this shader.

      Return the reflected color for this shader.

      \return The reflected color for this shader.
    */
    inline miColor getReflectedColor() const
    {
        return BLACK;
    }

  public:
    /*!
      Pointer to the current mental ray state for this shader invocation.
    */
    miState *state;

    /*!
      Pointer to the shader parameters for this shader invocation.
    */
    ShaderParameters *params;
};


/*!
  \brief Specular shader helper class.

  This class extends LambertianShaderHelper to provide additional functionality
  for specular materials.

  \tparam ShaderParameters The shader parameter structure.
*/
template<typename ShaderParameters>
class SpecularShaderHelper : public LambertianShaderHelper<ShaderParameters> {
  public:

    /*!
      \brief Constructor for lambertian shader helper.

      This will be called once per evaluation of the main shading function
      for the shader. This stores the state and the parameters for use in
      various functions.

      \param[in,out] pState A pointer to the mental ray state structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    SpecularShaderHelper(miState *pState, ShaderParameters *pParameters) : LambertianShaderHelper<ShaderParameters>(pState, pParameters){};

    /*!
      \brief Deconstructor for lambertian shader helper.
      
      This will be called once per evaluation of the main shading function
      for the shader.
    */
    ~SpecularShaderHelper(){};

    /*!
      \brief Evaluates shader parameters necessary for later computations.
      
      This function is called after other initialization to give the helper
      a chance to evaluate any parameters necessary for later computations.
    */
    inline void evaluateParameters()
    {
        // GCC on linux does not pick up these members of the parent without
        // full qualification
        miState * const &state =  LambertianShaderHelper<ShaderParameters>::state;
        ShaderParameters * &params =  LambertianShaderHelper<ShaderParameters>::params;

        specularColor = *mi_eval_color(&params->specularColor);
        reflectedColor = *mi_eval_color(&params->reflectedColor);
    }

    /*!
      \brief Set the ASQ weight for this shader call.

      This function adjusts the ASQ weight according to the light loop's
      impact on the final shader result.

      \param[in,out] MBS The current Maya state.

      \param[in] bc BRDF component information.

      \param[in] pColor The diffuse color for the shader.

      \param[in] pTransparency The transparency for the shader.

      \param[in] pGlowIntensity The glow intensity for the shader.
    */
    inline void setASQWeight(MayabaseState * &MBS,
                             BRDFComponent &bc,
                             const miColor &pColor,
                             const miColor &pTransparency,
                             miScalar &pGlowIntensity) const
    {
        if (!BC_HAS_LIGHT_SHADOW)
        {
            const float diffR = pColor.r * (1.0f - pTransparency.r);
            const float diffG = pColor.g * (1.0f - pTransparency.g);
            const float diffB = pColor.b * (1.0f - pTransparency.b);
            MBS->asqWeight.r *= MAYA_MAX(diffR, specularColor.r);
            MBS->asqWeight.g *= MAYA_MAX(diffG, specularColor.g);
            MBS->asqWeight.b *= MAYA_MAX(diffB, specularColor.b);
            if (pGlowIntensity > 1.0f)
            {
                MBS->asqWeight.r *= pGlowIntensity;
                MBS->asqWeight.g *= pGlowIntensity;
                MBS->asqWeight.b *= pGlowIntensity;
            }
        }
    }

    /*!
      \brief Computes the specular factor for area lights.

      This function computes the specular factor for area lights.

      \param[in] pBumpNormal The normal after bump adjustments.

      \param[in] pLightBlindData Custom light shader data.

      \return The specular factor for area lights.
    */
    inline float computeSpecularAreaLightFactor(miVector &pBumpNormal,
                                                void *pLightBlindData)
    {
        // GCC on linux does not pick up these members of the parent without
        // full qualification
        miState * const &state = LambertianShaderHelper<ShaderParameters>::state;

        return arealight_lambertian_reflect(&state->point, &pBumpNormal, pLightBlindData);
    }

    /*!
      \brief Return the reflected color for this shader.

      Return the reflected color for this shader.

      \return The reflected color for this shader.
    */
    inline miColor getReflectedColor() const
    {
        return reflectedColor;
    }

  public:
    /*!
      The specular color for the material.
    */
    miColor specularColor;

    /*!
      The reflected color for the material.
    */
    miColor reflectedColor;
};


/*!
  \brief The base shader class.

  This class is the base shader class from which most of the Maya shaders are
  derived.

  \tparam ShaderParameters The shader parameter structure.

  \tparam ShaderHelper The shader helper to use with this shader.

  \tparam VERSION The version of this shader. Should match the version of the
                  shader declared in the .mi file.
*/
template <typename ShaderParameters, typename ShaderHelper, int VERSION = DEFAULT_SHADER_VERSION>
class Shader
{
  public:

    /*!
      \brief Shader constructor. This will be called once per
      shader instance, and is where data for each shader instance
      should be initialized.

      \param[in,out] pState A pointer to the mental ray state
      structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    Shader(miState *pState, ShaderParameters *pParameters);

    /*!
      \brief Shader destructor.
      
      The member variables \c mDestructorState and \c mDestructorParameters
      will be set correctly when the destructor is called.
    */
    virtual ~Shader();

    /*!
      \brief The shader initialization function.

      This function is called once at the begining of the
      rendering loop. This is where shaders should initialize and
      pre-compute data common to all instances of the shader.

      \param[in,out] pState A pointer to the mental ray state
      structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    static void init(miState *pState, ShaderParameters *pParameters);

    /*!
      \brief Function returning the current version of the shader.
    */
    static int version() {return VERSION;}

    /*!
      \brief The shader exit function.

      This function is called once after all calls to the shader
      have completed. This is where shaders should release any
      dynamically allocated resources.

      \param[in,out] pState A pointer to the mental ray state
      structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    static void exit(miState *pState, ShaderParameters *pParameters);

    /*!
      \brief Main shading function.
           
      This is the function which is called for shader samples.

      \param[out] pResult A pointer to the mental ray color result.

      \param[in,out] pState A pointer to the mental ray state
      structure.

      \param[in] pParameters A pointer to the shader parameters.

      \return True if the shader call was successful, false otherwise.
    */
    miBoolean operator()(miColor *pResult, miState *pState, ShaderParameters *pParameters);

    /*!
      Pointer to the mental ray state structure. This is only
      guaranteed to be valid during a call to the destructor.

      \note Some of the macros provided by mental images assume
      that the state variable is called \c state so it may be
      necessary to create a reference to this variable using that
      name for proper functionality, that is:

      \code
      miState * const &state = mDestructorState;
      \endcode
    */
    miState *mDestructorState; 

    /*!
      Pointer to the mental ray shader parameters. This is only
      guaranteed to be valid during a call to the destructor.
    */
    ShaderParameters *mDestructorParameters;
};

/*!
  \brief Material shader class.

  This class holds all data and behaviors which are specific to
  mental ray material shaders. It is an extension of the base class Shader.

  \tparam MaterialParameters The material parameter structure.

  \tparam ShaderHelper The shader helper to use with this shader.

  \tparam VERSION The version of this shader. Should match the version of the
                  shader declared in the .mi file.
*/
template<typename MaterialParameters,
         typename ShaderHelper,
         int VERSION = DEFAULT_SHADER_VERSION>
class Material : public Shader<MaterialParameters, ShaderHelper, VERSION>
{
  private:
    typedef Material<MaterialParameters, ShaderHelper, VERSION> MaterialBase;

  public:
    /*!
      \brief Material shader constructor.
      
      This will be called once per shader instance, and is where
      data for each shader instance should be initialized.

      \param[in,out] pState A pointer to the mental ray state structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    Material(miState *pState, MaterialParameters *pParameters);

    /*!
      \brief Material shader destructor.
      
      The member variables \c mDestructorState and \c mDestructorParameters
      will be set correctly when the destructor is called.
    */
    virtual ~Material();

    /*!
      \brief Main shading function.
           
      This is the function which is called for shader samples.

      \param[out] pResult A pointer to the mental ray color result.

      \param[in,out] pState A pointer to the mental ray state
      structure.

      \param[in] pParameters A pointer to the shader parameters.

      \return True if the shader call was successful, false otherwise.
    */
    miBoolean operator()(miColor *pResult, miState *pState, MaterialParameters *pParameters);

    /*!
      \brief Write to frame buffers of a given type.

      \param[in,out] pState The shading state

      \param[in,out] pFrameBufferInfo The array of frame buffer information structs

      \param[in] pPassTypeInfo The array of pass type information structs

      \param[in] pValue The value to be written to the frame buffer

      \param[in] pPassType The pass type ID that identifies the frame buffer to be written to

      \param[in] pUseIrradiance Set to true if the value should be modulated by 
      irradiance. This option should only be used inside a light loop.

      \param[in] pIrradianceNoShadow Sample irradiance without shadows, used to compute 
      differential shadow passes.  When non-null, the difference between pIrradianceNoShadow
      and the sample irradiance is used as a lighting factor, instead of the sample irradiance.
    */
    template<typename T>
    void writeToFrameBuffers( 
        miState*              pState,
        FrameBufferInfo*      pFrameBufferInfo,
        PassTypeInfo*         pPassTypeInfo,
        const T&              pValue, 
        PassTypeID            pPassType,
        const bool&           pUseIrradiance,
        const miColor* const& pIrradianceNoShadow = 0 );

  protected:
    miInteger   mFrameBufferWriteOperation;  //!< Operation to be performed on frame buffers.
    miInteger   mFrameBufferWriteFlags;      //!< Flags affecting the frame buffer operation.
    miScalar    mFrameBufferWriteFactor;     //!< Scaling factor for contribution if scaling is enabled.
};

/*!
  \brief Surface shader class.

  This class holds all data and behaviors which are specific to
  mental ray surface shaders. It is an extention of the Material class.

  \tparam SurfaceParameters The surface parameter structure.

  \tparam SurfaceResult The surface result structure.

  \tparam ShaderHelper The shader helper to use with this shader.

  \tparam AmbientMaterialColorComponent The ambient material color component to use with this shader.

  \tparam AmbientComponent The ambient component to use with this shader.

  \tparam DiffuseMaterialColorComponent The diffuse material color component to use with this shader.

  \tparam DiffuseComponent The diffuse component to use with this shader.

  \tparam SpecularComponent The specular component to use with this shader.

  \tparam ReflectionComponent The reflection component to use with this shader.

  \tparam RefractionComponent The refraction component to use with this shader.

  \tparam ScatterComponent The scatter component to use with this shader.

  \tparam IndirectComponent The indirect component to use with this shader.

  \tparam IncandescenceComponent The incandescence component to use with this shader.

  \tparam CustomComponent The custom component to use with this shader.

  \tparam VERSION The version of this shader. Should match the version of the
                  shader declared in the .mi file.
*/
template<typename SurfaceParameters,
         typename SurfaceResult,
         typename ShaderHelper,
         typename AmbientMaterialColorComponent = DefaultAmbientMaterialColorComponent<SurfaceParameters, ShaderHelper>,
         typename AmbientComponent = DefaultAmbientComponent<SurfaceParameters, ShaderHelper>,
         typename DiffuseMaterialColorComponent = DefaultDiffuseMaterialColorComponent<SurfaceParameters, ShaderHelper>,
         typename DiffuseComponent = DefaultDiffuseComponent<SurfaceParameters, ShaderHelper>,
         typename SpecularComponent = DefaultSpecularComponent<SurfaceParameters, ShaderHelper>,
         typename ReflectionComponent = DefaultReflectionComponent<SurfaceParameters, ShaderHelper>,
         typename RefractionComponent = DefaultRefractionComponent<SurfaceParameters, ShaderHelper>,
         typename ScatterComponent = DefaultScatterComponent<SurfaceParameters, ShaderHelper>,
         typename IndirectComponent = DefaultIndirectComponent<SurfaceParameters, ShaderHelper>,
         typename IncandescenceComponent = DefaultIncandescenceComponent<SurfaceParameters, ShaderHelper>,
         typename CustomComponent = DefaultCustomComponent<SurfaceParameters, SurfaceResult, ShaderHelper>,
         int VERSION = DEFAULT_SHADER_VERSION>
class Surface : public Material<SurfaceParameters, ShaderHelper, VERSION> {
  private:
    typedef Material<SurfaceParameters, ShaderHelper, VERSION> MaterialBase;

  public:
    /*!
      \brief Surface shader constructor.
      
      This will be called once per shader instance, and is where data
      for each shader instance should be initialized.

      \param[in,out] pState A pointer to the mental ray state structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    Surface(miState *pState, SurfaceParameters *pParameters);

    /*!
      \brief Surface shader destructor.
      
      The member variables \c mDestructorState and \c mDestructorParameters
      will be set correctly when the destructor is called.
    */
    virtual ~Surface();

    /*!
      \brief Main shading function.
           
      This is the function which is called for shader samples.

      \param[out] pResult A pointer to the mental ray surface shader result struct.

      \param[in,out] pState A pointer to the mental ray state
      structure.

      \param[in] pParameters A pointer to the shader parameters.
    */
    miBoolean operator()(SurfaceResult *pResult, miState *pState, SurfaceParameters *pParameters);

    /*!
      Scatter user data pointer
    */
    void* mScatterData;
};

// Shader method implementations

template <typename ShaderParameters, typename ShaderHelper, int VERSION>
Shader<ShaderParameters, ShaderHelper, VERSION>::Shader(miState *pState, ShaderParameters *pParameters)
{
}

template <typename ShaderParameters, typename ShaderHelper, int VERSION>
Shader<ShaderParameters, ShaderHelper, VERSION>::~Shader()
{
}

template <typename ShaderParameters, typename ShaderHelper, int VERSION>
void Shader<ShaderParameters, ShaderHelper, VERSION>::init(miState *pState, ShaderParameters *pParameters)
{
}

template <typename ShaderParameters, typename ShaderHelper, int VERSION>
void Shader<ShaderParameters, ShaderHelper, VERSION>::exit(miState *pState, ShaderParameters *pParameters)
{
}

template <typename ShaderParameters, typename ShaderHelper, int VERSION>
miBoolean Shader<ShaderParameters, ShaderHelper, VERSION>::operator()(miColor *pResult,
                                                                      miState *pState,
                                                                      ShaderParameters *pParameters)
{
    adskWarning("Shader::operator() was called. Should be eclipsed by derived class implementation.");
    return miTRUE;
}

// Material method implementations

template <typename MaterialParameters,
          typename ShaderHelper,
          int VERSION>
Material<MaterialParameters,
         ShaderHelper,
         VERSION>::Material(miState *pState, MaterialParameters *pParameters) : Shader<MaterialParameters, ShaderHelper, VERSION>(pState, pParameters)
{
    // For mental images macros
    miState * const &state = pState;

    // Set up the operation, flags, and factor
    mFrameBufferWriteOperation = *mi_eval_integer(&pParameters->FrameBufferWriteOperation);
    mFrameBufferWriteFlags = *mi_eval_integer(&pParameters->FrameBufferWriteFlags);
    mFrameBufferWriteFactor = *mi_eval_scalar(&pParameters->FrameBufferWriteFactor);
}

template <typename MaterialParameters,
          typename ShaderHelper,
          int VERSION>
Material<MaterialParameters,
         ShaderHelper,
         VERSION>::~Material()
{
}


template <typename MaterialParameters,
          typename ShaderHelper,
          int VERSION>
miBoolean Material<MaterialParameters,
                   ShaderHelper,
                   VERSION>::operator()(miColor *pResult,
                                        miState *pState,
                                        MaterialParameters *pParameters)
{
    return miTRUE;
}

template<typename MaterialParameters, 
         typename ShaderHelper, 
         int VERSION>
template<typename T>
void Material<MaterialParameters, 
              ShaderHelper, 
              VERSION>::writeToFrameBuffers(miState*              pState,
                                            FrameBufferInfo*      pFrameBufferInfo,
                                            PassTypeInfo*         pPassTypeInfo,
                                            const T&              pValue, 
                                            PassTypeID            pPassType,
                                            const bool&           pUseIrradiance,
                                            const miColor* const& pIrradianceNoShadow )
{
    operateOnFrameBuffersOfType(
        pState,
        pValue,
        pFrameBufferInfo,
        pPassTypeInfo,
        pPassType,
        mFrameBufferWriteOperation,
        mFrameBufferWriteFlags,
        mFrameBufferWriteFactor,
        pUseIrradiance,
        pIrradianceNoShadow );
}

// Surface shader method implementations

template <typename SurfaceParameters,
          typename SurfaceResult,
          typename ShaderHelper,
          typename AmbientMaterialColorComponent,
          typename AmbientComponent,
          typename DiffuseMaterialColorComponent,
          typename DiffuseComponent,
          typename SpecularComponent,
          typename ReflectionComponent,
          typename RefractionComponent,
          typename ScatterComponent,
          typename IndirectComponent,
          typename IncandescenceComponent,
          typename CustomComponent,
          int VERSION>
Surface<SurfaceParameters,
        SurfaceResult,
        ShaderHelper,
        AmbientMaterialColorComponent,
        AmbientComponent,
        DiffuseMaterialColorComponent,
        DiffuseComponent,
        SpecularComponent,
        ReflectionComponent,
        RefractionComponent,
        ScatterComponent,
        IndirectComponent,
        IncandescenceComponent,
        CustomComponent,
        VERSION>::Surface(miState *pState, SurfaceParameters *pParameters) : 
            Material<SurfaceParameters, ShaderHelper, VERSION>(pState, pParameters),
            mScatterData(0)
{
}

template <typename SurfaceParameters,
          typename SurfaceResult,
          typename ShaderHelper,
          typename AmbientMaterialColorComponent,
          typename AmbientComponent,
          typename DiffuseMaterialColorComponent,
          typename DiffuseComponent,
          typename SpecularComponent,
          typename ReflectionComponent,
          typename RefractionComponent,
          typename ScatterComponent,
          typename IndirectComponent,
          typename IncandescenceComponent,
          typename CustomComponent,
          int VERSION>
Surface<SurfaceParameters,
        SurfaceResult,
        ShaderHelper,
        AmbientMaterialColorComponent,
        AmbientComponent,
        DiffuseMaterialColorComponent,
        DiffuseComponent,
        SpecularComponent,
        ReflectionComponent,
        RefractionComponent,
        ScatterComponent,
        IndirectComponent,
        IncandescenceComponent,
        CustomComponent,
        VERSION>::~Surface()
{
    miState * const &state = Shader<SurfaceParameters, ShaderHelper, VERSION>::mDestructorState;
    destroy_scatter(state, &mScatterData);
}

template <typename SurfaceParameters,
          typename SurfaceResult,
          typename ShaderHelper,
          typename AmbientMaterialColorComponent,
          typename AmbientComponent,
          typename DiffuseMaterialColorComponent,
          typename DiffuseComponent,
          typename SpecularComponent,
          typename ReflectionComponent,
          typename RefractionComponent,
          typename ScatterComponent,
          typename IndirectComponent,
          typename IncandescenceComponent,
          typename CustomComponent,
          int VERSION>
miBoolean Surface<SurfaceParameters,
                  SurfaceResult,
                  ShaderHelper,
                  AmbientMaterialColorComponent,
                  AmbientComponent,
                  DiffuseMaterialColorComponent,
                  DiffuseComponent,
                  SpecularComponent,
                  ReflectionComponent,
                  RefractionComponent,
                  ScatterComponent,
                  IndirectComponent,
                  IncandescenceComponent,
                  CustomComponent,
                  VERSION>::operator()(SurfaceResult *pResult,
                                       miState *pState,
                                       SurfaceParameters *pParameters)
{
    // to make the mental images and mayabase macros work
    miState * const &state = pState;

    MBS_SETUP(pState);

    // Set up custom component and see if we will break from shading early
    CustomComponent lCustomComponent(pState, pParameters);
    miBoolean scResult = miTRUE;
    if (lCustomComponent.shortCircuitShading(pState, pParameters, pResult, &scResult))
    {
        return scResult;
    }

    const miVector normal = state->normal;
    const miScalar dot_nd = state->dot_nd;

    BRDFComponent bc;

    miColor   resAmbient;
    miColor   resIncandescence;
    miColor   resDiff[2] = { BLACK, BLACK };
    miColor   resSpec[2] = { BLACK, BLACK };
    miColor   resIrradiance;
    miColor   resScatter;
    miColor   resRefl;
    miColor   resRefr;
    float     resShadow = 0.0f;

    miColor   color;
    miColor   transparency;
    miScalar  translucence;
    miScalar  glowIntensity;
    miScalar  specularGlow;
    miScalar  translucenceFocus = 0.0f;
    miScalar  translucenceDepth = 0.0f;
    miVector  bumpNormal;
    miVector  reflDirection;
    miBoolean refractions;
    miBoolean hideSource;
            
    MBS_ASSERT("AdskShaderSDK")

        // Fetch frame buffer information
        PassTypeInfo* passTypeInfo;
    FrameBufferInfo* frameBufferInfo;
    unsigned int numberOfFrameBuffers = 
        getFrameBufferInfo(state, passTypeInfo, frameBufferInfo);

    // Set up the shading helper function whose behaviour changes
    // depending on the type of shader.
    ShaderHelper lShaderHelper(pState, pParameters);

    // play nice with Maya's bump mapping
    lShaderHelper.setupMayaBumpMapping();
    // Uninverted normal, for lighting in mi_sample_light().
    bumpNormal = pState->normal;

    // hide source?
    hideSource = lShaderHelper.computeHideSource();

    // If the current ray type is MI_RAY_SHADOW this shader must have
    // been called from maya_shadow(). Calculate only transparency and
    // return it in outTransparency for the shadow shader to pick up.
    if (pState->type == miRAY_SHADOW)
    {
        lShaderHelper.computeTransparencyForShadow(pResult->transparency, hideSource);
        // Return to shadow shader.
        return miTRUE;
    }
    
    if (!pState->environment)
    {
        pState->environment = pState->camera->environment;
    }
    
    // Initialize BRDF components.
    bc_construct(&bc, MBS->options.renderPass, state);
    // Zero out all elements of the return structure.
    memset(pResult, 0, sizeof(SurfaceResult));
        
    // Set up the shading components
    AmbientMaterialColorComponent lAmbientMaterialColorComponent(pState, pParameters);
    AmbientComponent lAmbientComponent(pState, pParameters);
    DiffuseMaterialColorComponent lDiffuseMaterialColorComponent(pState, pParameters);
    DiffuseComponent lDiffuseComponent(pState, pParameters);
    SpecularComponent lSpecularComponent(pState, pParameters);
    ReflectionComponent lReflectionComponent(pState, pParameters);
    RefractionComponent lRefractionComponent(pState, pParameters);
    ScatterComponent lScatterComponent(pState, pParameters);
    IndirectComponent lIndirectComponent(pState, pParameters);
    IncandescenceComponent lIncandescenceComponent(pState, pParameters);

    // Evaluate the necessary parameters
    lShaderHelper.evaluateParameters();
    color = lDiffuseMaterialColorComponent(pState, pParameters, lShaderHelper);
    transparency = lShaderHelper.computeTransparency();
    translucence = *mi_eval_scalar(&pParameters->translucence);
    bool blackHole = (*mi_eval_integer(&pParameters->matteOpacityMode) == MATTEMODE_BLACKHOLE)?true:false;
    if (translucence)
    {
        translucenceFocus = *mi_eval_scalar(&pParameters->translucenceFocus);
        translucenceDepth = *mi_eval_scalar(&pParameters->translucenceDepth);
    }

    reflDirection.x = state->dir.x - 2.0f * state->dot_nd * state->normal.x;
    reflDirection.y = state->dir.y - 2.0f * state->dot_nd * state->normal.y;
    reflDirection.z = state->dir.z - 2.0f * state->dot_nd * state->normal.z;
    glowIntensity = *mi_eval_scalar(&pParameters->glowIntensity);
    specularGlow = lShaderHelper.computeSpecularGlow();

    // light loop

    const miColor asqWeight = MBS->asqWeight;
    LightDataArray *inLightData = &MBS->lightData;
    float resPreShadowIntensity = 0.0f;

    miTag *lights;
    int numLights;
    miColor  *preShadowColor = &inLightData->preShadowColor;
    miScalar *shadowFraction = &inLightData->shadowFraction;
    void    **lightBlindData = &inLightData->lightBlindData;

    // Adaptive Shading Quality (ASQ)

    // If a shader is found to contribute only little to the current
    // pixel sample, it may shade at reduced quality. The contribution
    // of a shader is proportional to asqWeight, which is itself
    // maintained by the shaders.

    // For example, the direct diffuse lighting component is scaled by
    // color*(1 - transparency). For small color and/or large
    // transparency, diffuse lighting will have only little impact on
    // the shader result. We scale asqWeight by the same factor. If
    // light shaders find sufficiently small asqWeight they might
    // reduce shadow quality or cast no shadows at all, because the
    // difference would not be noticeable anyway.

    /* ASQ:: adjust ASQ weight according to the light loop's impact on
     * the final shader result. Five values are computed here: resDiff[0],
     * resDiff[1], resSpec[0], resSpec[1] and resShadow. The first four are
     * later scaled by color/transparency, specularColor. But resShadow is
     * not scaled - ASQ must not be changed if BC_HAS_LIGHT_SHADOW is on!
     */

    lShaderHelper.setASQWeight(MBS, bc, color, transparency, glowIntensity);

    // the ambient material color
    miColor lAmbientMaterialColor = lAmbientMaterialColorComponent(pState, pParameters, lShaderHelper);

    // the diffuse material color
    miColor lMaterialColor = color;
    miColor lDiffuseMaterialColor = color*(*mi_eval_scalar(&pParameters->diffuse));

    if (numberOfFrameBuffers && 
        MaterialBase::mFrameBufferWriteOperation)
    {
        if (!blackHole)
        {
            // add values to the appropriate passes
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(lAmbientMaterialColor), AMBIENT_MATERIAL_COLOR, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(lDiffuseMaterialColor), DIFFUSE_MATERIAL_COLOR, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(lShaderHelper.getReflectedColor()), REFLECTED_MATERIAL_COLOR, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(transparency), REFRACTION_MATERIAL_COLOR, false);
        }
        // material normal passes must be handled differently since they have a parameter associated with them
        operateOnNormalMaterialFrameBuffersOfType(state, state->normal, frameBufferInfo, passTypeInfo,
                                                  MaterialBase::mFrameBufferWriteOperation,
                                                  MaterialBase::mFrameBufferWriteFlags,
                                                  MaterialBase::mFrameBufferWriteFactor);
    }

    // write to the ouput connection since we already have the necessary values
    if (!BC_HAS_AMBIENT)
    {
        resAmbient = BLACK;
    }
    else
    {
        resAmbient = lShaderHelper.computeAmbientResult(lAmbientMaterialColor, lMaterialColor);
    }

    // go through each light
    mi_instance_lightlist(&numLights, &lights, state);
    /* Evaluate all lights in the list. */
    for ( ; numLights--; lights++)
    {
        int backsideCnt = 2;
        
        // Custom light shader might not have set light data.
        *inLightData = defaultLightDataArray;
        // Do not compute shadows unless it is required.
        inLightData->canDropShadow = !BC_HAS_DIRECTILLUM_SH;

        // Some shading effects (ambientLight, translucence) require
        // lights to be sampled on both sides of the current
        // primitive.  We can not set state->pri to zero, because this
        // brings about shadow tolerance issues. So we just sample
        // twice, once with inverted normals. Because normal inversion
        // is a workaround, all lighting computations must use the
        // original normal.

        // NOTE: lights located on the backside always have cos_nl <
        // 0.
        while (backsideCnt--)
        {
            int      samples = 0;
            miColor  lightColor;
            miVector lightDirection;
            miScalar dotNL;
            miColor  directIrradianceSum = BLACK;
            miColor  directIrradianceNoShadowSum = BLACK;
            miColor  diffuseSum = BLACK;
            miColor  diffuseNoShadowSum = BLACK;
            miColor  specularSum = BLACK;
            miColor  specularNoShadowSum = BLACK;
            miColor  ambientSum = BLACK;
            miColor  ambientNoShadowSum = BLACK;
            miColor  translucenceSum = BLACK;
            miColor  translucenceNoShadowSum = BLACK;
            float    lightNormalIncidenceSum = 0.f;
            int      lightNormalIncidenceCount = 0;
            float    shadowSum = 0.f;
            float    preShadowIntensitySum = 0.f;

            // samples on current light
            sampleLightBegin(numberOfFrameBuffers, frameBufferInfo);
            while (mi_sample_light(&lightColor, &lightDirection, &dotNL, state, *lights, &samples))
            {
                handleNonAdskLights(numberOfFrameBuffers, frameBufferInfo, lightColor, *lights, state);

                // Account for normal inversion
                if (inLightData->normalInverted)
                {
                    dotNL = -dotNL;
                }

                miColor unlitAmbient = BLACK;
                // does the current light emit ambient light?
                if (inLightData->lightAmbient)
                {
                    // Maya actually multiplies the ambient color by
                    // the material color before adding. Keep this to
                    // give the same shading result.
                    unlitAmbient = lAmbientComponent(state, pParameters, lShaderHelper, color);
                    ambientSum = ambientSum + unlitAmbient*lightColor;
                    ambientNoShadowSum = ambientNoShadowSum + unlitAmbient*(*preShadowColor);
                    MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                      WHITE, AMBIENT_IRRADIANCE, true);
                    if (!blackHole)
                    {
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(unlitAmbient), AMBIENT, true);
                    }
                }
                
                miColor unlitTranslucence = BLACK;
                miColor unlitDiffuse = BLACK;
                // does the current light emit direct light?
                if (inLightData->lightDiffuse)
                {
                    // is it an area light?
                    if (*lightBlindData)
                    {
                        dotNL = lShaderHelper.computeDiffuseAreaLightFactor(bumpNormal, *lightBlindData);
                    }

                    // add the direct irradiance color
                    if (dotNL > 0.f)
                    {
                        directIrradianceSum = directIrradianceSum + (lightColor * dotNL);
                        directIrradianceNoShadowSum = directIrradianceNoShadowSum + ((*preShadowColor) * dotNL);
                        miColor irradianceFactor = dotNL*WHITE;
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(irradianceFactor), DIRECT_IRRADIANCE, true);
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(irradianceFactor * (*preShadowColor)), DIRECT_IRRADIANCE_NO_SHADOW, false);
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(irradianceFactor), RAW_SHADOW, true, preShadowColor);
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          dotNL, RAW_SHADOW_MONO, true, preShadowColor);
                    }

                    if (BC_HAS_LIGHT_SHADOW)
                    {
                        const float preShadowIntensity = MAYA_LUMINANCE(*preShadowColor);
                        if (dotNL > 0.f)
                        {
                            shadowSum = shadowSum + (*shadowFraction * preShadowIntensity);
                        }
                        preShadowIntensitySum += preShadowIntensity;
                    }

                    if (translucence)
                    {
                        miScalar translucenceFactor = lShaderHelper.computeTranslucence(dotNL,
                                                                                        lightDirection,
                                                                                        translucence,
                                                                                        translucenceFocus,
                                                                                        translucenceDepth,
                                                                                        *lightBlindData);

                        unlitTranslucence = translucenceFactor * color;

                        if (!blackHole)
                        {
                            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                              opaqueColor(unlitTranslucence), TRANSLUCENCE, true);
                            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                              opaqueColor(unlitTranslucence * (*preShadowColor)), TRANSLUCENCE_NO_SHADOW, false);
                        }

                        miColor litTranslucence = unlitTranslucence * lightColor;
                        miColor translucenceNoShadowTemp = translucenceFactor * (*preShadowColor) * color;

                        translucenceSum = translucenceSum + litTranslucence;
                        translucenceNoShadowSum = translucenceNoShadowSum + translucenceNoShadowTemp;

                        diffuseSum = diffuseSum + litTranslucence;
                        diffuseNoShadowSum = diffuseNoShadowSum + translucenceNoShadowTemp;
                    }

                    unlitDiffuse = lDiffuseComponent(state,
                                                     pParameters,
                                                     lShaderHelper,
                                                     color,
                                                     lightDirection,
                                                     dotNL,
                                                     *lightBlindData);

                    diffuseSum = diffuseSum + unlitDiffuse * lightColor;
                    diffuseNoShadowSum = diffuseNoShadowSum + unlitDiffuse* (*preShadowColor);

                    if (!blackHole)
                    {
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(unlitDiffuse + unlitTranslucence), DIFFUSE, true);
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor((unlitDiffuse + unlitTranslucence) * (*preShadowColor)), DIFFUSE_NO_SHADOW, false);
                    }
                }

                // this needs to be here to allow dotNL to be changed
                // by the area light calculation
                lightNormalIncidenceSum += (dotNL + 1.f) / 2.f; // map to 0 .. 1
                // we have to keep a separate sample count for the light normal incidence
                ++lightNormalIncidenceCount;                    

                miColor unlitSpecular = BLACK;
                // does the light emit specular light?
                if (inLightData->lightSpecular)
                {
                    // is it an area light?
                    if (*lightBlindData)
                    {
                        float factor;
                        arealight_max_phong_spec_dir(&state->point, &reflDirection, *lightBlindData, 
                                                     *lights, &lightDirection);
                        dotNL = mi_vector_dot(&bumpNormal, &lightDirection);
                        factor = lShaderHelper.computeSpecularAreaLightFactor(bumpNormal, *lightBlindData);
                        if (BC_HAS_LIGHT_SPEC)
                        {
                            lightColor.r *= factor;
                            lightColor.g *= factor;
                            lightColor.b *= factor;
                        }
                        if (BC_HAS_LIGHT_SPEC_NOSH)
                        {
                            preShadowColor->r *= factor;
                            preShadowColor->g *= factor;
                            preShadowColor->b *= factor;
                        }
                    }
                    // add the specular component
                    unlitSpecular = lSpecularComponent(state,
                                                       pParameters,
                                                       lShaderHelper,
                                                       lightDirection,
                                                       reflDirection,
                                                       dotNL,
                                                       bumpNormal);
                    specularSum = specularSum + lightColor * unlitSpecular;
                    specularNoShadowSum = specularNoShadowSum + (*preShadowColor) * unlitSpecular;

                    if ( !blackHole )
                    {
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(unlitSpecular), SPECULAR, true);
                        MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                          opaqueColor(unlitSpecular * (*preShadowColor)), SPECULAR_NO_SHADOW, false);
                    }
                }

                miColor unlitBeauty =
                    (unlitSpecular + (unlitDiffuse + unlitTranslucence + unlitAmbient) * (WHITE - transparency));

                if ( !blackHole )
                {
                    MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                      opaqueColor(unlitBeauty), SHADOW, true, preShadowColor);
                    MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                      MAYA_LUMINANCE(unlitBeauty), SHADOW_MONO, true, preShadowColor);
                    MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                      opaqueColor(unlitBeauty), BEAUTY, true );
                    MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                      opaqueColor(unlitBeauty * (*preShadowColor)), BEAUTY_NO_SHADOW, false );
                }

                // do custom component
                lCustomComponent(state, pParameters, lShaderHelper, color, lightDirection, dotNL);
            }
            sampleLightEnd(state,
                           numberOfFrameBuffers,
                           frameBufferInfo,
                           samples,
                           MaterialBase::mFrameBufferWriteOperation,
                           MaterialBase::mFrameBufferWriteFlags,
                           MaterialBase::mFrameBufferWriteFactor);

            // average the sample contributions
            if (samples > 1)
            {
                float  sampleWeight = 1.f / samples;
                directIrradianceSum = directIrradianceSum * sampleWeight;
                directIrradianceNoShadowSum = directIrradianceNoShadowSum * sampleWeight;
                ambientSum = ambientSum * sampleWeight;
                ambientNoShadowSum = ambientNoShadowSum * sampleWeight;
                diffuseSum = diffuseSum * sampleWeight;
                diffuseNoShadowSum = diffuseNoShadowSum * sampleWeight;
                specularSum = specularSum * sampleWeight;
                specularNoShadowSum = specularNoShadowSum * sampleWeight;
                shadowSum = shadowSum * sampleWeight;
                preShadowIntensitySum = preShadowIntensitySum * sampleWeight;
                translucenceSum = translucenceSum * sampleWeight;
                translucenceNoShadowSum = translucenceNoShadowSum * sampleWeight;
            }
            // light normal incidence is special and has its own count
            if (lightNormalIncidenceCount > 1)
            {
                lightNormalIncidenceSum = lightNormalIncidenceSum / lightNormalIncidenceCount;
            }
            // tell custom component the number of samples
            lCustomComponent.adjustForSamples(lShaderHelper, samples);

            // were there any samples for this light?
            if (samples > 0)
            {
                // set up the relevant Maya outputs
                if (BC_HAS_LIGHT_DIFF)
                {
                    resDiff[0] = resDiff[0] + diffuseSum + ambientSum;
                }
                if (BC_HAS_LIGHT_DIFF_NOSH)
                {
                    resDiff[1] = resDiff[1] + diffuseNoShadowSum + ambientNoShadowSum;
                }
                if (BC_HAS_LIGHT_SPEC)
                {
                    resSpec[0] = resSpec[0] + specularSum;
                }
                if (BC_HAS_LIGHT_SPEC_NOSH)
                {
                    resSpec[1] = resSpec[1] + specularNoShadowSum;
                }
                resShadow             = resShadow  + shadowSum;
                resPreShadowIntensity = resPreShadowIntensity + preShadowIntensitySum;

                MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo,
                                                  lightNormalIncidenceSum, INCIDENCE_LIGHT_NORMAL, false);
            }
            /* Blobby surfaces have state->pri==0 because they are computed
             * in a volume shader. Lights must not be sampled twice in this
             * case.
             */
            if (!state->pri)
            {
                break;
            }

            inLightData->normalInverted = !inLightData->normalInverted;
            mi_vector_neg(&state->normal_geom);
            mi_vector_neg(&state->normal);
        }
    }
    
    /* Like 'normalInverted', 'canDropShadow' must always be reset to
     * miFALSE before leaving a shader. Otherwise custom shaders, which
     * might not set this value, might not get shadows.
     */
    inLightData->canDropShadow = miFALSE;

    if (BC_HAS_LIGHT_SHADOW)
    {
        if (resPreShadowIntensity > MAYA_EPS)
        {
            resShadow /= resPreShadowIntensity;
        }
    }

    MBS->asqWeight = asqWeight;

    // Trace refractions and compute transparency.
    hideSource  = lShaderHelper.computeHideSource();
    refractions = *mi_eval_boolean(&pParameters->refractions);
    miScalar frameBufferScale = 
        (MaterialBase::mFrameBufferWriteFlags & FB_WRITE_FLAG_SCALED)?
        MaterialBase::mFrameBufferWriteFactor:1.0f;
    resRefr = lRefractionComponent(pState,
                                   pParameters,
                                   lShaderHelper,
                                   pResult->transparency,
                                   transparency,
                                   hideSource,
                                   BC_HAS_REFRACTION ? refractions : miFALSE,
                                   numberOfFrameBuffers,
                                   frameBufferInfo,
                                   passTypeInfo,
                                   frameBufferScale);

    // compute the reflections
    resRefl = BLACK;
    if (BC_HAS_REFLECTION)
    {
        resRefl = lReflectionComponent(pState,
                                       pParameters,
                                       lShaderHelper,
                                       reflDirection,
                                       hideSource,
                                       glowIntensity,
                                       numberOfFrameBuffers,
                                       frameBufferInfo,
                                       passTypeInfo,
                                       frameBufferScale);
    }

    // scatter
    resScatter = BLACK;
    if (BC_HAS_SCATTER)
    {
        resScatter = lScatterComponent(pState,
                                       pParameters,
                                       lShaderHelper,
                                       &mScatterData);
    }

    // add the indirect illumination
    if (!BC_HAS_IRRADIANCE)
    {
        resIrradiance = BLACK;
    }
    else
    {
        resIrradiance = lIndirectComponent(pState, pParameters, lShaderHelper, color, transparency);
    }

    // add the incandescence
    if (!BC_HAS_INCANDESCENCE)
    {
        resIncandescence = BLACK;
    }
    else
    {
        resIncandescence = lIncandescenceComponent(pState, pParameters, lShaderHelper);
    }

    // Do standard maya compositing on the main shading result
    bc_composite(
        bc,
        // Results
        (SurfaceShaderReturnType*)pResult, // assume result starts the same as base surface result
        &resAmbient, &resIncandescence, &resIrradiance,
        resDiff, resShadow, resSpec, &resRefl, &resRefr, &resScatter,
        // Parameters
        &transparency, glowIntensity, specularGlow, hideSource,
        *mi_eval_integer(&pParameters->matteOpacityMode),
        *mi_eval_scalar(&pParameters->matteOpacity));
    
    bc_destruct(&bc);

    // allow custom component to set results
    lCustomComponent.adjustFinalResult(pState, pParameters, pResult, lShaderHelper);

    // add the contributions to the frame buffers if this is a primary ray
    if (numberOfFrameBuffers && 
        MaterialBase::mFrameBufferWriteOperation)
    {
        // add to the appropriate passes
        if (!blackHole)
        {
            // incidence (camera / normal)
            // Product design wants a value of 0 if the surface points towards
            // the camera, and 1 if it is >= 90 degrees
            // This is the same as reversing the eye ray so it's pointing away
            // from the surface
            miScalar lIncidenceCameraNormal = -pState->dot_nd; 
            if (lIncidenceCameraNormal < 0.f)
            {
                lIncidenceCameraNormal = 1.f;             // clamp
            }
            else
            {
                lIncidenceCameraNormal = 1.f - lIncidenceCameraNormal;     // "reverse" the meaning of the dot product
            }

            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(resRefr), REFRACTION, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(resRefl), REFLECTION, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(resScatter), SCATTER, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(resIrradiance), INDIRECT, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(resIncandescence), INCANDESCENCE, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(pResult->glowColor), GLOW_SOURCE, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              lIncidenceCameraNormal, INCIDENCE_CAMERA_NORMAL, false);
            MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                              opaqueColor(resAmbient), AMBIENT, false);

            // add all of the non-light specific contributions to the
            // custom beauty passes
            miColor beauty = BLACK;
            if (!hideSource)
            {
                // Note: Reflections and refractions and direct lighting were already added to the beauty passes
                beauty = (resIrradiance + resScatter) * (WHITE - transparency) 
                    + resIncandescence + resAmbient;
                beauty.a = pParameters->matteOpacity;
                // add additional stuff to the beauty
                lCustomComponent.adjustBeautyResult(pState, pParameters, lShaderHelper, beauty);
                MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                  opaqueColor(beauty), BEAUTY, false);
                MaterialBase::writeToFrameBuffers(state, frameBufferInfo, passTypeInfo, 
                                                  opaqueColor(beauty), BEAUTY_NO_SHADOW, false);
            }
        }
    }

    // Must inform shadingEngine.
    MBS->refr = refractions;

    // Restore dot_nd and normal.
    state->dot_nd = dot_nd;
    state->normal = normal;
    return miTRUE;
}

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif  // __cplusplus
#endif // ADSK_SHADER_H
