SRCS		:= cp-demangle.c
OBJS		:= $(subst .c,.o,$(SRCS))
TGT			:= libgccdemangle.a
CFLAGS	:= -m32 -c -DHAVE_STRING_H -DHAVE_STDLIB_H -DIN_GLIBCPP_V3
LDFLAGS	:= 

all: $(TGT)

$(TGT): $(OBJS)
	@ar rcs $@ $(OBJS)

%.o: %.c
	@gcc $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	@rm -f *.a
	
