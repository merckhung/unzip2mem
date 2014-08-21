CFLAGS	:= -m32 -c -DHAVE_STRING_H -DHAVE_STDLIB_H -DIN_GLIBCPP_V3
LDFLAGS	:= 

all:
	@gcc $(CFLAGS) $(LDFLAGS) -o libgccdemangle.o cp-demangle.c
	ar rcs libgccdemangle.a libgccdemangle.o

clean:
	@rm -f *.a
	
