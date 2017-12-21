/******************************************************************************
 * Copyright 1986-2008 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin
 * All rights reserved.
 ******************************************************************************
 * Author:	daniel	
 * Created:	25.04.2008
 * Purpose:	BSDF interface for mental ray
 *
 * Note: This file is generated automatically from the mental ray sources, do
 * not edit. Some definitions exist for internal reasons and are subject to
 * change between mental ray versions. See the mental ray user's manual for
 * a definitive description of the shader interface. Avoid using features not
 * documented in the manual because they may change in future versions.
 *****************************************************************************/

#ifndef SHADER_BSDF_H
#define SHADER_BSDF_H


/*------------ brdf.h ------------*/


namespace mi {
namespace shader_v3 {


/// Simplified BSDF interface.
///
/// The \c Bsdf interface represents the concept of a Bidirectional Scattering
/// Distribution Function. The BSDF describes the scattering characteristics
/// of a point, i.e. reflection (the BRDF), and transmission (the BTDF). 
///
/// This interface allows shaders to interact with BSDFs. It is intended to
/// serve the same purpose as the RC Direction Functions and Shading Models 
/// functions (see the manual), but in a generalized way. 
/// 
/// For example, a shader might use a \c Bsdf in the following way:
/// \code
/// Access_bsdf bsdf(state);
/// 
/// // do light loop
/// for (...) {
///     direct += light * bsdf->eval(view_dir,light_dir);
/// }
/// \endcode
///
/// If diffuse and specular contributions are needed separately, the BSDF
/// evaluation can be restricted by passing e.g. \c Bsdf::Reflect_diffuse
/// or \c Bsdf::All_glossy as the third parameter of the \c eval function.
/// Note, however, that multiple separate evaluations of components are 
/// more expensive than a single evaluation of all components. 
/// 
/// Note that specular components cannot be evaluated, they have to be 
/// sampled. Thus, reflections of light sources in perfect mirrors can be
/// achieved by code similar to
/// \code
/// double xi[3];
/// mi_sample(xi,0,state,3,0);
/// if (bsdf->sample(view_dir,&refl_dir,&mirror,xi,Bsdf::Reflect_specular) 
///     && mi_trace_reflection(&hit,state,&refl_dir)
///	&& !state->child->pri) {	// light source hit
///     light_hit = mirror * hit;
/// }
/// \endcode
///
class Bsdf
{
public:
    /// no virtual dtor
    
    /// sampling/evaluation direction
    typedef bool Transport;
    static const Transport From_eye	= false;  ///< rendering from the camera
    static const Transport From_light 	= true;	  ///< from the light, e.g. photons

    
    /// scatter type.
    ///
    /// Type flags are bit patterns. Typical binary operations are valid e.g.
    /// for component combinations or sample result inspection.
    enum {
	// single types
	Invalid		  = 0x00, ///< unknown or absorption
	Reflect_diffuse	  = 0x01, ///< diffuse reflection
	Reflect_glossy	  = 0x02, ///< glossy reflection
	Reflect_specular  = 0x04, ///< specular reflection
	Transmit_diffuse  = 0x10, ///< diffuse transmission
	Transmit_glossy	  = 0x20, ///< glossy transmission
	Transmit_specular = 0x40, ///< specular transmission
	
	// compound types
	Reflect_regular		  ///< non-specular reflection
	= Reflect_diffuse
	| Reflect_glossy,
	Transmit_regular	  ///< non-specular transmission
	= Transmit_diffuse
	| Transmit_glossy,
	All_diffuse		  ///< diffuse reflection and transmission
	= Reflect_diffuse 
	| Transmit_diffuse,
	All_glossy		  ///< glossy reflection and transmission
	= Reflect_glossy 
	| Transmit_glossy,
	All_specular		  ///< specular reflection and transmission
	= Reflect_specular 
	| Transmit_specular,
	All_regular		  ///< non-specular reflection and transmission
	= Reflect_regular 
	| Transmit_regular,
	All_reflect		  ///< diffuse, glossy, and specular reflection
	= Reflect_regular 
	| Reflect_specular,
	All_transmit		  ///< diffuse, glossy, and specular transmission
	= Transmit_regular 
	| Transmit_specular,
	All			  ///< all types
	= All_reflect 
	| All_transmit
    };
    typedef miUint4 Type;

    
    /// Evaluates the BSDF at the current point.
    ///
    /// When tracing rays from the eye towards the scene (the usual case),
    /// \p dir is \c From_eye, \p ray is the view direction and \p out is the
    /// light direction.
    /// All directions are in world space. The \p ray direction points towards
    /// the intersection, the \p out direction points away from it.
    ///
    /// Because specular components cannot be evaluated (they can only be
    /// sampled), this function only evaluates the diffuse and glossy parts.
    /// The contribution from specular components is black. Shaders must use
    /// \c sample to obtain a specular direction and contribution.
    ///
    /// \param[in]  ray		given direction
    /// \param[in]  out		sampled direction
    /// \param[in]  flags	allowed types
    /// \param[in]  dir		trace direction
    /// \return the value of the BSDF at the current point and for the given 
    /// pair of directions 
    virtual miColor eval(
	    const miVector&	ray,
	    const miVector&	out,
	    Type		flags = All,
	    Transport		dir = From_eye
	    ) const = 0;
    

