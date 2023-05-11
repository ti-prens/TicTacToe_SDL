CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -pg -I.\include\ -I. -I.\include\SDL2
LDFLAGS=-L.\lib -L. -lmingw32 -lSDL2main -lSDL2 -lSDL2_image  -lSDL2_mixer -lSDL2_ttf
OBJFILES= renderer.o game_model.o tictactoe.o
TARGET=ttt
	
#ttt: tictactoe.c
#	$(CC) $(CFLAGS) -o ttt  tictactoe.c $(shell sdl2-config --cflags --libs)

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

# clean:
#	rm $(OBJFILES) $(TARGET)

clean:
	pwsh -Command {rm ./*.o}