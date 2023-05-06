all: dist/main
	./dist/main

dist/main: src/main.cpp
	rm -rf dist && mkdir dist && g++ -o "dist/main" "src/main.cpp" -std=c++17 `sdl2-config --cflags --libs`

clean:
	rm -rf dist && mkdir dist
