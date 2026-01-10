CC = gcc
ARCH = x86_64
LIB_EXTENSION = dylib
CFLAGS = -Wall -Wextra -fPIC -I. #  -arch $(ARCH)
LIBNAME = libcparser.$(LIB_EXTENSION)

SRCS = extern.c \
       Analyzer/Analyzer.c \
       Remark/Remark.c \
       Modules/DummyModule.c

OBJS = $(SRCS:.c=.o)

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIBNAME)