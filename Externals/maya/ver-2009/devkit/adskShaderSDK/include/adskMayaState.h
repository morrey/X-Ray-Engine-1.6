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
  \brief Structures and functions for manipulating the Maya state.
*/

#ifndef ADSK_MAYASTATE_H
#define ADSK_MAYASTATE_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

#ifndef ADSK_CONSTANTS_H
#include "adskConstants.h"
#endif

#ifndef ADSK_MI_DATA_PTR_H
#include "adskMIDataPtr.h"
#endif

#ifndef ADSK_EXPORT_H
#include <adskExport.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

//! \cond DOCUMENT_MAYA_STATE

/* Stack.
 */

struct Stack {
    void        *head;
    int         numItems;
    miMemblk    *arena;
};

/* Types.
 */

typedef enum {
    RENDERPASS_BEAUTY = 0,
    RENDERPASS_COLOR,
    RENDERPASS_SHADOW,
    RENDERPASS_AMBIENT,
    RENDERPASS_DIFFUSE,
    RENDERPASS_SPECULAR,
    RENDERPASS_GLOBILLUM
} RenderPass;

struct MayaOptions {
    RenderPass  renderPass;
    miInteger   shadowLimit;
    miInteger   glowColorBuffer;
    miBoolean   passAlphaThrough;
    miBoolean   passLabelThrough;
    miBoolean   passDepthThrough;
    miBoolean   computeFilterSize;
    miScalar    defaultFilterSize;
    miInteger   refractionBlurLimit;
    miInteger   reflectionBlurLimit;
    miBoolean   aggressiveCaching;
    miScalar    asqMinThreshold;
    miScalar    asqMaxThreshold;
    miBoolean   asqShaderGlow;
};

struct FrameConstants {
    miScalar    xPixelAngle;
    miVector    OOPixelEyePos;
    miVector    OOPixelOffset;
    miBoolean   computeDepth;
    float       depthThreshold;
    float       depthCoeffs[4];
};

struct LightDataArray {
    miBoolean   lightAmbient;       /* contribute to ambient? */
    miBoolean   lightDiffuse;       /* contribute to diffuse? */
    miBoolean   lightSpecular;      /* contribute to specular? */
    miScalar    shadowFraction;     /* percentage of shadowing */
    miColor     preShadowColor;     /* pre-shadow color */
    void        *lightBlindData;    /* area light blind data */
    miBoolean   normalInverted;     /* has normal been inverted? */
    miBoolean   canDropShadow;      /* can shadows be left out? */
};

struct ParticleState {
    int         id;
    float       age;
    float       lifespan;
    float       weight;
    miColor     color;
    miColor     transparency;
    miColor     incandescence;
    float       userScalar[5];
    miVector    userVector[5];
    miColor     emission;
    miVector    pointWorld;
    miVector    farPointWorld;
    miMatrix    globalToLocal;
    miMatrix    localToGlobal;
};

struct Hit {                /* depth stack fragment */
    struct Hit  *next;
    float       transparency;
    float       depth;
};

struct MayabaseState {
    MayaOptions     options;        /* Maya render options */
    FrameConstants  frameConstants;     /* per-frame constants */
    LightDataArray  lightData;      /* the light data array */
    ParticleState   particle;       /* data for current particle */
    miBoolean       refr;
/* ---  miColor     accColor;        * is mi_trace*() parameter */
    miColor         accGlowColor;
    miColor         accMatteOpacity;
    miColor         accTransparency;
    miVector        uvFilterSize;
    miVector        filterSize;
    unsigned int    infoBits;
    Stack           depthStack;
#ifdef ALIAS_MERGE_VOLUME_INTERVALS
    Stack           volumeStack;
#endif
    miColor         asqWeight;
};

struct OptionsData {
    miInteger   magic;
    RenderPass  renderPass;
    miInteger   shadowLimit;
    miBoolean   computeFilterSize;
    miScalar    defaultFilterSize;
    miBoolean   aggressiveCaching;
    miBoolean   disableShaderGlow;
    miScalar    asqMinThreshold;
    miScalar    asqMaxThreshold;
    miInteger   refractionBlurLimit;
    miInteger   reflectionBlurLimit;
};

