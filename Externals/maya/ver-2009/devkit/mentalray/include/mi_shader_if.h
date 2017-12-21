///////////////////////////////////////////////////////////////////////////////
// Copyright 1986-2008 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Author:	kjs
// Created:	09.01.06
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file mi_shader_if.h
/// mental ray C++ shader interface extensions.
///
/// This is a new C++ interface for shaders which extends the existing C-style
/// shader interface to mental ray. It is implemented as abstract interface
/// classes which do not require symbol lookups across dynamically lodable
/// library boundaries, like shaders. It also makes it possible to provide new,
/// even incompatible versions of the interface later.
///
/// Binaries which have been compiled with an older version of this header file
/// typically work with newer versions of this interface as long as the new
/// member functions have been appended at the end of the existing classes.
///
/// mi_shader_if.h is included from shader.h if the shader is compiled as C++
/// code; a shader does not need to include mi_shader_if.h directly.
/// 
/// The namespace alias shader_v3 is used to avoid conflict of inlined 
/// symbols between shader libraries compiled with different version.
/// On Linux plafroms, this relaxes the requirement to link shader libraries
/// with the -Bsymbolic option.

#ifndef MI_SHADER_IF_H
#define MI_SHADER_IF_H

// if file is included internally
#if !defined(SHADER_H)
#include <mi_raylib.h>
#include <mi_lib.h>
#include <mi_shader.h>
#endif

#ifndef __cplusplus
#error mi_shader_if.h requires C++ compilation
#endif


/// \brief version number of the interface
static const int mi_ray_interface_version = 3;

namespace mi {
namespace shader_v3 {
class Interface;
}}

/// \brief Acquire an instance of the mental ray C++ shader interface extensions.
///
/// \param version is the version number of the requested interface class
/// and should usually be left at the default value.
/// The passed version argument is used to support multiple different interface 
/// versions and should usually be the value of the variable
/// mi_ray_interface_version in the defining header file. A future version of
/// mental ray may optionally return a pointer to a newer version of the 
/// interface of a different type or in a different namespace, identified by a
/// different version number.
///
/// \return The returned pointer points to an object in mental ray which
/// contains the interface functions as virtual methods (hence it is possible to
/// call the interface routines from a dynamically loaded library without
/// resolving the routine in a symbol table). The caller may not attempt to
/// modify or delete the returned object but should call the
/// mi::shader::Interface::release() method when done.

extern "C" mi::shader_v3::Interface *mi_get_shader_interface(
    int version = mi_ray_interface_version);

//! \brief Top level namespace of mental ray
namespace mi {


/// \brief Namespace containing mental ray C++ shader interface extensions
///
/// The mental ray C++ interface is completely contained in the shader namespace.
/// \note This name may change later in order to support multiple versions of
/// the interface.
namespace shader_v3 {


/// forward declarations
class Options;
class LightList;
class Framebuffer;
class Map_status;
class Map_base;
class Map_edit_dbhandle;
class Map_access_dbhandle;
class Map_access;
class Map_edit;
class Map_declaration_base;
class Map_iterator_base;
class Map_element_base;
class Map_lookup_base;
class Bsdf;



/// \brief Top level C++ mental ray interface extensions.
///
/// This class is the top level access to the C++ shader interface extensions.
/// All other C++ extensions like mi::shader::Options and
/// mi::shader::LightIterator are accessible through this class.
///
/// An instance of the Interface must be acquired by calling
/// mi_get_shader_interface() or the static method Interface::get().
/// When the interface is no more needed, it must be released by calling
/// Interface::release():
/// \code
/// mi::shader::Interface *iface = mi::shader::Interface::get();
/// // do something with it...
/// iface->release();
/// \endcode
/// 
/// The C++ interface extensions are implemented as virtual functions in this
/// interface struct in order to avoid linking and symbol lookup problems.
/// The interface is defined in the header file mi_shader_if.h.

class Interface {
  public:
    /// \brief acquire an instance of the interface
    ///
    /// This static method is equivalent to the function
    /// mi_get_shader_interface(), see there fore more information.
    /// This static function can be used as follows:
    /// \code
    /// mi::shader::Interface *iface = mi::shader::Interface::get();
    /// \endcode
    /// \param version is the version number of the requested interface class,
    /// usually no version argument needs to be passed.
    /// \return The returned pointer points to an object in mental ray which
    /// contains the interface functions as virtual methods (hence it is 
    /// possible to call the interface routines from a dynamically loaded 
    /// library without resolving the routine in a symbol table). The caller may
    /// not attempt to modify or delete the returned object but should call the
    /// mi::shader::Interface::release() method when done.
    static inline Interface* get(
	int 		version = mi_ray_interface_version)
    { 
	return mi_get_shader_interface(version); 
    }

