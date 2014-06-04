
libs := libusb-1.0

CC ?= cc
CFLAGS := -Wall -ggdb $(shell pkg-config --cflags $(libs))
LDFLAGS := $(shell pkg-config --libs $(libs))

all: req retr reset

%: %.c
	${CC} ${CFLAGS} ${LDFLAGS} $< -o $@

clean:
	rm -vf req retr reset

