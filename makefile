LIBFLAGS= -l:libcsfml-graphics.a -l:libcsfml-window.a -l:libcsfml-system.a
CXXFLAGS = -std=c++11
INCLUDE = -Iinclude/ 
SOURCE = src/main.c src/GameWindow.c src/GameLoop.c src/GameMap.c src/Player.c src/Bullet.c src/UI.c src/crate.c src/Collision.c src/perlin.c

all: $(SOURCE)
	gcc $(INCLUDE) $(SOURCE) -o bin/game.exe -Linclude/ $(LIBFLAGS)
	strip bin/game.exe

clean:
	rm bin/game.exe