    /// \brief Access to string options.
    ///
    /// This may later be extended to also access all other options from the
    /// miOptions structure. This function can be used as follows:
    /// \code
    /// Options *stringOptions = interface->getOptions(options->string_options);
    /// \endcode
    /// \param string_options is the tag of the string options, taken from
    /// the string_options field of the miOptions structure to be read or
    /// modified.
    /// It must be valid throughout the use of the Options instance.
    /// \return A pointer to an interface class. The Options::release() method
    /// should be called when done.
    virtual Options *getOptions(
	miTag 		string_options);

    /// \brief Framebuffer factory function
    ///
    /// \return a database tag for an empty framebuffer collection.
    virtual miTag createFramebuffer();

    /// \brief Creates a copy of the framebuffer collection
    ///
    /// \param old_buffer_tag A database tag for the framebuffer to copy	
    /// \return a database tag for a copy of framebuffer collection.
    virtual miTag copyFramebuffer(
        miTag           old_buffer_tag);

    /// \brief Deprecated. Used internally by LightIterator to create a light list.
    ///
    /// This may be used to generate light iterators. This method is needed
    /// by the LightIterator::LightIterator() constructor. Usually there is no need to invoke
    /// this method directly.
    /// \param state provided the method with the current rendering state. From
    /// the state the current instance light list may be deduced.
    /// \param slist is an optional list of light tags. If provided, this list
    /// will be used instead of the default instance light list.
    /// \param n gives the number of light tags in the optional light list.
    /// \return the method returns a pointer to a LightList.
    virtual LightList *createLightList(
	miState		*state, 
	miTag 		*slist = 0, 
	int 		n = 0);

    /// \brief release (delete) the instance of the interface
    ///
    /// An interface acquired with mi_get_shader_interface() or 
    /// mi::shader::Interface::get() must be released with this call when 
    /// done. The call may delete the object, and the interface may no longer be
    /// used afterwards.
    virtual void release();


    /// \brief Used internally by LightIterator to create a light list.
    ///
    /// This may be used to generate light iterators. This method is needed
    /// by the LightIterator::LightIterator() constructor. Usually there is no need to invoke
    /// this method directly.
    /// \param state provided the method with the current rendering state. From
    /// the state the current instance light list may be deduced.
    /// \param axis specifies the axis for the light cone. The value should be normalized.
    /// \param spread_cos specifies the cosine of the angle to the light cone axis.
    /// \param slist is an optional list of light tags. If provided, this list
    /// will be used instead of the default instance light list.
    /// \param n gives the number of light tags in the optional light list.
    /// \return the method returns a pointer to a LightList.
    virtual LightList *createLightList(
	miState		*state,
	const miVector	&axis,
	miScalar	spread_cos,
	miTag		*slist = 0, 
	int 		n = 0);


    /// \brief creation of map. 
    ///
    /// This function is wrapped by the Map_edit class and should not be
    /// used directly.
    /// \param map_declaration is the declaration (possibly NULL) of the new map 
    /// \return pointer to the newly created map
    virtual Map_edit_dbhandle *createMap(
	const Map_declaration_base  *map_declaration = 0);

    /// \brief read-only access to a map in the DB.
    ///
    /// This function is wrapped by the Map_access class and should not be
    /// used directly
    /// \param map_tag database tag of the map
    /// \return pointer to the map
    virtual Map_access_dbhandle *accessMap(
	const miTag 		map_tag);

    /// \brief read-write access to a map in the DB.
    ///
    /// This function is wrapped by the Map_edit class and should not be
    /// used directly
    /// \param map_tag database tag of the map
    /// \return pointer to the map
    virtual Map_edit_dbhandle *editMap(
	const miTag 		map_tag);

    /// \brief read-only access to a map to be read from file.
    ///
    /// This function is wrapped by the Map_access class and should not be
    /// used directly
    /// \param filename the file name of the map to read
    /// \param status a status code
    /// \return pointer to the map
    virtual Map_access_dbhandle *accessMap(
	const char		*filename,
	Map_status		*status);

