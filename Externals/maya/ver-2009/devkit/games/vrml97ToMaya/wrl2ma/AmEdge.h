#ifndef _AmEdge
#define _AmEdge
//
// Class:    AmEdge
//
// Description:
//              The object of this class represents an edge 
//              with one field pointing to another edge.
//
//              AmEdge:
//                          ---------------
//                          | fEdgeId     |
//                          ---------------
//                          | fStartIndex |
//                          ---------------
//                          | fEndIndex   |
//                          ---------------
//                          | fNextEdge   |
//                          ---------------
//                               |
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

class AmEdge {

public:

	AmEdge               ( );
	~AmEdge              ( );
	
	void setEdge         ( int edgeId, int startIndex, int endIndex,
						   double *startNormal, double *endNormal );

	int edgeId           ( );
	int startIndex       ( );
	int endIndex         ( );
	double *startNormal  ( );
	double *endNormal	 ( );
	
	int hardEdge     ( );
	void hardenEdge      ( );
	
	void setNextEdge     ( AmEdge * );
	AmEdge *nextEdge     ( );

	void printEdge       ( int counter );
private:

	int      fEdgeId;      // index to the edge
	int      fStartIndex;  // index of the start vertex
	int      fEndIndex;    // index of the end vertex
	double	 fStartNormal[3];
	double   fEndNormal[3];
	bool	 fHardEdge;
	AmEdge   *fNextEdge;   // next edge in the edge list
};

#endif /* _AmEdge */



