//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

// Description:
//				Metacycle is not implemented in Maya.
//			  	All the functions in this file either return NULL 
//              or commented out at this point.
//

#include <stdio.h>
#if defined (UNIX) || defined (WIN32)
#include <malloc.h>
#endif

#include <MDt.h>


// HERE ARE THE BACKDOORS!
//
#define ACN_NODE_PREVIEW_LOOPS  0
#define ACN_NODE_PREVIEW_FRAMES 1
#define ACN_STARTFRAME_ONE      0
#define ACN_STARTFRAME_END      1
#define ACN_STARTFRAME_SPACED   2
#define ACN_STARTFRAME_ALL      3

#define ACN_ENDFRAME_START          0
#define ACN_ENDFRAME_ONE            1

#define ACN_ROLLING_ENDPOINT     0
#define ACN_FIXED_ENDPOINT       1

#define ACN_ROLLING_STARTPOINT     0
#define ACN_FIXED_STARTPOINT       1

#define ACN_LINEAR               0
#define ACN_EASE                 1

#ifdef WIN32
#include <string.h>
#else
#include <strings.h>
#endif

/*
 * This is a magic number to terminate a list of transitions.
 */
#define LIST_TERM -999999


//
// Return a count of the number of characters in the scene
//
int DtCnetCharacterCount( int *count )
{
	*count = 0;

	return 0;
}

// 
// Returns the range of frames defined in the character network.
// 1 on success, 0 on failure
//
//	Not implemented for Maya

int DtCnetCharacterGetFrameRange(int cnetId, int *start, int *end)
{
	*start = 0;
	*end = 0;

	return(0);
}  


//
// Return the number and list of parent shapes that belong
// to the character.
// 1 on success, 0 on failure.
//
//	Not implemented for Maya

int DtCnetCharacterGetShapes(int cnetId, int *count, int **shapelist)
{
	*count = 0;
	*shapelist = NULL;

	return(0);
}

//
// Return the name of character N
//
int DtCnetCharacterName( int i, char **name )
{
	return 0;
}

//
// Return a state table corresponding to character N
//
int DtCnetGetStateTable( int i, DtStateTable **table )
{
	return 0;
}

