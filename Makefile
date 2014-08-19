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
CPPFLAGS	:=	-Iinclude -Wall -g3
#CPPFLAGS	+=	-std=c++11
ifeq ($(OS), Darwin)
CPPFLAGS	+=	-I/usr/include/c++/4.2.1
endif

LDFLAGS		:=	-lz
ifeq ($(OS), Darwin)
LDFLAGS		+=	-stdlib=libstdc++ -lc++
endif

# Modules
MODULES	:= unzip2mem
SRCS		:= fd_file.cc zip_archive.cc os_linux.cc stringpiece.cc main.cc

# Rules
all: $(MODULES)

unzip2mem:
	@$(CPP) -o $@ $(CPPFLAGS) $(LDFLAGS) $(SRCS)

%.o: %.cpp
	@$(CPP) -o $@ $< $(CPPFLAGS) -c

clean:
	@$(RM) -rf $(MODULES) *.dSYM
	$(shell find ./ -name "*.o" -exec rm -f {} \;)

