
libs := libusb-1.0
bin := req retr reset runseq

CC ?= cc
CFLAGS := -Wall -ggdb $(shell pkg-config --cflags $(libs))
LDFLAGS := $(shell pkg-config --libs $(libs)) -lreadline

all: ${bin}

%: %.c
	${CC} ${CFLAGS} ${LDFLAGS} $< -o $@

clean:
	rm -vf ${bin}