    /// \brief read-write access to a map to be read from file.
    ///
    /// This function is wrapped by the Map_edit class and should not be
    /// used directly
    /// \param filename the file name of the map to read
    /// \param status a status code
    /// \return pointer to the map
    virtual Map_edit_dbhandle *editMap(
	const char		*filename,
	Map_status		*status);

    /// \brief creation of a map declaration.
    ///
    /// This function is wrapped by the Map_declaration class and
    /// should not be used directly
    /// \param dimension is the dimension of the position
    /// \return pointer to the newly created map declaration
    virtual Map_declaration_base *createMapDeclaration(
	const miUint		dimension);

    /// \brief copy of a map declaration.
    ///
    /// This function is wrapped by the Map_declaration class and
    /// should not be used directly
    /// \param other is the handle of the declaration to copy
    /// \param status is a status code
    /// \return pointer to the newly copied map declaration
    virtual Map_declaration_base *copyMapDeclaration(
	const Map_declaration_base  *other,
	Map_status		    *status);

    /// \brief copy of the declaration of a map element.
    ///
    /// This function is wrapped by the Map_declaration class and
    /// should not be used directly
    /// \param map_element is the map element to get a copy of the decl from
    /// \param status is a status code
    /// \return pointer to the newly copied map declaration
    virtual Map_declaration_base *copyMapDeclaration(
	const Map_element_base	*map_element,
	Map_status		*status);

    /// \brief copy of the declaration of a map.
    ///
    /// This function is wrapped by the Map_declaration class and
    /// should not be used directly
    /// \param map is the map to get a copy of the declaration from
    /// \param status is a status code
    /// \return pointer to the newly copied map declaration
    virtual Map_declaration_base *copyMapDeclaration(
	const Map_base		*map,
	Map_status		*status);

    /// \brief creation of a map element.
    ///
    /// This function is wrapped by the Map_element class and
    /// should not be used directly
    /// \param declaration is the (possible) declaration to use
    /// \return pointer to the newly created map element
    virtual Map_element_base *createMapElement(
	const Map_declaration_base  *declaration = 0);

    /// \brief copy of a map element.
    ///
    /// This function is wrapped by the Map_element class and
    /// should not be used directly
    /// \param other is the element to copy
    /// \return pointer to the newly copied map element
    virtual Map_element_base *copyMapElement(
	const Map_element_base	*other);

    /// \brief creation of a map iterator.
    ///
    /// This function is wrapped by the Map_iterator_access/edit classes
    /// and should not be used directly
    /// \param map is the map to attach the iterator to
    /// \param status is a status code
    /// \return pointer to the newly created map iterator
    virtual Map_iterator_base *createMapIterator(
	const Map_base		*map,
	Map_status		*status);

    /// \brief copy of a map iterator.
    ///
    /// This function is wrapped by the map_iterator_access/edit classes
    /// and should not be used directly
    /// \param other is the iterator to copy
    /// \param status is a status code
    /// \return pointer to the newly copied map iterator
    virtual Map_iterator_base *copyMapIterator(
	const Map_iterator_base	*other,
	Map_status		*status);

    /// \brief creation of a map lookup.
    ///
    /// This function is wrapped by the Map_lookup class
    /// and should not be used directly
    /// \param map is the map to attach the lookup to
    /// \param status is a status code
    /// \return pointer to the newly created map lookup
    virtual Map_lookup_base *createMapLookup(
	const Map_base		*map,
	Map_status		*status);

    /// \brief copy of a map lookup.
    ///
    /// This function is wrapped by the Map_lookup class
    /// and should not be used directly
    /// \param other is the lookup to copy
    /// \param status is a status code
    /// \return pointer to the newly created map lookup
    virtual Map_lookup_base *copyMapLookup(
	const Map_lookup_base	*other,
	Map_status		*status);

    /// \if 0 (internal. for linkage, method need to be virtual this cannot be private).
    /// \brief Read-only access to framebuffer. 
    ///
    /// This functions is wrapped by the Access_fb class and should
    /// not be used directly
    /// /param buffer_tag database tag for the framebuffer collection
    /// /return pointer to the framebuffer class
    /// \endif
    virtual const Framebuffer *accessFramebuffer(
	miTag 		buffer_tag);

