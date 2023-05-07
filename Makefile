DIST = if [ ! -d dist ]; then mkdir dist; fi
CC = g++
CFLAGS = -std=c++17 `sdl2-config --cflags --libs`

all: dist/main
	./dist/main &> /dev/null

dist/Ball.o: src/Ball.cpp
	$(DIST); $(CC) -c -o dist/Ball.o src/Ball.cpp $(CFLAGS)

dist/Brick.o: src/Brick.cpp
	$(DIST); $(CC) -c -o dist/Brick.o src/Brick.cpp $(CFLAGS)

dist/CollisionObject.o: src/CollisionObject.cpp
	$(DIST); $(CC) -c -o dist/CollisionObject.o src/CollisionObject.cpp $(CFLAGS)

dist/GameObject.o: src/GameObject.cpp
	$(DIST); $(CC) -c -o dist/GameObject.o src/GameObject.cpp $(CFLAGS)

dist/Message.o: src/Message.cpp
	$(DIST); $(CC) -c -o dist/Message.o src/Message.cpp $(CFLAGS)

dist/Platform.o: src/Platform.cpp
	$(DIST); $(CC) -c -o dist/Platform.o src/Platform.cpp $(CFLAGS)

dist/ReflectiveObject.o: src/ReflectiveObject.cpp
	$(DIST); $(CC) -c -o dist/ReflectiveObject.o src/ReflectiveObject.cpp $(CFLAGS)

dist/utils.o: src/utils.cpp
	$(DIST); $(CC) -c -o dist/utils.o src/utils.cpp $(CFLAGS)

dist/main.o: src/main.cpp
	$(DIST); $(CC) -c -o dist/main.o src/main.cpp $(CFLAGS)

dist/main: dist/main.o dist/utils.o dist/Ball.o dist/Brick.o dist/CollisionObject.o dist/GameObject.o dist/Message.o dist/Platform.o dist/ReflectiveObject.o
	$(DIST); $(CC) -o dist/main dist/main.o dist/utils.o dist/Ball.o dist/Brick.o dist/CollisionObject.o dist/GameObject.o dist/Message.o dist/Platform.o dist/ReflectiveObject.o $(CFLAGS)

clean:
	rm -rf dist && mkdir dist
