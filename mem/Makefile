TARGET = memdump
OBJS = memdump.o NKLIB.o

BUILD_PRX=1

#USE_PSPSDK_LIBC=1
#USE_PSPSDK_LIBS=1
USE_KERNEL_LIBC=1
USE_KERNEL_LIBS=1

PRX_EXPORTS=exports.exp

INCDIR = 
CFLAGS = -Os -G0 -Wall -fno-strict-aliasing -fno-builtin-printf
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = -mno-crt0 -nostartfiles
LIBS =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
