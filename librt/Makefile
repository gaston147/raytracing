LIB = rt.a
SRC = rt.c
OBJ = $(SRC:.c=.o)
CFLAGS = -W -Wall -Wextra

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJ)
	ar -q $@ $^

%.o: %.c
	gcc -o $@ -c $^ $(CFLAGS)

clean:
	-rm -f $(LIB)
	-rm -f $(OBJ)

# vim: noexpandtab