typedef enum {
    DEPTHTYPE_CLOSEST = 0,
    DEPTHTYPE_FURTHEST
} DepthType;

struct CameraData {
    miInteger   magic;
    miScalar    xPixelAngle;
    miScalar    horizontalFilmAperture;
    miScalar    verticalFilmAperture;
    miScalar    horizontalFilmOffset;
    miScalar    verticalFilmOffset;
    miScalar    lensSqueezeRatio;
    miScalar    orthographicWidth;
    /* Volume Sampler Parameters. */
    miInteger   volumeSamples;
    miBoolean   depthJitter;
    /* Z Channel Parameters. */
    miBoolean   depth;
    miBoolean   transparencyBasedDepth;
    miScalar    threshold;
    DepthType   depthType;
    /* Shutter Times. */
    miScalar    shutterOpen;
    miScalar    shutterClose;
    /* Background Color. */
    miColor     backgroundColor;
};

//! \endcond

/*!
  \brief Data structure used in the per-Camera frame buffer
  information user data block, which contains an array of these
  structures.
*/
struct FrameBufferInfoData
{
    miTag     frameBufferName; //!< The name of the frame buffer.
    miBoolean useTransparency; //!< When false, all objects are rendered as opaque.
    miBoolean holdout; //!< When true, hidden objects produce occlusions in the scene.
    miBoolean reflectHidden; //!< When true, hidden geometries are visible through reflections.
    miBoolean refractHidden; //!< When true, hidden geometries are visible through refractions.
    miBoolean hiddenReflect; //!< When true, hidden objects produce reflections.
    miBoolean hiddenRefract; //!< When true, hidden objects produce refractions.
    miBoolean transparentAttenuation; //!< When true, frame buffer contributions are modulated by the transparency.
    miBoolean computeShadows; //!< When true, shadows are computed.
    miBoolean hiddenShadows; //!< When true, hidden geometries cast shadows.
    miInteger minReflectionLevel; //!< Minimum reflection level.
    miInteger maxReflectionLevel; //!< Maximum reflection level.
    miInteger minRefractionLevel; //!< Minimum refraction level.
    miInteger maxRefractionLevel; //!< Maximum refraction level.
    miInteger integerUserParameter1; //!< General purpose user-defined parameter.
};

struct FrameBufferData {
    miInteger           magic;

    miInteger           i_nonMaterialPassFrameBufferNames;
    miInteger           n_nonMaterialPassFrameBufferNames;
    miTag               nonMaterialPassFrameBufferNames[1];

    miInteger           i_frameBufferInfo;
    miInteger           n_frameBufferInfo;
    FrameBufferInfoData frameBufferInfo[1];

    miInteger           i_frameBufferTypeCounts;
    miInteger           n_frameBufferTypeCounts;
    miInteger           frameBufferTypeCounts[1];
};

//! \cond DOCUMENT_MAYA_STATE

struct ObjectData {
    miInteger   magic;
    miInteger   uvSpace;
    /* Volume Sampler Parameters. */
    miInteger   renderableObjectType;
    miInteger   volumeSamples;
    miBoolean   depthJitter;
    /* FG and GI Overrides. */
    miBoolean   overrideFgGi;
    miInteger   finalgatherRays;
    miScalar    finalgatherMaxRadius;
    miScalar    finalgatherMinRadius;
    miBoolean   finalgatherView;
    miInteger   finalgatherFilter;
    miInteger   globillumAccuracy;
    miScalar    globillumRadius;
    miInteger   causticAccuracy;
    miScalar    causticRadius;
    miInteger   finalgatherPoints;
    miScalar    finalgatherImportance;
};

struct AreaLightData {
    miVector    vertices[4];
    miVector    direction;
};

ADSK_SHADERSDK_EXPORT const LightDataArray defaultLightDataArray;

#define MAYA_ISNULLMATRIX(m)                            \
    (!memcmp((m), MAYA_NULL_MATRIX, sizeof(miMatrix)))
