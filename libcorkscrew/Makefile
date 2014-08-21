generic_src_files	:=	\
	backtrace.c \
	backtrace-helper.c \
	demangle.c \
	map_info.c \
	ptrace.c \
	symbol_table.c

x86_src_files := \
	arch-x86/backtrace-x86.c \
	arch-x86/ptrace-x86.c

SRCS		:= $(generic_src_files) $(x86_src_files)
OBJS		:= $(subst .c,.o,$(SRCS))
CFLAGS	:= -m32 -c -Wall -DCORKSCREW_HAVE_ARCH -std=gnu99
CFLAGS	+= -I../include -c
LDFLAGS := -L../gcc-demangle -L../liblog -Llibcutils
LDFLAGS	+= -lgccdemangle -llog -lcutils

all: $(OBJS)
	ar rcs libcorkscrew.a $(OBJS)

%.o: %.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o *.a
