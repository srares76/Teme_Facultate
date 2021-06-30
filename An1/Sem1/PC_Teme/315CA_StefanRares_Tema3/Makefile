# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# pickp all sources
SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)

# define targets
TARGETS=image_editor

build: $(OBJS) $(TARGETS)

image_editor:
	$(CC) $(CFLAGS) *.c -o $(TARGETS) -lm

pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJS)

.PHONY: pack clean