#define MAYA_ISIDENTITYMATRIX(m)                            \
    (!memcmp((m), MAYA_IDENTITY_MATRIX, sizeof(miMatrix)))

// State macros.

// Key for mi_shaderstate_set() and _get().
#define MBS_KEY "mayabase"

// Initialize mayabase state.
#define MBS_SETUP(state)                        \
    MayabaseState *MBS =                        \
        (MayabaseState*)                        \
        mi_shaderstate_get(state, MBS_KEY, 0);

// Initialization successful?
#define MBS_ERROR (!MBS)

//! \hideinitializer \ingroup Macros
//! \brief Assert if there is no MBS.
/*!
  \param[in] shader Name of the shader
*/
#define MBS_ASSERT(shader)                      \
    if (MBS_ERROR) {                            \
        adskWarning(                            \
            shader "(): "                       \
            "Internal state error.");           \
        return miFALSE;                         \
    }

#define MAYA_CONNECTED(p)                                   \
    (state->shader->ghost_offs &&                           \
     *((miTag *)((char *)(p) + state->shader->ghost_offs)))

void *get_userdata(
    miInteger   magic,
    int     type,
    miTag       item,
    miTag       *outData,
    miBoolean   *hasBadEndian);

/*!
  \brief Retrieve a user data block

  \param[in] pItem The tag of the user data block
  \param[in] pMagicId Optional, the magic number that identifies the data block

  \return MIDataPtr to the data block
*/
template<typename DataStruct>
inline MIDataPtr<DataStruct> getMayaUserData(const miTag& pItem, const miInteger pMagicId = MAYA_MAGIC)
{
    miTag outItem;
    miBoolean outEndian;
    DataStruct* data = (DataStruct*)get_userdata(pMagicId, miSCENE_USERDATA, pItem, &outItem, &outEndian);
    MIDataPtr<DataStruct> result(data, outItem, outEndian ? true : false);
    return result;
}

/*!
  \brief Retrieve an object data block

  \param[in] pItem The tag of the object data block
  \param[in] pMagicId Optional, the magic number that identifies the data block

  \return MIDataPtr to the data block
*/
template<typename DataStruct>
inline MIDataPtr<DataStruct> getMayaObjectData(const miTag& pItem, const miInteger pMagicId = MAYA_MAGIC)
{
    miTag outItem;
    DataStruct* data = (DataStruct*)get_userdata(pMagicId, miSCENE_OBJECT, pItem, &outItem, 0);
    MIDataPtr<DataStruct> result(data, outItem);
    return result;
}

/* User data macro shortcuts.
 */

#define MAYA_USERDATA(i,d,e)                                    \
    get_userdata(MAYA_MAGIC, miSCENE_USERDATA, (i), (d), (e))

#define MAYA_OBJECTDATA(i,d)                                            \
    (ObjectData *) get_userdata(MAYA_MAGIC, miSCENE_OBJECT, (i), (d), 0)

/* Macro for retrieving 3D texture coordinates coordPointer.
 * This macro actually belongs to Texture3d but it's used by Bump3d, Projection
 * and in all other places where reference coordinates are required. mi_query()
 * can get quite expensive here.
 */
inline void TEX3D_GET_COORD_PTR(miVector* &coordPointer, miState* state, MayabaseState * &MBS){
    if (!MBS_ERROR &&
        (MBS->infoBits &
         (MAYA_BIT_VOLUMEFOG |
          MAYA_BIT_ENVLIGHTFOG |
          MAYA_BIT_FLUID)))
    {
        coordPointer = &state->org;
    } else {
        miTag usrTag;
        ObjectData *usrPtr;
        if (state->instance &&
            (usrPtr = MAYA_OBJECTDATA(state->instance, &usrTag))) {
            if (usrPtr->uvSpace >= 0) {
                coordPointer = &state->tex_list[usrPtr->uvSpace];
                mi_point_from_world(state, coordPointer, coordPointer);
            } else {
                coordPointer = &state->point;
            }
            mi_db_unpin(usrTag);
        } else {
            coordPointer = &state->point;
        }
    }
}

