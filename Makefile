CC = gcc
CFLAGS = -Wall -Wextra -fPIC -I.
LIB_EXTENSION = dylib
LIB_NAME = libcparser
LIBRARY = $(LIB_NAME).$(LIB_EXTENSION)

SRCS = extern.c \
       Analyzer/Analyzer.c \
       Remark/Remark.c \
       Modules/DummyModule.c

OBJS = $(SRCS:.c=.o)

all: $(LIBRARYLIBRARY)

$(LIBNAME): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIBRARY)


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(COMPILER_CALL) -c $< -o $@
