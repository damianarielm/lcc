# NOTE: this is a GNU Makefile.  You must use GNU Make; other `make`
# implementations may not work.
#
# Makefile for the virtual memory assignment.
# Defines set up assuming the virtual memory assignment is done before  the
# file system assignment. If not, use the “filesystem first” defines below.
#
# Also, if you want to simplify the translation so it assumes only linear
# page tables, do not define `USE_TLB`.
#
# Copyright (c) 1992      The Regents of the University of California.
#               2016-2017 Docentes de la Universidad Nacional de Rosario.
# All rights reserved.  See `copyright.h` for copyright notice and
# limitation of liability and disclaimer of warranty provisions.

DEFINES      = -DUSER_PROGRAM  -DFILESYS_NEEDED -DFILESYS_STUB -DVMEM \
               -DUSE_TLB -DDFS_TICKS_FIX
INCLUDE_DIRS = -I.. -I../filesys -I../bin -I../userprog -I../threads \
               -I../machine
HDR_FILES    = $(THREAD_HDR) $(USERPROG_HDR) $(VMEM_HDR)
SRC_FILES    = $(THREAD_SRC) $(USERPROG_SRC) $(VMEM_SRC)
OBJ_FILES    = $(THREAD_OBJ) $(USERPROG_OBJ) $(VMEM_OBJ)

# If filesystem is done first!
#DEFINES      = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS -DVMEM -DUSE_TLB
#INCLUDE_DIRS = -I../vm -I../bin -I../filesys -I../userprog -I../threads \
#               -I../machine
#HFILES       = $(THREAD_HDR) $(USERPROG_HDR) $(FILESYS_HDR) $(VMEM_HDR)
#CFILES       = $(THREAD_SRC) $(USERPROG_SRC) $(FILESYS_SRC) $(VMEM_SRC)
#C_OFILES     = $(THREAD_OBJ) $(USERPROG_OBJ) $(FILESYS_OBJ) $(VMEM_OBJ)

include ../Makefile.common
include ../Makefile.env
-include Makefile.depends
