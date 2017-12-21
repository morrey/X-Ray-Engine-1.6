///////////////////////////////////////////////////////////////////////////////
// Copyright 1986-2008 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Author:	juergen
// Created:	27.02.08
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file shader_lightlist.h
/// mental ray C++ shader interface extensions.
///
/// This file provides interfaces that simplify use of light lists.
///
/// shader_lightlist.h is included by mi_shader_if.h, which in turn is 
/// included from shader.h if the shader is compiled as C++ code.
/// A shader does not need to include this file directly.


#ifndef SHADER_LIGHTLIST_H
#define SHADER_LIGHTLIST_H

#include "mi_shader_if.h"

namespace mi {
namespace shader_v3 {


/// \brief Iterate over shader or instance light lists.
/// 
/// mental ray 3.5 introduced the concept of instance light lists.
/// These lists are not explicitely passed to the shader as a parameter.
/// Instead mental ray makes them available through LightIterators.
/// The LightIterator class allows shaders to iterate over lights for
/// the purpose of sampling. A typical use would look like
/// \code
/// for (mi::shader::LightIterator iter(state); !iter.at_end(); ++iter) {
///     miColor col = {0,0,0,1};
///     while (iter->sample()) {
///         miColor light_color;
///         iter->get_contribution(&light_color);
///         col.r += light_color.r;
///         col.g += light_color.g;
///         col.b += light_color.b;
///     }
///     const int n_samples = iter->get_number_of_samples();
///     if (n_samples > 1) {
///         col.r /= n_samples;
///         col.g /= n_samples;
///         col.b /= n_samples;
///     }
/// }
/// \endcode
///
class LightIterator {
public:
    /// \brief the contructor for the LightIterator
    ///
    /// Construct a LightIterator from state and an optional shader light list.
    /// Note that two different light lists may be assigned to instances: a light 
    /// list and a shadow light list. During regular rendering the iterator uses 
    /// the light list, but when either rendering shadow maps or tracing shadow rays, 
    /// then the iterator prefers the shadow light list over the light list, that 
    /// is, in these cases the light list will only be used if no shadow light list 
    /// is present. It is also possible to instanciate the iterator with an explicit 
    /// light list provided by the shader.
    ///
    /// \param state
    ///	        provides the iterator with information about the rendering state, 
    ///	        especially where to find the lights for the iteration.
    /// \param shader_light_list
    ///         allows to provide a custom list of lights for the iteration.
    ///         This optional list overrides the instance light lists used by
    ///         default.
    /// \param n_shader_lights
    ///         tells the iterator the number of custom lights passed in.
    /// \param version
    ///        allows to specify a specific interface version. By default this
    ///        is set to the current interface version.
    LightIterator(
	miState* 	state,
	miTag*	 	shader_light_list = 0,
	int	 	n_shader_lights = 0,
        int      	version = mi_ray_interface_version);

    /// \brief the contructor for the LightIterator with sampling cone.
    ///
    /// The cone for light samples is defined by axis and the cosine of the angle.
    ///
    /// \param state
    ///         provides the iterator with information about the rendering state, 
    ///         especially where to find the lights for the iteration.
    /// \param axis
    ///        specifies the axis for the light cone. The value should be normalized.
    /// \param spread_cos
    ///        specifies the cosine of the angle to the light cone axis.
    ///        The value 0 corresponds to a hemisphere, the value -1 to the complete sphere.
    /// \param shader_light_list
    ///        allows to provide a custom list of lights for the iteration.
    ///        This optional list overrides the instance light lists used by default.
    /// \param n_shader_lights
    ///        tells the iterator the number of custom lights passed in.
    /// \param version
    ///        allows to specify a specific interface version. By default this
    ///        is set to the current interface version.
    LightIterator(
	miState* 	state,
	const miVector	&axis,
	miScalar	spread_cos,
	miTag*	 	shader_light_list = 0,
	int	 	n_shader_lights = 0,
        int      	version = mi_ray_interface_version);


    /// \brief the copy constructor.
    ///
    /// creates a copy of a given LightIterator. This constructor is needed
    /// to return LightIterators from methods.
    ///
    /// \param iter the LightIterator to be copied.
    LightIterator(const LightIterator &iter);

    /// \brief the destructor
    ///
    /// The destructor for a LightIterator instance is called when it goes out of scope.
    /// It releases all resources associated with this instance.
    ~LightIterator();

