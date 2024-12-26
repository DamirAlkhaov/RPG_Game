LIBFLAGS= -l:libcsfml-graphics.a -l:libcsfml-window.a -l:libcsfml-system.a
CXXFLAGS = -std=c++11
INCLUDE = -Iinclude/ 
SOURCE = src/main.c src/GameWindow.c src/GameLoop.c src/GameMap.c src/GameTile.c src/Player.c src/Bullet.c

all: $(SOURCE)
	gcc $(INCLUDE) $(SOURCE) -o bin/game.exe -Linclude/ $(LIBFLAGS)

play:
	bin/game.exe

clean:
	rm bin/game.exe