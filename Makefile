CC := gcc

ifdef OS
	MKDIR := -mkdir
	RMDIR := -RMDIR /S /Q
	CFLAGS := -Iinclude -Lbin -Llib -w -Wl,-subsystem,windows -Wall -Wextra -pedantic -std=c99
	LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
	EXE := ./toader.exe
else
	MKDIR := mkdir
	RMDIR := rm -rf
	CFLAGS := -Iinclude -Wall -Wextra -pedantic -std=c99
	LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer
	EXE := ./toader
endif

HEADERS :=
SOURCES := $(wildcard ./src/*.c ./src/entities/*.c)

OBJECTS := $(patsubst ./src/%.c,./obj/%.o,$(SOURCES))

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJECTS) | ./binary
	$(CC) $(LDFLAGS) $^ $(CFLAGS) $(LIBS) -g -o $@

./obj/%.o: ./src/%.c | ./obj
	$(CC) $(CFLAGS) -g -c $< -o $@

./binary:
	$(MKDIR) $@

./obj:
	$(MKDIR) ./obj
	$(MKDIR) ./obj/entities

release: ./src/$(SOURCES)
	$(CC) ./src/$(SOURCES) $(CFLAGS) $(LIBS) -Ofast -o $(EXE)

run: $(EXE)
	./$<

clean:
	$(RMDIR) ./obj ./binary

runRelease: release
	$(EXE)
