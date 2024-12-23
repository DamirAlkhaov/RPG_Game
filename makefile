LIBFLAGS= -l:libcsfml-graphics.a -l:libcsfml-window.a -l:libcsfml-system.a
CXXFLAGS = -std=c++11

all: main.c 
	gcc -Iinclude/ main.c -o bin/main.exe -Linclude/ $(LIBFLAGS)

play:
	bin/main.exe

clean:
	rm bin/main.exe