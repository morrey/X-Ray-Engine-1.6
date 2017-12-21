///////////////////////////////////////////////////////////////////////////////
// Copyright 1986-2008 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Author:	carsten
// Created:	27.02.08
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file shader_framebuffer.h
/// mental ray C++ shader interface extensions.
///
/// This file provides interfaces that allow interaction with frame buffers.
///
/// shader_framebuffer.h is included by mi_shader_if.h, which in turn is 
/// included from shader.h if the shader is compiled as C++ code.
/// A shader does not need to include this file directly.


#ifndef SHADER_FRAMEBUFFER_H
#define SHADER_FRAMEBUFFER_H
#include "mi_shader_if.h"

namespace mi {
namespace shader_v3 {


/// \brief Framebuffer class.
///
/// The Framebuffer class is a collection of framebuffers used for a frame rendering.
/// It provide an interface to the named framebuffer attributes.
/// It also allows to retrieve the index of the buffer to use it with
/// <tt>mi_fb_put</tt> and <tt>mi_fb_get</tt> functions.
/// 
/// All strings are const char. Strings passsed in are copied, and need to
/// be freed by the user. Strings passed out should be copied by the user,
/// since they reference internal data.
///
class Framebuffer {
    public:
        /// \brief set a boolean attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const 	bool value) = 0;

        /// \brief set a float attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const float value) = 0;

        /// \brief set an integer attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const int 	value) = 0;

        /// \brief set an integer attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute. A copy of the value is stored.
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const char 	*value) = 0;

        /// \brief get a boolean attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            bool 	&value) const = 0;

        /// \brief get a float attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            float 	&value) const = 0;

        /// \brief get an integer attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise. 
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            int 	&value) const = 0;

        /// \brief get a string attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            const char 	*&value) const = 0;

        /// \brief get an index of the framebuffer to be used in
        /// <tt>mi_fb_put</tt> and <tt>mi_fb_get</tt> functions.
        /// \param buffer is the name of the framebuffer
        /// \param index is the returned index
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get_index(const char *buffer, size_t &index) const = 0;

        /// \brief removes all named buffers.
        /// It is not legal to call this method during the rendering process.
        /// \return true if the operation is successful, false otherwise.
        virtual bool reset() = 0;

        /// \brief echoes mi syntax for the framebuffer to the file pointer.
        virtual void echo(FILE *) const = 0;

        /// \brief get the count of buffers defined.
        /// \param buffercount is the number of buffers.
        /// \return false on failure.
        virtual bool get_buffercount(size_t &buffercount) const = 0;

        /// \brief get the name of buffer num. Note that num
        /// is not related to the index returned by <tt>get_index</tt>
        /// \param num is the number of the buffer name to return,
        /// starting with 0.
        /// \param name is the returned buffer name.
        /// \return false on failure.
        virtual bool get_buffername(size_t num, const char *&name) const = 0;

        /// \brief removes the named buffer.
        /// It is not legal to call this method during the rendering process.
        /// \return true if the operation is successful, false otherwise.
        virtual bool remove(const char *buffer) = 0;
};

/// \brief Smart pointer to access Framebuffer class, no editing.
///
/// There resources are released automatically when Access_fb goes out of scope.
/// For editing operations use Edit_fb.
class Access_fb {
    public:
        /// \brief smart pointer for the Framebuffer tag, read-only access.
        /// \param tag framebuffer database tag.
        Access_fb(
	    miTag tag);

	/// \brief release resources, unpin database tag
        ~Access_fb();

	/// \brief reference the Framebuffer class, read-only access
        const Framebuffer * operator->() const;
    private:
        Access_fb();
        Access_fb(const Access_fb &);
        const Access_fb & operator=(const Access_fb &);
	mi::shader_v3::Interface	*m_iface;
        const Framebuffer 		*const m_fb;
	const miTag	  	 	m_tag;
};


/// \brief Smart pointer to access Framebuffer class for editing.
///
/// There resources are released automatically when Edit_fb goes out of scope.

class Edit_fb {
    public:
        /// \brief smart pointer for the Framebuffer tag, read-write access.
        /// \param tag framebuffer database tag
        Edit_fb(
	    miTag tag);

	/// \brief release resources, unpin database tag
        ~Edit_fb();

	/// \brief reference the Framebuffer class, read-write access
        Framebuffer * operator->() const;
    private:
        Edit_fb();
        Edit_fb(const Edit_fb &);
        const Edit_fb & operator=(const Edit_fb &);
	mi::shader_v3::Interface	*m_iface;
	Framebuffer 			*const m_fb;
	const miTag			m_tag;
};

/// \brief Framebuffer access wrapper class.
///
inline Access_fb::Access_fb(
    miTag tag)
  : m_iface(mi_get_shader_interface())
  , m_fb(m_iface->accessFramebuffer(tag))
  , m_tag(tag)
{
}

inline Access_fb::~Access_fb()
{
    if (m_fb != 0) {
	m_iface->releaseFramebuffer(m_fb, m_tag);
    }
    m_iface->release();
}

inline const Framebuffer * Access_fb::operator->() const
{
    return m_fb;
}

/// \brief Framebuffer edit wrapper class.
///
inline Edit_fb::Edit_fb(
    miTag tag)
  : m_iface(mi_get_shader_interface())
  , m_fb(m_iface->editFramebuffer(tag))
  , m_tag(tag)
{
}

inline Edit_fb::~Edit_fb()
{
    if (m_fb != 0) {
	m_iface->releaseFramebuffer(m_fb, m_tag);
    }
    m_iface->release();
}

inline Framebuffer * Edit_fb::operator->() const
{
    return m_fb;
}


}}

#endif //SHADER_FRAMEBUFFER_H
