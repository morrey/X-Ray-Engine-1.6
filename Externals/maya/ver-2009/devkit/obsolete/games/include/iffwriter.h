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

#ifndef _iffwriter_h
#define _iffwriter_h

typedef unsigned char byte;

class MStatus;
class MString;

class IFFimageWriter
{
public:
        IFFimageWriter ();
        ~IFFimageWriter ();
        MStatus open (MString filename);
        MStatus close ();
		MStatus outFilter( const char * );
        MStatus writeImage ( byte *, float *, int);
        MStatus setSize ( int x, int y);
		MStatus setBytesPerChannel( int bpp);
		MStatus setType( int type);
        MString errorString ();

protected:
        ILimage *fImage;
        byte *fBuffer;
        float *fZBuffer;

		int	Bpp;
		int	Xsize;
		int Ysize;

};

#endif
