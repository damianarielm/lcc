# Copyright (c) 1992      The Regents of the University of California.
#               2016-2017 Docentes de la Universidad Nacional de Rosario.
# All rights reserved.  See `copyright.h` for copyright notice and
# limitation of liability and disclaimer of warranty provisions.

MAKE = make
LPR  = lpr
SH   = bash

.PHONY: all clean test print

all:
	$(MAKE) -C threads depend
	$(MAKE) -C threads all
	$(MAKE) -C userprog depend
	$(MAKE) -C userprog all
	$(MAKE) -C vmem depend
	$(MAKE) -C vmem all
	$(MAKE) -C filesys depend
	$(MAKE) -C filesys all
	$(MAKE) -C network depend
	$(MAKE) -C network all
	$(MAKE) -C bin
	$(MAKE) -C userland

# Do not delete executables in `userland` in case there is no cross-compiler.
clean:
	$(MAKE) -C threads clean
	$(MAKE) -C userprog clean
	$(MAKE) -C vmem clean
	$(MAKE) -C filesys clean
	$(MAKE) -C network clean
	$(MAKE) -C bin clean
	$(MAKE) -C userland clean

test:
	@./tests/check.sh

print:
	$(SH) -c '$(LPR) Makefile* */Makefile                              \
	                 threads/*.h threads/*.hh threads/*.cc threads/*.s \
	                 userprog/*.h userprog/*.hh userprog/*.cc          \
	                 filesys/*.hh filesys/*.cc                         \
	                 network/*.hh network/*.cc                         \
	                 machine/*.hh machine/*.cc                         \
	                 bin/noff.h bin/coff.h bin/coff2noff.c             \
	                 userland/*.h userland/*.c userland/*.s'
