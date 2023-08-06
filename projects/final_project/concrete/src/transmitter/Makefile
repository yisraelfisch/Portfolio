
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../../../..

#PROJ_SRCS = $(wildcard *.cpp)
PROJ_SRCS = transmitter.cpp transmitterTest.cpp

# list of directories containing header files
#PROJ_INC_DIR = $(ROOT_DIR)/include
PROJ_INC_DIR = ../../include ../../../framework/include

# the executable file
PROJ_OUT = transmitterTest.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS =-std=c++11

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =  nbd_comm.o 

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  =  ../nbd_comm/Makefile  ../../../framework/src/observer/Makefile ../../../framework/src/singleton/Makefile ../../../framework/src/factory/Makefile

include $(ROOT_DIR)/make/Project.mak
