CPPFLAGS ?= -O3
CPPFLAGS += --std=c++14 -Iinclude -ltbb


.PHONY: all
all: test sum func_args map
