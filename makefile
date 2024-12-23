LIBFLAGS= -l:libcsfml-graphics.a -l:libcsfml-window.a -l:libcsfml-system.a
CXXFLAGS = -std=c++11
INCLUDE = -Iinclude/
SOURCE = src/main.c

all: $(SOURCE)
	gcc $(INCLUDE) $(SOURCE) -o bin/main.exe -Linclude/ $(LIBFLAGS)

play:
	bin/main.exe

clean:
	rm bin/main.exe