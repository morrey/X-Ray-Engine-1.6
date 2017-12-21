#ifndef _MGlobal
#define _MGlobal
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related
// material (collectively the "Data") in these files contain unpublished
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its
// licensors,  which is protected by U.S. and Canadian federal copyright law
// and by international treaties.
//
// The Data may not be disclosed or distributed to third parties or be
// copied or duplicated, in whole or in part, without the prior written
// consent of Autodesk.
//
// The copyright notices in the Software and this entire statement,
// including the above license grant, this restriction and the following
// disclaimer, must be included in all copies of the Software, in whole
// or in part, and all derivative works of the Software, unless such copies
// or derivative works are solely in the form of machine-executable object
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE,
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES.
// ==========================================================================
//+
//
// CLASS:    MGlobal
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MSelectionMask.h>
#include <maya/MTransformationMatrix.h>

// ****************************************************************************
// DECLARATIONS

class MPoint;
class MString;
class MTime;
class MVector;
class MSelectionList;
class MRichSelection;
class MDagPath;
class MObjectArray;
class MCommandResult;

// ****************************************************************************
// CLASS DECLARATION (MGlobal)

//! \ingroup OpenMaya
//! \brief Static class providing common API global functions. 
/*!
  Provide methods for selection, 3D-views, time, model manipulation and MEL
  commands.

  MGlobal is a static class which provides access to Maya's model (3d
  graphical database).

  MGlobal provides methods for selection, 3d-views, setting the global
  time, adding to the DAG, and executing MEL commands from within the
  API.  There are multiple methods provided in this class for
  executing MEL within the API.  Plug-ins requiring the execution of
  MEL from the non-main Maya thread must use the
  executeCommandOnIdle() method to avoid program errors.

  MGlobal also provides methods for controlling error logging in the API.
*/
class OPENMAYA_EXPORT MGlobal
{
public:
	static MString      mayaVersion ();

	static int          apiVersion ();

	//! State in which Maya has been started.
	enum MMayaState	{
		kInteractive,	//!< Running with a UI.
		kBatch,			//!< Running without a UI.
		kLibraryApp,	//!< A standalone (MLibrary) application is running.
		kBaseUIMode		//!< Running in baseUI mode.
	};

	static MMayaState   mayaState( MStatus * ReturnStatus = NULL );
	static MStatus		getFunctionSetList( MObject forObject,
											MStringArray & array );
	static MStatus		getAssociatedSets( const MSelectionList & list,
											MObjectArray & setArray );
    static MStatus		getSelectionListByName( const MString& name,
												MSelectionList &list );
	//! Operations on selection lists
    enum ListAdjustment {
        kReplaceList,   //!< Totally replace the list with the given items.
		/*! For each item, remove it to the list if that are
		  already present, add it otherwise.
		*/
		kXORWithList,   
        kAddToList,     //!< Add the items to the list.
        kRemoveFromList, //!< Remove the items from the list.
		kAddToHeadOfList //!< Add to beginning of the list.
    };

	//! Choices for types of selection methods used in the selectFromScreen functions.
	enum SelectionMethod {
		kSurfaceSelectMethod,	//!< Select based on the wireframe of the objects.
		kWireframeSelectMethod	//!< Select based on the surface of the objects.
	};

