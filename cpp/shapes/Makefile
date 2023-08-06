
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = point.cpp shape.cpp circle.cpp shapesTest.cpp rectangle.cpp triangle.cpp group.cpp

# list of directories containing header files
PROJ_INC_DIR =

# the executable file
PROJ_OUT = shapesTest.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS =

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =

# additional libraries
PROJ_LIBS = glut_utils

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
#PROJ_DEPENDS  = ./MkGlutUtils.mak

include $(ROOT_DIR)/make/Project.mak
