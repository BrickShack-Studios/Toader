CC := gcc

ifdef OS
	CFLAGS := -Iinclude -Lbin -Llib -w -Wl,-subsystem,windows -Wall -Wextra -std=c99
	LIBS := -lmingw32 -lSDL2main -lSDL2
	EXE := toader.exe
else
	CFLAGS := -g -Wall -Wextra -std=c99
	LIBS := -lSDL2
	EXE := toader
endif

HEADERS :=
SOURCES := main.c

OBJECTS := $(SRCS:.c=.o)

build: ./src/$(SOURCES)
	$(CC) ./src/$(SOURCES) $(CFLAGS) $(LIBS) -g -o $(EXE)

release: ./src/$(SOURCES)
	$(CC) ./src/$(SOURCES) $(CFLAGS) $(LIBS) -Ofast -o $(EXE)

run: build
	./$(EXE)

runRelease: release
	./$(EXE)
