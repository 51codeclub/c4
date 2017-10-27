CC     = gcc
CFLAGS = -g

src = $(wildcard *.c)
tartget = $(patsubst %.c, %.o, $(src))

.PHONY:all
all:$(target)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
clean:
	$(RM) $(target)
