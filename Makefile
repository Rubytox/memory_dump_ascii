CC=gcc
CFLAGS=-Wall -Werror -pedantic
LDFLAGS=
EXEC=memory_dump_ascii

all: $(EXEC)

$(EXEC): $(EXEC).c
	gcc $(CFLAGS) $(LDFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXEC)