    /// Importance samples an outgoing direction using the quasirandom numbers
    /// supplied in \p xi and stores it in \p out.
    ///
    /// All directions are in world space. The \p ray direction points towards
    /// the intersection, the \p out direction points away from it.
    ///
    /// The importance sampling weight (i.e. the BSDF value for the sampled 
    /// direction divided by the probability of sampling the direction) will
    /// be written to \p weight. 
    /// Note that the \p weight result contains the probability density in
    /// projected solid angle measure. One implication of this is that the 
    /// weight does not have to be multiplied by
    /// \htmlonly
    /// <span class="math">cos &theta;</span>, where &theta; is the angle
    /// between surface normal and light, when tracing secondary rays.
    /// \endhtmlonly
    /// \latexonly
    /// \f$ \cos\theta \f$, where \f$\theta\f$ is the angle between surface
    /// normal and light, when tracing secondary rays.
    /// \endlatexonly
    /// This function returns the type of the component that was sampled.
    /// Note that, while this function may return \c Bsdf::Invalid in some
    /// cases, it does \em not perform Russian roulette for absorption. 
    /// If Russian roulette is needed, then
    /// \htmlonly
    /// <span class="math">min{1, |<tt>weight</tt>|}</span>
    /// \endhtmlonly
    /// \latexonly
    /// \f$ \min\{1,\|\mathtt{weight}\|\} \f$
    /// \endlatexonly
    /// is a good candidate for the continuation probability. Usually, the
    /// maximum norm yields the best results.
    ///
    /// Suitable values for \p xi can be acquired e.g. by calling \c mi_sample.
    ///
    /// \param[in]  ray		known direction
    /// \param[out] out		sampled direction
    /// \param[out] weight	sample weight
    /// \param[in]  xi		sample in [0,1)^3
    /// \param[in]  flags	allowed types
    /// \param[in]  dir		trace direction
    /// \return the sampled component type
    virtual Type sample(
	    const miVector&	ray,
	    miVector*		out,
	    miColor*		weight,
	    double		xi[3],
	    Type		flags = All,
	    Transport		dir = From_eye
	    ) const = 0;
    
    
    /// Checks if the BSDF supports all of the given components.
    ///
    /// If \p type is a compound type, e.g \c All_xxx, this function
    /// checks if all of the given components are supported. For single
    /// types, this function's result is identical to that of 
    /// \c Bsdf::any_component.
    ///
    /// \param type the scatter type to check
    /// \return \c true if all of the given components are supported by
    /// the BSDF, \c false otherwise.
    virtual bool all_components(Type type) const = 0;
    
    
    /// Checks if the BSDF supports the given component.
    ///
    /// If \p type is a compound type, e.g \c All_xxx, this function
    /// checks if one or more of the given components are supported. For 
    /// single types, this function's result is identical to that of 
    /// \c Bsdf::all_components.
    ///
    /// \param type the scatter type to check
    /// \return \c true if any of the given components are supported by
    /// the BSDF, \c false otherwise.
    virtual bool any_component(Type type) const = 0;
};



/// A read-only \c Bsdf handle.
///
/// Note that this must be used thread-locally
class Access_bsdf
{
public:
    
    /// Accesses a \c Bsdf.
    ///
    /// The created access will attempt to acquire a \c Bsdf instance from
    /// a pool by executing the shader that is attached to the \c bsdf slot
    /// in the current material. The access is valid if the \c bsdf slot is
    /// populated with a valid BSDF wrapper shader.
    ///
    /// \param state the current state
    Access_bsdf(miState* state)
    : m_state(state)
    {
	m_bsdf = Interface_access()->allocBsdf(state);
    }

    
    /// Destroys the access. 
    ///
    /// All acquired resources are released.
    ~Access_bsdf()
    {
	Interface_access()->releaseBsdf(m_bsdf,m_state);
    }
    
    
    /// Allows the access to be used like a pointer.
    const Bsdf* operator->() const { return m_bsdf; }
    
    
    /// Checks if the access is valid.
    ///
    /// \return \c true if a \c Bsdf instance was found on construction,
    /// \c false otherwise.
    bool valid() const { return 0 != m_bsdf; }
    
private:
    Access_bsdf(const Access_bsdf&);
    Access_bsdf& operator=(const Access_bsdf&);
    
    miState* 	m_state;
    Bsdf* 	m_bsdf;
};

}}


#endif
