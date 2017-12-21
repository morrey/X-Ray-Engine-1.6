#ifdef NT_ENV
#include "StdAfx.h"
#endif
//
// Class:   AmEdge
//
/*
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
*/


#include <stdio.h>

#ifdef WIN32
#include <io.h>
#endif

#include "AmEdge.h"

extern FILE *fp;

#define kFALSE false
#define kTRUE true

#ifdef WIN32
#define NULL 0
#endif


AmEdge::AmEdge( )
:	fEdgeId      ( 0 ),
    fStartIndex  ( 0 ),
    fEndIndex    ( 0 ),
	fHardEdge    ( kFALSE ),
    fNextEdge    ( NULL )
{ 
	fStartNormal[0] = fStartNormal[1] = fStartNormal[2] = 0.0;
	fEndNormal[0] = fEndNormal[1] = fEndNormal[2] = 0.0;
}

AmEdge::~AmEdge( )
{

}

void AmEdge::setEdge( int edgeId,
					  int startIndex,
					  int endIndex,
					  double *startNormal,
					  double *endNormal )
//
// Description:
//      This function sets the edge id and the indices of 
//      its two vertices.
//
// Arguments:
//      edgeId        - index to the edge
//      startIndex   - index to the start vertex of the edge
//      endIndex     - index to the end vertex of the edge
// 
{
	fEdgeId     = edgeId;
	fStartIndex = startIndex;
	fEndIndex   = endIndex;
	for( int i = 0; i < 3; i++)
	{
		fStartNormal[i] = startNormal[i];
		fEndNormal[i] = endNormal[i];
	}
}
 
int AmEdge::edgeId( )
//
// Description:
//      This function returns the edgeId.
//
{
	return fEdgeId;
}

int AmEdge::startIndex( )
//
// Description:
//      This function returns the index to the start vertex.

//
{
	return fStartIndex;
}

int AmEdge::endIndex( )
//
// Description:
//      This function returns the index to the end vertex.
//
{
	return fEndIndex;
}

void AmEdge::hardenEdge( )
//
// Description:
//      This function returns the ...
//
{
	fHardEdge = kTRUE;
}

double * AmEdge::startNormal( )
//
// Description:
//      This function returns the ...
//
{
	return fStartNormal;
}

double * AmEdge::endNormal( )
//
// Description:
//      This function returns the ...
//
{
	return fEndNormal;
}

void AmEdge::setNextEdge( AmEdge *nextEdge )
//
// Description:
//      This function sets the next edge.
//
// Arguments:
//      nextEdge   - next edge in the edge list
//
{
	fNextEdge = nextEdge;
}

AmEdge * AmEdge::nextEdge( )
//
// Description:
//      This function returns the pointer to the next edge.
//
{
	return fNextEdge;
}

void AmEdge:: printEdge( int counter )
{
	if( counter == fEdgeId )
		if( kTRUE == fHardEdge )
			fprintf( fp, "%s%d\t%d\t0\n", 
					   "\t\t", fStartIndex-1, fEndIndex-1 );
		else
			fprintf( fp, "%s%d\t%d\t1\n", 
					   "\t\t", fStartIndex-1, fEndIndex-1 );
	else
		fprintf( stderr, "Error: edge out of order!\n" );
}



