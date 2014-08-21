commonSources := \
  hashmap.c \
  atomic.c \
  native_handle.c \
  socket_inaddr_any_server.c \
  socket_local_client.c \
  socket_local_server.c \
  socket_loopback_client.c \
  socket_loopback_server.c \
  socket_network_client.c \
  sockets.c \
  config_utils.c \
  cpu_info.c \
  load_file.c \
  list.c \
  open_memstream.c \
  strdup16to8.c \
  strdup8to16.c \
  record_stream.c \
  process_name.c \
  threads.c \
  sched_policy.c \
  iosched_policy.c \
  str_parms.c

commonHostSources := \
        ashmem-host.c

SRCS		:= $(commonSources) $(commonHostSources) dlmalloc_stubs.c
OBJS		:= $(subst .c,.o,$(SRCS))
TGT			:= libcutils.a
CFLAGS	:= -c -m32 -I../include -DANDROID_SMP=0 -DHAVE_PTHREADS
LDFLAGS	:=

all: $(TGT)

$(TGT): $(OBJS)
	@ar rcs $@ $(OBJS)

%.o: %.c
	@gcc $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	@rm -f *.a *.o

