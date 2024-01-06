SRCDIR = src
HEADDIR = include
LIBDIR = ./src

DEBUGFLAGS = -W -Wall -Wextra -Wvla -fsanitize=address -g
DEPENDENCIES = $(SRCDIR)/http.c $(SRCDIR)/string_utils.c
build:
	gcc $(SRCDIR)/server.c -o ./bin/server  $(DEPENDENCIES) $(FLAGS)

run:
	./bin/server

clean:
	rm ./bin/server

debug:
	gcc $(SRCDIR)/server.c -o ./bin/server $(DEPENDENCIES) $(DEBUGFLAGS) $(FLAGS)

all:
	make build
	make run