/* Macro for retrieving per-object overrides <o> for final gather and photon
 * settings. These settings are read from a user data block of type ObjectData
 * and stored to miIrrad_options which is passed to mi_compute_avg_radiance().
 */
inline void IRRAD_GET_OPTNS(miIrrad_options &pOptions, miState *pState){
    ObjectData *usrPtr = 0;
    miTag usrTag;
    pOptions.size = 0;
    if ((usrTag = pState->instance) &&
        (usrPtr = MAYA_OBJECTDATA(usrTag, &usrTag)) &&
        (usrPtr->overrideFgGi == miTRUE)) {
        pOptions.size = sizeof(miIrrad_options);
        pOptions.finalgather_rays = usrPtr->finalgatherRays;
        pOptions.finalgather_maxradius = usrPtr->finalgatherMaxRadius;
        pOptions.finalgather_minradius = usrPtr->finalgatherMinRadius;
        pOptions.finalgather_view = (miCBoolean) usrPtr->finalgatherView;
        pOptions.finalgather_filter = (miUchar) usrPtr->finalgatherFilter;
        pOptions.finalgather_points = (miUint) usrPtr->finalgatherPoints;
        pOptions.importance = usrPtr->finalgatherImportance;
        pOptions.globillum_accuracy = usrPtr->globillumAccuracy;
        pOptions.globillum_radius = usrPtr->globillumRadius;
        pOptions.caustic_accuracy = usrPtr->causticAccuracy;
        pOptions.caustic_radius = usrPtr->causticRadius;
        pOptions.padding1[0] = pOptions.padding1[1] = 0;
    }
    if (usrPtr)
        mi_db_unpin(usrTag);
}

/* Macro for calculating a scalar value from the asqWeight in MayabaseState. It
 * currently returns the maximum norm of asqWeight.{r,g,b}, but may be adjusted
 * to use a different norm if needed. Later...
 */
#define MAYA_ASQ_SCALAR                         \
    (MBS->asqWeight.r > MBS->asqWeight.g ?      \
     (MBS->asqWeight.r > MBS->asqWeight.b ?     \
      MBS->asqWeight.r : MBS->asqWeight.b) :    \
     (MBS->asqWeight.g > MBS->asqWeight.b ?     \
      MBS->asqWeight.g : MBS->asqWeight.b))


/* Matte opacity modes.
 */
enum MatteOpacityMode {
    MATTEMODE_BLACKHOLE = 0,
    MATTEMODE_SOLIDMATTE,
    MATTEMODE_OPACITYGAIN
};

/* BRDF components.
 */
struct BRDFComponent {
    miInteger     renderPass;
    miBoolean     directIllumination;
    miBoolean     directIlluminationShadows;
    unsigned int  components;
};

// Result structure for surface shaders.
#define ADSK_SURFACE_SHADER_STANDARD_RESULT     \
    miColor     color;                          \
    miColor     glowColor;                      \
    miColor     matteOpacity;                   \
    miColor     transparency;
#define ADSK_SURFACE_SHADER_BRDF_RESULT         \
    miColor     ambient;                        \
    miColor     incandescence;                  \
    miColor     irradiance;                     \
    miColor     diffuseShadowed;                \
    miColor     diffuseNoShadow;                \
    miColor     shadow;                         \
    miColor     specularShadowed;               \
    miColor     specularNoShadow;               \
    miColor     reflection;                     \
    miColor     refraction;                     \
    miColor     scatter;                        \
    miColor     opacity;

struct SurfaceShaderReturnType {
    ADSK_SURFACE_SHADER_STANDARD_RESULT
    ADSK_SURFACE_SHADER_BRDF_RESULT
};

