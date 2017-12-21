#ifdef NT_ENV
#include "StdAfx.h"
#endif
//
// Class:   AmEdgeList
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


#include <string.h>
#include "AmEdgeList.h"

#define kFALSE false
#define kTRUE true

AmEdgeList::AmEdgeList( )
:    fHeadNode  ( NULL ),
	fCurrentNode( NULL ),
	fLength     ( 0 )
{
}

AmEdgeList::~AmEdgeList( )
//
// Description:
//      This function traverses the edge list and deletes
//		all the edge nodes.
// 
{
	AmEdge *workingNode = NULL;
	AmEdge *nextNode    = NULL;
	
	workingNode = fHeadNode;
	fHeadNode = NULL;

	// Traverse the list to delete the nodes.
	//
	if( NULL != workingNode )
	{
		do 
		{
			nextNode = workingNode->nextEdge( );
			delete workingNode;
			workingNode = nextNode;
		} while( NULL != workingNode );
	}
}

void AmEdgeList::addEdge( int edgeId,
						  int startIndex,
						  int endVertex,
						  double *startNormal,
						  double *endNormal )
//
// Description:
//      This function builds up the edge list.
// 
// Arguments:
//      edgeId      - index to the edge
//      startIndex  - index of the start vertex
//      endIndex    - index of the end vertex
// 
{
	AmEdge *nextNode = new AmEdge;

	nextNode->setEdge( edgeId, startIndex, endVertex, startNormal, endNormal );
	nextNode->setNextEdge( NULL );

	if( 0 == fLength )
	{
		fHeadNode = nextNode;
		fCurrentNode = nextNode;
		fLength++;
	}
	else
	{
		fCurrentNode->setNextEdge( nextNode );
		fCurrentNode = nextNode;
		fLength++;
	}
}

void AmEdgeList::hardenEdge( int edgeId )
//
// Description:
//      This function ...
//
// Arguments:
//		
{
	AmEdge *workingNode = fHeadNode;

	// Traverse the list.
	//
	if( NULL != workingNode )
	{
		do 
		{

			if( edgeId == workingNode->edgeId() )
			{
				workingNode->hardenEdge();
				return;
			}
			workingNode = workingNode->nextEdge( );
		} while( NULL != workingNode );
	}
}

int AmEdgeList::findEdge( int startIndex,
						  int endIndex,
						  double *startNormal,
						  double *endNormal,
						  int &signEdge,
						  bool &hardEdge )
//
// Description:
//      This function finds the edge starting/ending
//      with vertex of startIndex and ending/starting
//      with vertex of endIndex. If the edge is found,
//      the edgeId is returned, otherwise -1 is returned.
//
// Arguments:
//		startIndex   - index of the start vertex
//      endIndex     - index of the end vertex
//      signEdge     - indicating the direction of the edge
//
{
	AmEdge *workingNode = fHeadNode;
	int i = 0;
	
	// Traverse the list.
	//
	if( NULL != workingNode )
	{
		do 
		{
			if( (startIndex == workingNode->startIndex()) &&
				(endIndex == workingNode->endIndex()) )
			{
				signEdge = 1;
				hardEdge = kFALSE;

				if( ( NULL != startNormal ) &&
					( NULL != endNormal ) )
				{
					double *wStartNormal = workingNode->startNormal();
					double *wEndNormal = workingNode->endNormal();
					for( i = 0; i < 3; i++ )
					{
						if( startNormal[i] != wStartNormal[i] )
						{
							hardEdge = kTRUE;
							break;
						}
						if( endNormal[i] != wEndNormal[i] )
						{
							hardEdge = kTRUE;
							break;
						}
					}
				}
				return workingNode->edgeId();
			}
			else if( (startIndex == workingNode->endIndex()) &&
					 (endIndex == workingNode->startIndex()) )
			{
				signEdge = -1;
				hardEdge = kFALSE;

				if( ( NULL != startNormal ) &&
					( NULL != endNormal ) )
				{
					double *wStartNormal = workingNode->startNormal();
					double *wEndNormal = workingNode->endNormal();
					for( i = 0; i < 3; i++ )
					{
						if( startNormal[i] != wEndNormal[i] )
						{
							hardEdge = kTRUE;
							break;
						}
						if( endNormal[i] != wStartNormal[i] )
						{
							hardEdge = kTRUE;
							break;
						}
					}
				}
				return workingNode->edgeId();
			}
			workingNode = workingNode->nextEdge( );
		} while( NULL != workingNode );
	}

	return -1;
}

void AmEdgeList::printEdges( )
//
// Description:
//      This function prints the edges in the list.
// 
{
	AmEdge *workingNode = fHeadNode;

	int counter = 1;
	// Traverse the list.
	//
	if( NULL != workingNode )
	{
		do 
		{
			workingNode->printEdge( counter );
			workingNode = workingNode->nextEdge( );
			counter++;
		} while( NULL != workingNode );
	}
}
