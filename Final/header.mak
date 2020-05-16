#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL, GLUT, and/or GLEW
# on the Ubuntu systems.
#
# To use it, place it in the same directory as your source code, and
# run the command
#
#	gmakemake > Makefile
#
# To compile and link your program, just run "make".
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
INCLUDE =
LIBDIRS =

LDLIBS = -lglut -lGL -lm -lGLEW

CFLAGS = -g $(INCLUDE) -DGL_GLEXT_PROTOTYPES
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)
