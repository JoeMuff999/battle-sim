SDL2_PATH := $(PWD)/SDL2-2.0.14/x86_64-w64-mingw32
# libs contain linked libraries, -L defines where to look for the things after -l
LIBS = -L$(SDL2_PATH)/lib -lmingw32 -lSDL2main -lSDL2 
# -I defines where to look for the headers
# -c says, hey man don't link these files, since this will lead to multiple definitions if we link again in the next step
all:
	g++ -o run_game main.cpp -I$(SDL2_PATH)/include/SDL2 $(LIBS)

clean:
	rm run_game.exe