    /// \brief obtain the tag for the current light
    ///
    /// dereferencing a LightIterator with the unary prefix operator '*' yields 
    /// the tag of the current light. Note that this operation is distinctly 
    /// different from dereferencing a LightIterator with the postfix operator '->'.
    ///
    /// \return the tag of the current light in the light list.
    miTag operator*() const;

    /// \brief access to light list from iterator
    ///
    /// the postfix dereference operator allows to invoke public methods of
    /// the LightList class from the LightIterator.
    ///
    /// \return a pointer to the LightList associated with the LightIterator. Note
    ///         that the LightList pointer is not available for direct use. Instead C++
    ///         will immediately use it to invoke the LightList method written to the right
    ///         of the '->' operator. For example,
    /// \code
    /// LightIterator iter(state)->sample();
    /// \endcode
    /// will invoke the sample method of the LightList class.
    LightList* operator->() const;

    /// \brief pre-increment operator
    ///
    /// The operator advances the LightIterator to the next light in the light list.
    /// The pre-increment operator should be prefered over the post-increment
    /// operator, since it avoids the generation of a temporary LightIterator.
    ///
    /// \return a constant reference of the iterator
    const LightIterator& operator++();

    /// \brief post-increment operator
    ///
    /// The increment operator advances the LightIterator to the next light
    /// in the light list. The post-increment operator is more expensive than
    /// the pre-increment operator, since it need to construct an extra
    /// copy of the iterator.
    ///
    /// \return a copy of the LightIterator before it was advanced
    ///         to the next light.
    LightIterator operator++(int);

    /// \brief check if iteration should continue.
    ///
    /// \return true if the end of the light list has been reached,
    ///         false otherwise.
    bool at_end() const;

    /// \brief assign LightIterator
    ///
    /// Assign a LightIterator to this LightIterator.
    /// If the two iterators refer to different light lists, make
    /// sure that proper reference counting is performed on the two lists.
    ///
    /// \param iter
    ///     gives the LightIterator to be assigned
    /// \return a constant reference to the LightIterator that has been assigned to.
    const LightIterator &operator=(const LightIterator &iter);

    /// \brief check if two LightIterators are equal
    ///
    /// Two LightIterators are considered equal if they refer to the same
    /// light list and have the same current light within the list.
    ///
    /// \return true if the two iterators are equal, false else.
    bool operator==(const LightIterator &iter) const;

    /// \brief check if two LightIterators are unequal.
    ///
    /// Two LightIterators are unequal if they do not refer to the same
    /// LightList or have two different current lights within the list.
    ///
    /// \return true if the two iterators are unequal, false else.
    bool operator!=(const LightIterator &iter) const;

private:
    /// \brief the list of lights to be iterated
    ///
    /// The iteration light list is only referenced here to keep the iterator small.
    LightList* m_list;

    /// \brief the current light
    ///
    /// Keep the index of the current light within the iteration LightList.
    size_t m_current;
};


/// \brief Light lists, used internally by LightIterator.
///
/// The LightList class manages the iteration over light sources. The class
/// is only used internally by the LightIterator class. The class is
/// reference counted to allow several iterators to refer to the same
/// light list. However, the class maintains only one cache for the results
/// of light sampling. Therefore, if there are several LightIterators
/// referencing the same light list, then most of the class "get" methods will
/// return results obtained from the most recent call of the sample method.
class LightList {
public:

    /// \brief sets the current light in the light list
    ///
    /// The method is used by light iterators to set the light list to the 
    /// wanted light. It is used when dereferencing a light iterator to 
    /// specify which light should be sampled.
    ///
    /// \param current
    ///         identifies the light to be made the current one.
    /// \return the current light index
    virtual size_t set_current(size_t current)		= 0;

    /// \brief get the index of the current light
    ///
    /// The method is used by light iterators to obtain the current light index.
    ///
    /// \return the current light index
    virtual size_t get_current() const                  = 0;

    /// \brief sample the current light source
    ///
    /// The method samples the current light and caches the obtained results.
    ///
    /// \return true if a sample was obtained and further samples should be taken,
    ///         false if no further samples are required.
    virtual bool sample()				= 0;

    /// \brief return dot product between light direction and surface normal
    ///
    /// \return the dot product between the light direction and the surface normal,
    ///         as obtained and chached during the last sampling.
    virtual miScalar get_dot_nl() const			= 0;