    /// \if 0 (internal. for linkage, method need to be virtual this cannot be private).
    /// \brief Release read-only access to framebuffer. 
    ///
    /// This functions is wrapped by the Access_fb class and should
    /// not be used directly
    /// /param buffer_tag database tag for the framebuffer collection
    /// /param pointer to the framebuffer class
    /// /return returns true on success
    /// \endif
    virtual bool releaseFramebuffer(
	const Framebuffer	*buffer,			   
	miTag 			buffer_tag);

    /// \if 0 (internal. for linkage, method need to be virtual this cannot be private).
    /// \brief Read-write access to framebuffer. 
    ///
    /// This functions is wrapped by the Edit_fb class and should
    /// not be used directly
    /// /param buffer_tag database tag for the framebuffer collection
    /// /return pointer to the framebuffer class
    /// \endif
    virtual Framebuffer *editFramebuffer(
	miTag 		buffer_tag);

    /// \if 0 (internal. for linkage, method need to be virtual this cannot be private).
    /// \brief Release read-write access to framebuffer. 
    ///
    /// This functions is wrapped by the Access_fb class and should
    /// not be used directly
    /// /param buffer_tag database tag for the framebuffer collection
    /// /param pointer to the framebuffer class
    /// /return returns true on success
    /// \endif
    virtual bool releaseFramebuffer(
	Framebuffer		*buffer,			   
	miTag 			buffer_tag);

    /// \if 0 (internal)
    /// \brief allocates a Bsdf instance.
    ///
    /// See @c Access_bsdf for details.
    /// \endif
    virtual Bsdf* allocBsdf(
	    miState* 		state);
 
    /// \if 0 (internal)
    /// \brief releases a Bsdf instance.
    ///
    /// See @c Access_bsdf for details.
    /// \endif
    virtual void releaseBsdf(
	    Bsdf* 		bsdf, 
	    miState* 		state);

};


/// \brief Access to string options
///
/// Up to version 3.4, options are hardcoded in the struct miOptions in
/// shader.h. New options are implemented as arbitrary name - value pairs,
/// where the name of the option is an arbitrary string, and the value can be a
/// boolean, string, integration, float, 3 floats, or 4 floats.
///
/// A pointer to string options must be obtained with Interface::getOptions().
/// When the pointer is no longer needed then the Options::release() method
/// must be called, like for example:
/// \code
/// mi::shader::Interface *iface = mi_get_shader_interface();
/// mi::shader::Options *opt = iface->getOptions(string_options_tag);
/// iface->release();
/// opt->set("favorite color", "blue");
/// opt->release();
/// \endcode
/// 
/// <h3>Setting options</h3>
/// Set functions set the value of an option of a given name, overwriting any
/// previous value. Previous values may be overwritten by values of a different
/// type.
///
/// \note Options should only be set before rendering starts. It is undefined
/// which value will be used if an option is set during rendering.
///
/// <h3>Getting options</h3>
/// All get functions return true and set the value if a matching option is
/// found, or returns false leave the value unmodified if no matching option is
/// found.
///
/// <h3>Strings and memory management</h3>
/// Strings passed as arguments are completely controlled by the caller; mental
/// ray uses the strings briefly, or makes copies of the passed strings.
///
/// Strings returned by these functions are read-only and controlled by mental
/// ray. The caller may use these only for a short time and may not delete them.
/// Make a copy if the value is needed later.

class Options {
  public: 
    /// \{

    /// \brief set a boolean option
    /// \param name is the name of the option to set.
    /// \param value is the new value of the option.
    virtual void set(
	const char 	*name, 
	bool 		value) = 0;

    /// \brief set a string option
    /// \param name is the name of the option to set.
    /// \param value mental ray will make a copy of the passed string \a value,
    /// the passed argument is under control
    /// of the caller.
    virtual void set(
	const char 	*name, 
	const char *	value) = 0;

    /// \brief set an integer option
    ///\note Integer options may also be used as floating point values.
    /// \param name is the name of the option to set.
    /// \param value is the new value of the option.
    virtual void set(
	const char 	*name, 
	int 		value) = 0;

    /// \brief set a floating point option
    /// \param name is the name of the option to set.
    /// \param value is the new value of the option.
    virtual void set(
	const char 	*name, 
	float 		value) = 0;

    /// \brief set a float triple option
    /// \param name is the name of the option to set.
    /// \param value1 is the first component of the triple.
    /// \param value2 is the second component of the triple.
    /// \param value3 is the third component of the triple.
    virtual void set(
	const char 	*name,
	float 		value1, 
	float 		value2, 
	float 		value3) = 0;

