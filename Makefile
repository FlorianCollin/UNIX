LDFLAGS=-L.
LDLIBS=-lutils
CFLAGS+=-std=c99 -D_XOPEN_SOURCE=700

libutils.a: utils.o
	ar r $@ $?
clean-lib:
	$(RM) utils.o libutils.a

.PHONY: clean-lib
