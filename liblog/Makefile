SRCS		:= logd_write.c fake_log_device.c
OBJS		:= $(subst .c,.o,$(SRCS))
TGT			:= liblog.a
CFLAGS	:= -c -m32 -DFAKE_LOG_DEVICE=1 -I../include
LDFLAGS	:=

all: $(TGT)

$(TGT): $(OBJS)
	@ar rcs $@ $(OBJS)

%.o: %.c
	@gcc $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	@rm -f *.a *.o

