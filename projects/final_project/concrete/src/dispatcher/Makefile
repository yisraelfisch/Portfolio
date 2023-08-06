
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../../../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = dispatcher.cpp dispatcherTest.cpp

# list of directories containing header files
#PROJ_INC_DIR = $(ROOT_DIR)/cdinclude
PROJ_INC_DIR = ../../include	../../../framework/include

# the executable file
PROJ_OUT = dispatcherTest.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS = -std=c++11

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = request_host.obj thread_pool.obj semaphore.obj select.obj nbd_comm.o transmitter.obj

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../request_host/Makefile ../../../framework/src/function/Makefile ../nbd_comm/Makefile ../../../framework/src/reactor/Makefile ../../../framework/src/thread_pool/Makefile ../../../framework/src/semaphore/Makefile ../transmitter/Makefile  ../../../framework/src/observer/Makefile

include $(ROOT_DIR)/make/Project.mak
