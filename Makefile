CC= clang++
FRAMEWORKS= -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS= -std=c++17
DEBUGCFLAGS= -Wall -Wextra -Wpedantic -D DEBUG -D LOG_POSITIONS
EXTRACFLAGS= -g -v
LIBS= -lglfw3 -lGLEW
OUTPUT= bin/app
WINOUT= bin/win64App.exe
DEPENDENCIES= src/renderingHead/shader.cpp src/renderingHead/texture.cpp  src/renderingHead/objloader.cpp  src/renderingHead/vboindexing.cpp src/renderingHead/matrices.cpp src/renderingHead/vectors.cpp
GAME= src/game/game.cpp src/game/head/controls.cpp src/game/head/model.cpp src/game/head/scene.cpp src/game/head/gun/gun.cpp src/game/head/collider/collider.cpp src/game/head/player.cpp src/game/head/camera.cpp src/game/head/enemy.cpp src/game/head/raycast.cpp
MAIN= src/main.cpp
MLIBFOLDER= -L./libs/macos
wLIBFOLDER= -L./libs/win32




macos: $(MAIN) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) -o $(OUTPUT) $(MAIN) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)

extra: $(MAIN) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) $(EXTRACFLAGS) -o $(OUTPUT) $(MAIN) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)


test: macos
	./bin/app
	
extratest: extra
	./bin/app

cleanup:
	rm -rf bin/app
	rm -rf /log/log.LOG

run:
	./bin/app


