SRCDIR = src
HEADDIR = include
LIBDIR = ./src

FLAGS = -lSDL2
DEBUGFLAGS = -W -Wall -Wextra -Wvla -fsanitize=address -g
DEPENDENCIES = $(SRCDIR)/byte_reader.c
build:
	gcc $(SRCDIR)/http_server.c -o ./bin/http_server  $(DEPENDENCIES) $(FLAGS)

run:
	./bin/http_server

clean:
	rm ./bin/http_server

debug:
	gcc $(SRCDIR)/http_server.c -o ./bin/wad_reader $(DEPENDENCIES) $(DEBUGFLAGS) $(FLAGS)

all:
	make build
	make run