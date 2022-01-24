CC= clang++
FRAMEWORKS= -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS= -std=c++17
DEBUGCFLAGS= -Wall -Wextra -Wpedantic -D DEBUG -D LOG_POSITIONS -D _LUDWIGPRAMER_
EXTRACFLAGS= -g -v
LIBS= -lglfw3 -lGLEW
OUTPUT= bin/app
WINOUT= bin/win64App.exe
DEPENDENCIES= src/renderingHead/shader.cpp src/renderingHead/texture.cpp  src/renderingHead/objloader.cpp  src/renderingHead/vboindexing.cpp src/renderingHead/matrices.cpp src/renderingHead/vectors.cpp
GAME= src/game/game.cpp src/game/head/controls.cpp src/game/head/model.cpp src/game/head/scene.cpp src/game/head/gun/gun.cpp src/game/head/collider/collider.cpp src/game/head/player.cpp src/game/head/camera.cpp src/game/head/enemy.cpp src/game/head/raycast.cpp
ARGS= src/args.cpp
MAIN= src/main.cpp 
MLIBFOLDER= -L./libs/macos
WLIBFOLDER32= -L./libs/win32
CROSSCOMPILERFLAGSWIN32= -target i686-pc-win32 -fms-compatibility-version=19 -fms-extensions -fdelayed-template-parsing -fexceptions -mthread-model posix -fno-threadsafe-statics -Wno-msvc-not-found -DWIN32 -D_WIN32 -D_MT -D_DLL -Xclang -disable-llvm-verifier -Xclang '--dependent-lib=msvcrt' -Xclang '--dependent-lib=ucrt' -Xclang '--dependent-lib=oldnames' -Xclang '--dependent-lib=vcruntime' -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -U__GNUC__ -U__gnu_linux__ -U__GNUC_MINOR__ -U__GNUC_PATCHLEVEL__ -U__GNUC_STDC_INLINE__ 
INCLUDESWIN32= -I/usr/local/Cellar/llvm/5.0.0/include -I/c/Program\ Files\ (x86)/Microsoft\ Visual\ Studio/2017/Community/VC/Tools/MSVC/14.11.25503/include -I/c/Program\ Files\ (x86)/Windows\ Kits/10/Include/10.0.15063.0/ucrt -I/c/Program\ Files\ (x86)/Windows\ Kits/10/Include/10.0.15063.0/shared -I/c/Program\ Files\ (x86)/Windows\ Kits/10/Include/10.0.15063.0/winrt



macos: $(MAIN) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) -o $(OUTPUT) $(MAIN) $(ARGS) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)

extra: $(MAIN) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) $(EXTRACFLAGS) -o $(OUTPUT) $(MAIN) $(ARGS) $(GAME) $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)


test: macos
	./bin/app
	
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

WIN32:
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) $(EXTRACFLAGS) $(CROSSCOMPILERFLAGSWIN32) $(INCLUDESWIN32) -o $(WIN32OUT) $(MAIN) $(ARGS) $(GAME) $(DEPENDENCIES) $(WLIBFOLDER32) $(LIBS)

