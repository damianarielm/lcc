# Use normal `make` for this Makefile.
#
# Makefile for building user programs to run on top of Nachos.
#
# Several things to be aware of:
#
# Nachos assumes that the location of the program startup routine (the
# location the kernel jumps to when the program initially starts up) is at
# location 0.  This means: `start.o` must be the first `.o` passed to `ld`,
# in order for the routine `Start` to be loaded at location 0.

# If you are cross-compiling, you need to point to the right executables and
# change the flags to ld and the build procedure for as:
#GCC_PREFIX = mips-suse-linux-
GCC_PREFIX = mipsel-linux-gnu-
LDFLAGS    = -T arrangement.ld -N -s
ASFLAGS    = -mips1
CPPFLAGS   = $(INCLUDE_DIRS)

# If you are not cross-compiling:
#GCC_DIR  =
#LDFLAGS  = -N -T 0
#ASFLAGS  =
#CPPFLAGS = -P $(INCLUDE_DIRS)


CC  = $(GCC_PREFIX)gcc
AS  = $(GCC_PREFIX)as
LD  = $(GCC_PREFIX)ld
CPP = $(GCC_PREFIX)cpp

INCLUDE_DIRS = -I../userprog -I../threads
CFLAGS       = -std=c99 -G 0 -c $(INCLUDE_DIRS) -mips1 -mfp32 \
               -nostdlib -nostartfiles -nodefaultlibs -mno-abicalls

PROGRAMS = halt shell tiny_shell matmult sort filetest


.PHONY: all clean

all: $(PROGRAMS)

clean:
	$(RM) *.o *.coff $(PROGRAMS) || true

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) $< >strt.s
	$(AS) $(ASFLAGS) -o $@ strt.s
	$(RM) strt.s


# Las reglas genéricas que siguen sirven para compilar programas simples,
# que consistan en un único archivo fuente. Si se quieren compilar programas
# más complejos, se deben agregar reglas adecuadas.

%.o: %.c
	$(CC) $(CFLAGS) -c $^

$(PROGRAMS): %: %.o start.o
	$(LD) $(LDFLAGS) start.o $*.o -o $*.coff
	../bin/coff2noff $*.coff $@
