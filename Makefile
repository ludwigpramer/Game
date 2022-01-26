CC= clang++
FRAMEWORKS= -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS= -std=c++17
DEBUGCFLAGS= -Wall -Wextra -Wpedantic -D DEBUG -D LOG_POSITIONS -D _LUDWIGPRAMER_
EXTRACFLAGS= -g -v
LIBS= -lglfw3 -lGLEW
OUTPUT= bin/app
DEPENDENCIES= src/renderingHead/shader.cpp src/renderingHead/texture.cpp  src/renderingHead/objloader.cpp  src/renderingHead/vboindexing.cpp src/renderingHead/matrices.cpp src/renderingHead/vectors.cpp
GAME= src/game/game.cpp src/game/head/controls.cpp src/game/head/model.cpp src/game/head/scene.cpp src/game/head/gun/gun.cpp src/game/head/collider/collider.cpp src/game/head/player.cpp src/game/head/camera.cpp src/game/head/enemy.cpp src/game/head/raycast.cpp
ARGS= src/args.cpp
MAIN= src/main.cpp 
MLIBFOLDER= -L./libs/macos



macos: $(MAIN) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) -o $(OUTPUT) $(MAIN) $(ARGS) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)

extra: $(MAIN) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) $(EXTRACFLAGS) -o $(OUTPUT) $(MAIN) $(ARGS) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)


test: macos run
	
extratest: extra
	./bin/app

cleanup:
	rm -rf bin/app
	rm -rf /log/log.LOG

run:
	./bin/app

testingFiles:
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) -o bin/test test/Test.cpp $(ARGS) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)

runTestingFiles:
	./bin/test

testTestingFiles: testingFiles runTestingFiles



WIN32CC= x86_64-w64-mingw32-g++
WIN32CFLAGS= -D _LUDWIGPRAMER_ -D WIN
WIN32LIBFOLDER= -L./libs/win32
WIN32OUT= bin/win32App.exe
WIN32LIBS= -lGLEW -lglfw3
WIN32INCLUDE= -I include

win32: $(MAIN) $(DEPENDENCIES)
	$(WIN32CC) $(WIN32CFLAGS) -o $(WIN32OUT) $(WIN32INCLUDE) $(MAIN) $(ARGS) $(GAME) $(DEPENDENCIES) $(WIN32LIBFOLDER) $(WIN32LIBS)
