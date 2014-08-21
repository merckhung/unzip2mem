CFLAGS	:= -m32 -DFAKE_LOG_DEVICE=1 -I../include
LDFLAGS	:= -lpthread -c

all:
	gcc $(CFLAGS) $(LDFLAGS) -o liblog.o logd_write.c
	gcc $(CFLAGS) $(LDFLAGS) -o fake_log_device.o fake_log_device.c
	ar rcs liblog.a liblog.o fake_log_device.o

clean:
	rm -f *.a *.o

