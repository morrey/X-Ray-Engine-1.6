#ifndef _AmEdgeList
#define _AmEdgeList
//
// Class:    AmEdgeList
//
// Description:
//              The object of this class is a linked list
//              of edges.
//
//              AmEdgeList:
//                              ----------
//                              | AmEdge |
//                              ----------
//                                  |
//                              ----------
//                              | AmEdge |
//                              ----------
//                                  |
//                              ----------
//                              | AmEdge |
//                              ----------
//                                  :
//
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

#include "AmEdge.h"

class AmEdgeList {

public:

	AmEdgeList      ( );
    ~AmEdgeList     ( );
	
	void addEdge    ( int edgeId, int startIndex, int endIndex,
					  double *startNormal, double *endNormal );

	int findEdge	( int startIndex, int endIndex,
					  double *startNormal, double *endNormal,
					  int &signEdge, bool &hardEdge );

	void hardenEdge ( int edgeId );
	void printEdges ( );

private:

	int    fLength;        // length of the edge list
	AmEdge *fHeadNode;     // pointer to the first node of the list 
	AmEdge *fCurrentNode;  // pointer to the current node of the list
};

#endif /* _AmEdgeList */
