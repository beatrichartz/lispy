CC = cc
INCS =
LIBFLAGS = -ledit -lm $(LIB_OBJECTS)
CFLAGS = -O2 -Os -g -iquote libs -std=c99 -Wpedantic $(INCS) -Wno-missing-field-initializers
LDFLAGS = $(LIBFLAGS)
.DEFAULT_GOAL := lispy
