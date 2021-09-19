CC = clang
CFLAGS = -g -Wall

EXEC = out
SRCS = $(shell find src -type f -name '*.c')
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(EXEC)

$(EXEC): $(filter-out src/tests.o, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: test
test: test.out
test.out: $(filter-out src/main.o, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@rm -f $(OBJS)
	@rm -f $(EXEC)
	@rm -f test.out