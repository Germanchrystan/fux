CC = gcc
CFLAGS = -Wall -Wextra -fPIC -I.
LIB_EXTENSION = dylib
LIB_NAME = libcparser
LIBRARY = $(LIB_NAME).$(LIB_EXTENSION)

SRCS = extern.c \
		analyzer/analyzer.c \
		modules/melodic_module.c \
		remark/remark.c \
		notation/notation.c \
		utils/utils.c \
	modules/counterpoint/module.c \
	modules/counterpoint/species/first.c

OBJS = $(SRCS:.c=.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIBRARY)


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(COMPILER_CALL) -c $< -o $@
