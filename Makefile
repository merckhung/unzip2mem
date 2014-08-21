# LLVM
OS :=  $(shell uname -s)

ifeq ($(OS), Darwin)
SWDIR	:=  /Users/merck/Sw
else
SWDIR	:=  /home/merck/Sw
endif

LLVMBIN		:=  $(SWDIR)/llvm
LLVMBPATH	:=  $(LLVMBIN)/bin/
LLVMCFG		:=  $(LLVMBPATH)llvm-config

# Compiler
CROSS_COMPILE :=
AS       :=	$(LLVMBPATH)clang
AR       :=	$(CROSS_COMPILE)ar
CC       :=	$(LLVMBPATH)clang
CPP      :=	$(LLVMBPATH)clang++
LD       :=	$(CROSS_COMPILE)ld
NM       :=	$(CROSS_COMPILE)nm
OBJCOPY  :=	$(CROSS_COMPILE)objcopy
OBJDUMP  :=	$(CROSS_COMPILE)objdump
RANLIB   :=	$(CROSS_COMPILE)ranlib
READELF  :=	$(CROSS_COMPILE)readelf
SIZE     :=	$(CROSS_COMPILE)size
STRINGS  :=	$(CROSS_COMPILE)strings
STRIP    :=	$(CROSS_COMPILE)strip
CPPLINT	 :=	tools/cpplint.py

# Common flags
CPPFLAGS	:=	-m32 -Iinclude -Wall -g3
#CPPFLAGS	+=	-std=c++11
ifeq ($(OS), Darwin)
CPPFLAGS	+=	-I/usr/include/c++/4.2.1
endif

LDFLAGS		:=	-lz -lcutils -Llibcutils -Llibcorkscrew -lcorkscrew -Lliblog -llog
ifeq ($(OS), Darwin)
LDFLAGS		+=	-stdlib=libstdc++ -lc++
endif

# Modules
MODULES	:= unzip2mem
SRCS		:= fd_file.cc zip_archive.cc os_linux.cc stringpiece.cc main.cc
SRCS		+= stringprintf.cc mem_map.cc

.PHONY:	gcc-demangle liblog libcutils libcorkscrew

# Rules
all: gcc-demangle liblog libcutils libcorkscrew $(MODULES)

unzip2mem:
	@$(CPP) -o $@ $(CPPFLAGS) $(SRCS) $(LDFLAGS)

gcc-demangle:
	@make -C $@

liblog:
	@make -C $@

libcutils:
	@make -C $@

libcorkscrew:
	@make -C $@

%.o: %.cpp
	@$(CPP) -o $@ $< $(CPPFLAGS) -c

clean:
	@make -C gcc-demangle clean
	@make -C liblog clean
	@make -C libcutils clean
	@make -C libcorkscrew clean
	@$(RM) -rf $(MODULES) *.dSYM
	$(shell find ./ -name "*.o" -exec rm -f {} \;)

