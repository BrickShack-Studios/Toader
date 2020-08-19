CC := gcc
CFLAGS := -g -std=c99
LIBS := -lSDL2

HEADERS :=
SOURCES := main.c

OBJECTS := $(SRCS:.c=.o)

EXE := toader

build: ./src/$(SOURCES)
	$(CC) ./src/$(SOURCES) $(CFLAGS) $(LIBS) -o $(EXE)

run: build
	./$(EXE)