    /// \brief return the direction to the light source
    ///
    /// \return the direction vector to the light source, as obtained and cached 
    ///         during the last sampling.
    virtual const miVector& get_direction() const	= 0;

    /// \brief get the color contribution of the light source
    ///
    /// The method gets the cached color contribution obtained from the light 
    /// source during the last sampling.
    ///
    /// \param c
    ///         will contain the color contribution of the light source
    ///         on return
    virtual void get_contribution(miColor *c) const	= 0;

    /// \brief get the spectrum contribution of the light source
    ///
    /// The method gets the cached spectrum contribution obtained from the light
    /// source during the last sampling.
    ///
    /// \param s
    ///         will contain the spectrum contribution of the light source
    ///         on return
    virtual void get_contribution(miSpectrum *s) const	= 0;

    /// \brief returns the number of light samples taken so far.
    ///
    /// The method should be invoked after the sample method returned false. 
    /// It allows to weight the color/spectrum contributions of a light source 
    /// with the number of samples taken.
    ///
    /// \return the number of samples taken for the current light source.
    virtual int get_number_of_samples() const		= 0;

    /// \brief get the requested light tag
    ///
    /// The method obtains the light tag at the current'th position in 
    /// the light list.
    ///
    /// \param current
    ///         gives the index of the light in the list.
    /// \return the light tag at the requested position in the list.
    virtual miTag get_light_tag(size_t current) const	= 0;

    /// \brief obtain the number of lights in the list
    ///
    /// \return the number of lights in the light list.
    virtual size_t get_number_of_lights() const         = 0;

    /// \brief increase reference count
    ///
    /// Tell the light list that one more object (most likely a LightIterator)
    /// has connected to the list. As long as there are objects connected, the
    /// light list is not deleted.
    virtual void connect() 				= 0;

    /// \brief decrease reference count
    ///
    /// Tell the light list that an object (most likely a LightIterator)
    /// releases its connection to the list. If there are no more connections
    /// left, then the LightList will be deleted.
    virtual void release() 				= 0;
}; 


//-----------------------------------------------------------------------------
// inline implementation for LightIterator methods
//-----------------------------------------------------------------------------

inline LightIterator::LightIterator(
    miState		*state,
    const miVector	&axis,
    miScalar		spread_cos,
    miTag		*shader_light_list, 
    int      		n_shader_lights,
    int      		version)
: m_list(0)
, m_current(0)
{
    Interface* iface = Interface::get(version);
    m_list = iface->createLightList(state, axis, spread_cos, shader_light_list, n_shader_lights);
    iface->release();
}

inline LightIterator::LightIterator(
    miState		*state,
    miTag		*shader_light_list, 
    int      		n_shader_lights,
    int      		version)
: m_list(0)
, m_current(0)
{
    Interface* iface = Interface::get(version);
    m_list = iface->createLightList(state, state->normal, 0, shader_light_list, n_shader_lights);
    iface->release();
}

inline LightIterator::LightIterator(const LightIterator &iter) 
: m_list(iter.m_list)
, m_current(iter.m_current)
{ 
    if(m_list) m_list->connect();  // maintain reference count 
}

inline LightIterator::~LightIterator() 
{
    if(m_list) m_list->release();  // maintain reference count
}

inline const LightIterator& LightIterator::operator=(const LightIterator &iter)
{
    if(m_list != iter.m_list) {
        // need the compare above, otherwise the release might delete the list
        // and the connect below would be invalid.
        m_list->release();
        m_list = iter.m_list;
        m_list->connect();
    }
    m_current = iter.m_current;
    return *this;
}

inline miTag LightIterator::operator*() const 
{
    return m_list->get_light_tag(m_current);
}

inline LightList* LightIterator::operator->() const
{
    m_list->set_current(m_current);
    return m_list;
}

inline const LightIterator& LightIterator::operator++() 
{
    ++m_current;
    return *this;
}

inline LightIterator LightIterator::operator++(int)
{
    LightIterator res(*this);
    ++m_current;
    return res;
}

inline bool LightIterator::at_end() const
{
    return m_current == m_list->get_number_of_lights();
}

inline bool LightIterator::operator==(const LightIterator &iter) const 
{
    return m_list == iter.m_list && m_current == iter.m_current;
}

inline bool LightIterator::operator!=(const LightIterator &iter) const 
{
    return !this->operator==(iter);
}


}}

#endif //SHADER_LIGHTLIST_H