    /// \brief set a float quadruple option
    /// \param name is the name of the option to set.
    /// \param value1 is the first component of the quadruple.
    /// \param value2 is the second component of the quadruple.
    /// \param value3 is the third component of the quadruple.
    /// \param value4 is the third component of the quadruple.
    virtual void set(
	const char 	*name, 
	float 		value1, 
	float 		value2, 
	float 		value3, 
	float 		value4) = 0;

    /// \brief get a boolean option
    /// \param name is the name of the option to look up
    /// \param value will be set on success, and left unchanged otherwise.
    /// \return true if an option of the given name and type is found, false
    /// otherwise.
    virtual bool get(
	const char 	*name, 
	bool 		*value) const = 0;

    /// \brief get a string option
    /// \param name is the name of the option to look up
    /// \param value The returned string \a value is only value for a short
    /// time, and may not be modified or deleted by the caller. The caller
    /// should make a copy of the string if needed.
    /// \return true if an option of the given name and type is found, false
    /// otherwise.
    virtual bool get(
	const char 	*name, 
	const char 	**value) const = 0;

    /// \brief get an integer option
    /// \param name is the name of the option to look up
    /// \param value will be set on success, and left unchanged otherwise.
    /// \return true if an option of the given name and type is found, false
    /// otherwise.
    virtual bool get(
	const char 	*name, 
	int 		*value) const = 0;

    /// \brief get a floating point option
    ///
    /// If the value of the named option is an integer then the integer is
    /// converted to a floating point number and returned in \a value.
    /// \param name is the name of the option to look up
    /// \param value will be set on success, and left unchanged otherwise.
    /// \return true if an option of the given name and type is found, false
    /// otherwise.
    virtual bool get(
	const char 	*name, 
	float 		*value) const = 0;

    /// \brief get a floating point triple option
    ///
    /// This can be used for RGB colors or 3 dimensional vectors.
    /// \param name is the name of the option to look up
    /// \param value1 will be set to the first component on success, and left
    /// unchanged otherwise.
    /// \param value2 will be set to the second component on success, and left
    /// unchanged otherwise.
    /// \param value3 will be set to the third component on success, and left
    /// unchanged otherwise.
    /// \return true if an option of the given name and type is found, false
    /// otherwise.
    virtual bool get(
	const char 	*name, 
	float 		*value1, 
	float 		*value2, 
	float 		*value3) const = 0;

    /// \brief get a floating point quadruple option
    ///
    /// This can be used for RGBA colors or 4 dimensional homogenous vectors.
    /// \param name is the name of the option to look up
    /// \param value1 will be set to the first component on success, and left 
    /// unchanged otherwise.
    /// \param value2 will be set to the second component on success, and left 
    /// unchanged otherwise.
    /// \param value3 will be set to the third component on success, and left 
    /// unchanged otherwise.
    /// \param value4 will be set to the fourth component on success, and left 
    /// unchanged otherwise.
    /// \return true if an option of the given name and type is found, false 
    /// otherwise.
    virtual bool get(
	const char	*name,
	float 		*value1,
	float 		*value2,
	float 		*value3,
	float 		*value4) const = 0;

    /// \brief delete a specific option
    ///
    /// This can be used to remove unneeded options. 
    /// \return true if an option of the given name and type is found, false 
    /// otherwise. 
    virtual bool remove(
	const char	*name) = 0;

    /// \brief release (delete) the interface
    ///
    /// This should be called when done. It may release the Options object.
    virtual void release() = 0;
};



/// \brief Interface wrapper class
///
class Interface_access {
public:
    /// \brief constructor
    Interface_access()
	: m_iface (mi_get_shader_interface())
    {}

    /// \brief destructor
    ~Interface_access()
    {
	m_iface->release();
	m_iface = 0;
    }

    /// \brief dereference operator
    mi::shader_v3::Interface * operator->()
    {
	return m_iface;
    }

private:
    mi::shader_v3::Interface *m_iface;
};


} // namespace shader_v3


// namespace alias, shaders should use it
namespace shader = shader_v3;

} // namespace mi

#include "shader_framebuffer.h"
#include "shader_map.h"
#include "shader_lightlist.h"

#endif // MI_SHADER_IF_H