	static MStatus	 	getActiveSelectionList( MSelectionList & dest );
	static MStatus	 	getRichSelection( MRichSelection & dest, bool defaultToActiveSelection = true);
	static MStatus 		getLiveList( MSelectionList & dest );
	static MStatus 		getHiliteList( MSelectionList & dest );
	static MStatus 		setHiliteList( MSelectionList & src );
	static MStatus	 	setActiveSelectionList( const MSelectionList & src,
									   ListAdjustment=kReplaceList);
	static MStatus 		setDisplayCVs( MSelectionList&, bool );
	//
	static MStatus		selectCommand( const MSelectionList & src,
									   ListAdjustment=kReplaceList);
    static MStatus		selectByName( const MString& name,
									  ListAdjustment=kAddToList );
    static MStatus		unselectByName( const MString& name );
    static MStatus		select( MObject& object, ListAdjustment=kAddToList );
    static MStatus		select( const MDagPath& object, const MObject& component,
								ListAdjustment=kAddToList );
    static MStatus		unselect( MObject& object );
    static MStatus		unselect( const MDagPath& object, const MObject& component );
    static MStatus		selectFromScreen( const short& x_pos,
										  const short& y_pos,
                                          ListAdjustment=kAddToList,
										  SelectionMethod=kWireframeSelectMethod);
    static MStatus		selectFromScreen( const short& start_x,
										  const	short& start_y,
                                          const short& end_x,
										  const short& end_y,
                                          ListAdjustment=kAddToList,
										  SelectionMethod=kWireframeSelectMethod);
	static SelectionMethod selectionMethod( MStatus * ReturnStatus = NULL );

	//! Global selection modes
	enum MSelectionMode {
		kSelectObjectMode,		//!< Select objects.
		kSelectComponentMode,	//!< Select components.
		kSelectRootMode,		//!< Select DAG roots.
		kSelectLeafMode,		//!< Select DAG leaves.
		kSelectTemplateMode		//!< Select templates.
	};

	static MSelectionMode selectionMode( MStatus * ReturnStatus = NULL );
	static MStatus		  setSelectionMode( MSelectionMode mode );

	static MSelectionMask objectSelectionMask( MStatus * ReturnStatus = NULL );
	static MStatus		  setObjectSelectionMask( const MSelectionMask& mask );
	static MSelectionMask componentSelectionMask( MStatus * ReturnStatus =
												  NULL );
	static MStatus		  setComponentSelectionMask( const MSelectionMask& mask );
	static MSelectionMask animSelectionMask( MStatus * ReturnStatus = NULL );
	static MStatus		  setAnimSelectionMask( const MSelectionMask& mask );
	static MSelectionMask miscSelectionMask( MStatus * ReturnStatus = NULL );
	static MStatus		  setMiscSelectionMask( const MSelectionMask& mask );

	static MStatus		  clearSelectionList();
	static bool			  isSelected( MObject& object,
							  		  MStatus * ReturnStatus = NULL );

	static MStatus		viewFrame( const MTime & time );
	static MStatus      viewFrame( double time);

	static MStatus		sourceFile( const MString& fileName );
	static MStatus 		executeCommandOnIdle( const MString& command,
										bool displayEnabled = false);
	static MStatus 		executeCommand( const MString& command,
										bool displayEnabled = false,
										bool undoEnabled = false);
	static MStatus		executeCommand( const MString& command,
										MCommandResult& result,
										bool displayEnabled = false,
										bool undoEnabled = false );
	static MStatus		executeCommand( const MString& command,
										int& result,
										bool displayEnabled = false,
										bool undoEnabled = false );
	static MStatus		executeCommand( const MString& command,
										MIntArray& result,
										bool displayEnabled = false,
										bool undoEnabled = false );
	static MStatus		executeCommand( const MString& command,
										double& result,
										bool displayEnabled = false,
										bool undoEnabled = false );
	static MStatus		executeCommand( const MString& command,
										MDoubleArray& result,
										bool displayEnabled = false,
										bool undoEnabled = false );
	static MStatus		executeCommand( const MString& command,
										MStringArray& result,
										bool displayEnabled = false,
										bool undoEnabled = false );
	static MString		executeCommandStringResult( const MString& command,
													bool displayEnabled = false,
													bool undoEnabled = false,
													MStatus * ResultStatus = NULL);

BEGIN_NO_SCRIPT_SUPPORT:
	//! \noscript
	static MStatus		executeCommand( const MString& command,
										MString& result,
										bool displayEnabled = false,
										bool undoEnabled = false );

	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												bool displayEnabled = false,
												bool undoEnabled = false );

	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												int& result,
												bool displayEnabled = false,
												bool undoEnabled = false );

	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												MIntArray& result,
												bool displayEnabled = false,
												bool undoEnabled = false );

	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												double& result,
												bool displayEnabled = false,
												bool undoEnabled = false );

	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												MDoubleArray& result,
												bool displayEnabled = false,
												bool undoEnabled = false );
	//! \noscript
	static MString		executePythonCommandStringResult (	const MString& command,
												bool displayEnabled = false,
												bool undoEnabled = false,
												MStatus * ReturnStatus = NULL);
	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												MString& result,
												bool displayEnabled = false,
												bool undoEnabled = false );

	//! \noscript
	static MStatus		executePythonCommand (	const MString& command,
												MStringArray& result,
												bool displayEnabled = false,
												bool undoEnabled = false );
	//! \noscript
	static MStatus 		executePythonCommandOnIdle( const MString& command,
												bool displayEnabled = false);