#define BC_BIT_AMBIENT          (1u <<  0)
#define BC_BIT_INCANDESCENCE    (1u <<  1)
#define BC_BIT_IRRADIANCE       (1u <<  2)
#define BC_BIT_LIGHT_DIFF       (1u <<  3)
#define BC_BIT_LIGHT_DIFF_NOSH  (1u <<  4)
#define BC_BIT_LIGHT_SHADOW     (1u <<  5)
#define BC_BIT_LIGHT_SPEC       (1u <<  6)
#define BC_BIT_LIGHT_SPEC_NOSH  (1u <<  7)
#define BC_BIT_REFLECTION       (1u <<  8)
#define BC_BIT_REFRACTION       (1u <<  9)
#define BC_BIT_SCATTER          (1u << 10)

#define BC_HAS_AMBIENT          (bc.components & BC_BIT_AMBIENT)
#define BC_HAS_INCANDESCENCE    (bc.components & BC_BIT_INCANDESCENCE)
#define BC_HAS_IRRADIANCE       (bc.components & BC_BIT_IRRADIANCE)
#define BC_HAS_LIGHT_DIFF       (bc.components & BC_BIT_LIGHT_DIFF)
#define BC_HAS_LIGHT_DIFF_NOSH  (bc.components & BC_BIT_LIGHT_DIFF_NOSH)
#define BC_HAS_LIGHT_SHADOW     (bc.components & BC_BIT_LIGHT_SHADOW)
#define BC_HAS_LIGHT_SPEC       (bc.components & BC_BIT_LIGHT_SPEC)
#define BC_HAS_LIGHT_SPEC_NOSH  (bc.components & BC_BIT_LIGHT_SPEC_NOSH)
#define BC_HAS_REFLECTION       (bc.components & BC_BIT_REFLECTION)
#define BC_HAS_REFRACTION       (bc.components & BC_BIT_REFRACTION)
#define BC_HAS_SCATTER          (bc.components & BC_BIT_SCATTER)

#define BC_HAS_DIRECTILLUM      (bc.directIllumination)
#define BC_HAS_DIRECTILLUM_SH   (bc.directIlluminationShadows)

ADSK_SHADERSDK_EXPORT void bc_construct(
    BRDFComponent    *bc,
    const miInteger  renderPass,
    miState          *state);

ADSK_SHADERSDK_EXPORT void bc_composite(
    BRDFComponent            bc,
    SurfaceShaderReturnType  *result,
    const miColor            *ambient,
    const miColor            *incandescence,
    const miColor            *irradiance,
    const miColor            diffuse[2],
    const float              shadow,
    const miColor            specular[2],
    const miColor            *reflection,
    const miColor            *refraction,
    const miColor            *scatter,
    const miColor            *transparency,
    const miScalar           glowIntensity,
    const miScalar           specularGlow,
    const miBoolean          hideSource,
    const miInteger          matteOpacityMode,
    const miScalar           matteOpacity);

ADSK_SHADERSDK_EXPORT void bc_destruct(
    BRDFComponent    *bc);

/* fast version of mi_point_from_camera
 */
ADSK_SHADERSDK_EXPORT void origin_from_camera(
    const miState    *state,
    miVector         *origin);

/* Thread local arena code and Stack implementation
 */
ADSK_SHADERSDK_EXPORT miMemblk *get_tla(
    miLock       lock,
    miThreadID   threadId,
    unsigned int blkSize);

ADSK_SHADERSDK_EXPORT void clr_tla_list(
    miLock lock);

ADSK_SHADERSDK_EXPORT void stack_create(
    miState      *state,
    Stack        *stack,
    unsigned int sizeOfItem);

ADSK_SHADERSDK_EXPORT void *stack_push(
    Stack *stack);

ADSK_SHADERSDK_EXPORT void stack_pop(
    Stack *stack);

typedef struct TmSampler
{
    unsigned int    curSample;
    unsigned int    numSamples;
    float       sampleStep;
} TmSampler;

ADSK_SHADERSDK_EXPORT void tmsampler_init(
    TmSampler   *sampler,
    miState     *state,
    miBoolean   oversample);

ADSK_SHADERSDK_EXPORT miBoolean tmsampler_isDone(
    const TmSampler *sampler);

ADSK_SHADERSDK_EXPORT void tmsampler_next(
    TmSampler   *sampler,
    miState     *state);

//! \endcond
    
// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus

#endif  // ADSK_MAYASTATE_H
