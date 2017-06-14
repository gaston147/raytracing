EXE = rt_ui
SRC = main.c
OBJ = $(SRC:.c=.o)

LIBRT = librt
LIBRT_LIB = $(LIBRT)/rt.a

LIB = $(LIBRT_LIB)

CFLAGS = -W -Wall -Wextra
LDFLAGS = $(LIB) -lSDL2

.PHONY: all clean $(LIBRT_LIB)

all: $(EXE)

# The last dependency run a command which checks if `make' should be run on
# `librt'; if the exit status of `make -q' isn't 0, then `$(LIBRT_LIB)' will be
# added to the dependencies, therefore `make' will be run.
$(EXE): $(OBJ) $(shell $(MAKE) -q -C $(LIBRT) || echo $(LIBRT_LIB))
	gcc -o $@ $(OBJ) $(LDFLAGS)

$(LIBRT_LIB):
	$(MAKE) -C $(LIBRT)

%.o: %.c
	gcc -o $@ -c $^ $(CFLAGS)

clean:
	@make -C $(LIBRT) clean
	-rm -f $(EXE)
	-rm -f $(OBJ)

# vim: noexpandtab
