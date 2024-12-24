LIBFLAGS= -l:libcsfml-graphics.a -l:libcsfml-window.a -l:libcsfml-system.a
CXXFLAGS = -std=c++11
INCLUDE = -Iinclude/ -Isrc/
SOURCE = src/main.c src/GameWindow.c src/GameLoop.c

all: $(SOURCE)
	gcc $(INCLUDE) $(SOURCE) -o bin/main.exe -Linclude/ $(LIBFLAGS)

play:
	bin/main.exe

clean:
	rm bin/main.exe