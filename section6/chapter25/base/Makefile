.PHONY: clean

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: libsssp.a

libsssp.a: ${OBJS}
	ar -r $@ $^

clean:
	rm -rf *.o *.a
