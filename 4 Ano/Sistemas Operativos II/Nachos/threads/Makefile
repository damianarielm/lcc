# NOTE: this is a GNU Makefile.  You must use GNU Make; other `make`
# implementations may not work.
#
# Makefile for the threads assignment.  The threads assignment must be done
# first!
#
# Copyright (c) 1992      The Regents of the University of California.
#               2016-2017 Docentes de la Universidad Nacional de Rosario.
# All rights reserved.  See `copyright.h` for copyright notice and
# limitation of liability and disclaimer of warranty provisions.


DEFINES      = -DTHREADS -DDFS_TICKS_FIX
INCLUDE_DIRS = -I.. -I../machine
HDR_FILES    = $(THREAD_HDR)
SRC_FILES    = $(THREAD_SRC)
OBJ_FILES    = $(THREAD_OBJ)

include ../Makefile.common
include ../Makefile.env
-include Makefile.depends
