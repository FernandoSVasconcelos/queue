CC := gcc

CSRC := main.c

$(CSRC):
	$(CC) $@ -o $(patsubst %.c, %.o, $@)


all: $(CSRC)
.PHONY: all $(CSRC)