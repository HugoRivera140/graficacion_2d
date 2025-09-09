cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g

sdl3_include = deps/sdl3/SDL3-3.2.20/x86_64-w64-mingw32/include
sdl3_lib = deps/sdl3/SDL3-3.2.20/x86_64-w64-mingw32/lib -lSDL3 


source = $(wildcard src/*.c) $(wildcard src/**/*.c)
DVAR =

output = bin/render_cpu

build:
	gcc $(cflags) $(source) -o $(output) -I $(sdl3_include) -L $(sdl3_lib)
	copy "deps\sdl3\SDL3-3.2.20\x86_64-w64-mingw32\bin\SDL3.DLL" "bin\SDL3.dll"
	@echo "\033[1;35mCompilo exitosamente!!\033[0m"
run:
	./$(output)	


