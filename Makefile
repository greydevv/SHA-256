CC = clang
CFLAGS = -g -Wall

EXEC = out
SRCS = $(shell find src -type f -name '*.c')
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	@rm -f $(OBJS)
	@rm -f $(EXEC)