nat_dir = ../nat/
natio_dir = ../natio/
CC = clang
CFLAGS = -std=c++2b \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -I$(nat_dir) -I$(natio_dir) -x c++

vpath %.c $(nat_dir):$(natio_dir)
vpath %.h $(nat_dir):$(natio_dir)
objects = natio_test.o nat.o natio.o
executable = natio_test
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

natio_test.o: natio_test.c nat.h natio.h
nat.o: nat.c nat.h
natio.o: natio.c natio.h nat.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
