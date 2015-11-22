CC = cc
INCS =
LIBFLAGS = -ledit -lm $(LIB_OBJECTS)
CFLAGS = -O -g -iquote libs -std=c99 -pedantic -Wall $(INCS)
LDFLAGS = $(LIBFLAGS)
.DEFAULT_GOAL := lispy
