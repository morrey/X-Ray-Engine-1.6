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
  \brief Base class for non-material render passes
*/

#ifndef ADSK_PASS_SHADER_H
#define ADSK_PASS_SHADER_H

#if defined __cplusplus

#ifndef ADSK_SHADER_H
#include <adskShader.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

#define PASS_SHADER_BASE_PARAMETERS             \
    miInteger   frameBufferNumber;              \
    miInteger   encodingIndex;

/*!
  \brief Data structure used for storing the baseline parameters for
  pass shaders.
*/
struct PassShaderBaseParameters {
    PASS_SHADER_BASE_PARAMETERS
};

/*!
  \brief Pass shader base class

  \tparam PassShaderParameters The type of the pass shader parameters.

  \tparam PassComputation The helper function object which computes a
  value per sample. This function object will be constucted using
  using the current state, and the current parameters, and will be
  called with the state, parameters, and a reference to the current
  value in the frame buffer for the given sample.

  \tparam RayFilter The helper function object which determines
  whether a ray should be processed or not. See \c
  PassShaderEyeRayFilter for an example implementation.

  \tparam VERSION The version number of this shader.
*/
template<typename FrameBufferDataType,
    typename PassShaderParameters,
    typename PassComputation,
    typename RayFilter,
    int VERSION = 1>
    class PassShader : public Shader<PassShaderParameters, ShaderHelper<PassShaderParameters>, VERSION> {
  public:
  /*!
    \brief PassShader constructor. This will be called
    once per shader instance, and is where data for each shader
    instance should be initialized.

    \param pState A pointer to the mental ray state structure.

    \param pParameters A pointer to the shader parameters.
  */
  PassShader(miState *pState, PassShaderParameters *pParameters);

  /*!
    \brief PassShader destructor. The member variables \c
    mDestructorState and \c mDestructorParameters will be set
    correctly when the destructor is called.
  */
  virtual ~PassShader();

  /*!
    \brief Main shading function.
           
    This is the function which is called for shader samples.

    \param pResult A pointer to the mental ray color result.

    \param pState A pointer to the mental ray state
    structure.

    \param pParameters A pointer to the shader parameters.
  */
  miBoolean operator()(miColor *pResult, miState *pState, PassShaderParameters *pParameters);

  /*!
    The frame buffer IDs
  */
  miUint mFrameBufferID;
  /*!
    Index associated with the render pass. Used for lookups in the pass
    contribution encoding strings.
  */
  miUint mEncodingIndex;

  /*!
    Object used for performaing pass-specific computations
  */
  PassComputation   mPassComputation;
};


// PassShader method implementations

template <typename FrameBufferDataType,
    typename PassShaderParameters,
    typename PassComputation,
    typename RayFilter,
    int VERSION>
    PassShader<FrameBufferDataType,
    PassShaderParameters,
    PassComputation,
    RayFilter,
    VERSION>::PassShader(miState *state, PassShaderParameters *pParameters) : 
    Shader<PassShaderParameters, ShaderHelper<PassShaderParameters>, VERSION>(state, pParameters),
    mPassComputation(state, pParameters)
{
    // Set up the frame buffer ID
    mFrameBufferID = getNonMaterialPassFrameBufferIndex(state, *mi_eval_integer(&pParameters->frameBufferNumber));
    mEncodingIndex = *mi_eval_integer(&pParameters->encodingIndex);
}

template <typename FrameBufferDataType,
    typename PassShaderParameters,
    typename PassComputation,
    typename RayFilter,
    int VERSION>
    PassShader<FrameBufferDataType,
    PassShaderParameters,
    PassComputation,
    RayFilter,
    VERSION>::~PassShader() {
}

template <typename FrameBufferDataType,
    typename PassShaderParameters,
    typename PassComputation,
    typename RayFilter,
    int VERSION>
    miBoolean PassShader<FrameBufferDataType,
    PassShaderParameters,
    PassComputation,
    RayFilter,
    VERSION>::operator()(miColor *pResult,
                         miState *state,
                         PassShaderParameters *pParameters)
{
    RayFilter lRayFilter(state, pParameters);

    if (lRayFilter())
    {
        miColor curDataBuffer;  // make sure we have a type wide
                                // enough for all possibilities to
                                // avoid stack corruption
        mi_fb_get(state, mFrameBufferID, &curDataBuffer);
        FrameBufferDataType &curData = *((FrameBufferDataType*)&curDataBuffer);
        
        // Get the auxiliary pass contribution map for the geometry
        // at the ray intersection
        const adskInstanceParameters *lObjectInstParams = 0;
        if (state->instance)
        {
            MIDataPtr<miInstance> leafInstance(state->instance);
            if (leafInstance && leafInstance->parent) 
            {
                mi_query(
                    miQ_INST_PARAM,
                    state,
                    leafInstance->parent,
                    &lObjectInstParams
                    );
            }
        }

        if (lObjectInstParams && lObjectInstParams->passEncoding)
        {
            MIDataPtr<const char> lObjectEncoding(lObjectInstParams->passEncoding);
            if (lObjectEncoding && lObjectEncoding[0] == 0){
                lObjectEncoding = 0;
            }
            if ( !lObjectEncoding || contributesToPass(mEncodingIndex, lObjectEncoding.get()) )
            {
                mPassComputation(state, pParameters, curData);
                mi_fb_put(state, mFrameBufferID, &curData);
            }
        }
        else{
            if (contributesToPass(mEncodingIndex, 0)){
                mPassComputation(state, pParameters, curData);
                mi_fb_put(state, mFrameBufferID, &curData);
            }
        }
    }

    return miTRUE;
}

//----------------------------------------------------------------------------
// Basic Filter classes

/*!
  \brief Filter class for pass shaders that only evaluate on eye rays in
  the tile rendering stage

  \tparam PassShaderParameters The shader parameter data structure.
*/
template<typename PassShaderParameters>
class PassShaderEyeRayFilter
{
  public:
    /*!
      \brief Filter constructor
      
      \param pState The mental ray state.
      
      \param pParameters The shader parameters.
    */
    PassShaderEyeRayFilter(miState* pState, PassShaderParameters* pParameters) {
        // are we in the tile render stage?
        bool inTileRenderingStage = false;
        miInteger stage;
        mi_query(miQ_STAGE, pState, miNULLTAG, &stage);
        if (stage == miSTAGE_TILE){
            inTileRenderingStage = true;
        }
        mFilterResult = (pState->type == miRAY_EYE && inTileRenderingStage);
    };
    /*!
      \brief Called for each sample.

      \return Whether we should process this sample or not.
    */
    inline bool operator()() { return mFilterResult; }
  private:
    bool mFilterResult; //!< Whether we should process the sample or not.
};

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus
#endif // ADSK_PASS_SHADER_H
