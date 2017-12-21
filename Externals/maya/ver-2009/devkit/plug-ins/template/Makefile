#-
# ==========================================================================
# Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
#
# Use of this software is subject to the terms of the Autodesk
# license agreement provided at the time of installation or download,
# or which otherwise accompanies this software in either electronic
# or hard copy form.
# ==========================================================================
#+

#
# Include platform specific build settings
#
include $(MAYA_LOCATION)/devkit/plug-ins/buildconfig

.SUFFIXES: .cpp .cc .o .so .c .bundle 

.c.o:
	$(CC) -c $(INCLUDES) $(CFLAGS) $<
	
.cc.o:
	$(C++) -c $(INCLUDES) $(C++FLAGS) $<

.cpp.o:
	$(C++) -c $(INCLUDES) $(C++FLAGS) $<

.cc.i:
	$(C++) -E $(INCLUDES) $(C++FLAGS) $*.cc > $*.i

.cc.so:
	-rm -f $@
	$(LD) -o $@ $(INCLUDES) $< $(LIBS)

.cpp.so:
	-rm -f $@
	$(LD) -o $@ $(INCLUDES) $< $(LIBS)

.o.so:
	-rm -f $@
	$(LD) -o $@ $< $(LIBS)

.o.bundle:
	-rm -f $@
	$(LD) -o $@ $< $(LIBS)

LINUX_PLUGINS = 

plugins: \
		$(PLATFORM_SPECIFIC_PLUGINS)	\
		createTransformNodeTemplate.$(EXT)	\
		helloTemplateWorld.$(EXT) \
		zoomCameraTemplate.$(EXT) 

depend:
	makedepend $(INCLUDES) -I/usr/include/CC *.cc

clean:
	-rm -f *.o

Clean:
	-rm -f *.o *.so *.lib *.bak *.bundle

#
# Specific Rules
# Required for more than one .cpp or .c per binary
#

zoomCameraTemplate.$(EXT): zoomCameraTemplate.o
	-rm -f $@
	$(LD) -o $@ $? $(LIBS) -lOpenMayaUI

