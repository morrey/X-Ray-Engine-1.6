#-
# ==========================================================================
# Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
# rights reserved.
#
# The coded instructions, statements, computer programs, and/or related 
# material (collectively the "Data") in these files contain unpublished 
# information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
# licensors, which is protected by U.S. and Canadian federal copyright 
# law and by international treaties.
#
# The Data is provided for use exclusively by You. You have the right 
# to use, modify, and incorporate this Data into other products for 
# purposes authorized by the Autodesk software license agreement, 
# without fee.
#
# The copyright notices in the Software and this entire statement, 
# including the above license grant, this restriction and the 
# following disclaimer, must be included in all copies of the 
# Software, in whole or in part, and all derivative works of 
# the Software, unless such copies or derivative works are solely 
# in the form of machine-executable object code generated by a 
# source language processor.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
# AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
# WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
# NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
# PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
# TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
# BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
# DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
# AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
# OR PROBABILITY OF SUCH DAMAGES.
#
# ==========================================================================
#+


#
# Description: 
#	
#	Running this application will start a Maya standalone python application.
#
# Usage:
#
#	Set the environment variable MAYA_LOCATION to your Maya path and in 
#	a shell on Linux execute:
#	
#	$MAYA_LOCATION/bin/mayapy helloWorld.py
#
#	NOTE: you must use the Python executable that ships
# 	with Maya for this to work.  This executable may be located
#	in a different directory for other platforms.

import maya.standalone
import maya.OpenMaya as OpenMaya

import sys

def main( argv = None ):
	try:
		maya.standalone.initialize( name='python' )
	except:
		sys.stderr.write( "Failed in initialize standalone application" )
		raise

	sys.stderr.write( "Hello world! (script output)\n" )
	OpenMaya.MGlobal().executeCommand( "print \"Hello world! (command script output)\\n\"" )
	
if __name__ == "__main__":
    main()