SDL2_PATH := $(PWD)/SDL2-2.0.14/x86_64-w64-mingw32
# libs contain linked libraries, -L defines where to look for the things after -l
LIBS = -L$(SDL2_PATH)/lib -lmingw32 -lSDL2main -lSDL2 
# -I defines where to look for the headers
INCLUDE = -I$(SDL2_PATH)/include/SDL2
# -c says, hey man don't link these files, since this will lead to multiple definitions if we link again in the next step
all:
	g++ -c -o run_game.o demonstration.cpp 
	g++ -o run_game run_game.o $(INCLUDE) $(LIBS)
# g++ -o run_game main.cpp $(INCLUDE) $(LIBS) # the actual line, 

clean:
	rm *.o 
	rm *.exe