END_NO_SCRIPT_SUPPORT:


    static MStatus      addToModel( MObject & object,
									  MObject & parent = MObject::kNullObj );
    static MStatus      addToModelAt( MObject&, const MVector& point,
								  const double scale[3]  = NULL,
								  const double rotation[3] = NULL,
								  MTransformationMatrix::RotationOrder order =
									  MTransformationMatrix::kXYZ );
    static MStatus      removeFromModel( MObject& );
    static MStatus      deleteNode( MObject& );
    static MStatus      setYAxisUp( bool rotateView = false );
    static MStatus      setZAxisUp( bool rotateView = false );
    static bool			isYAxisUp( MStatus* = NULL );
    static bool			isZAxisUp( MStatus* = NULL );
    static MVector      upAxis( MStatus* = NULL );

	static void			displayInfo( const MString & theMessage );
	static void			displayWarning( const MString & theWarning );
	static void			displayError( const MString & theError );
	static void			setDisableStow( bool state );
	static bool			disableStow( );

	//! setting & getting option variable values
	static int			optionVarIntValue(const MString& name, bool *result = NULL );
	static double		optionVarDoubleValue(const MString& name, bool *result = NULL);
	static MString		optionVarStringValue(const MString& name, bool *result = NULL);
	static bool			setOptionVarValue(const MString& name, int value);
	static bool			setOptionVarValue(const MString& name, double value);
	static bool			setOptionVarValue(const MString& name, MString value);


//	Support for DEBUG/NDEBUG API
//
	static MString		defaultErrorLogPathName( MStatus* ReturnStatus = NULL );
	static MStatus		resetToDefaultErrorLogPathName();
	static MStatus		setErrorLogPathName( const MString& logPathName );
	static MString		errorLogPathName( MStatus* ReturnStatus = NULL );
	static MStatus		startErrorLogging();
	static MStatus		startErrorLogging( const MString& logPathName );
	static bool			errorLoggingIsOn( MStatus* ReturnStatus = NULL );
	static MStatus		stopErrorLogging();
	static MStatus		closeErrorLog();
	static MStatus		doErrorLogEntry( const MString& errorLogEntry );
	static bool			isUndoing();
	static bool			isRedoing();

//	Deprecated methods
//
BEGIN_NO_SCRIPT_SUPPORT:
	//! \obsolete \noscript
	static bool			getOptionVarValue(const MString& name, int& value);
	//! \obsolete \noscript
	static bool			getOptionVarValue(const MString& name, double& value);
	//! \obsolete \noscript
	static bool			getOptionVarValue(const MString& name, MString& value);
	//! \obsolete \noscript
    static MStatus		select( MDagPath& object, const MObject& component,
								ListAdjustment=kAddToList );
	//! \obsolete \noscript
    static MStatus		unselect( MDagPath& object, const MObject& component );
END_NO_SCRIPT_SUPPORT:

protected:
	static const char* className();
private:
	~MGlobal();
#ifdef __GNUC__
	friend class shutUpAboutPrivateDestructors;
#endif
};

#endif /* __cplusplus */
#endif /* _MGlobal */
