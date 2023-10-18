SDL2_PATH := $(PWD)/SDL2-2.0.14/x86_64-w64-mingw32
# libs contain linked libraries, -L defines where to look for the things after -l
LIBS = -L$(SDL2_PATH)/lib -lmingw32 -lSDL2main -lSDL2 
# -I defines where to look for the headers
INCLUDE = -I$(SDL2_PATH)/include/SDL2
# src path
SRC_PATH = $(PWD)/src
# src files
SRC_LINUX = $(SRC_PATH)/*.cpp $(SRC_PATH)/*.hpp
# SRC_WINDOWS = $(SRC_PATH)/main.cpp $(SRC_PATH)/agent.hpp $(SRC_PATH)/controllable.hpp $(SRC_PATH)/drawable.hpp $(SRC_PATH)/game.hpp $(SRC_PATH)/graphics.hpp $(SRC_PATH)/InputManager.hpp $(SRC_PATH)/InputManager.cpp $(SRC_PATH)/point.hpp $(SRC_PATH)/time.hpp $(SRC_PATH)/agent.cpp $(SRC_PATH)/graphics.cpp
SRC_CPP = $(wildcard $(SRC_PATH)/*.cpp)
SRC_HPP = $(wildcard $(SRC_PATH)/*.hpp)
SRC_WINDOWS = $(SRC_HPP) $(SRC_CPP)
# -c says, hey man don't link these files, since this will lead to multiple definitions if we link again in the next step

all:
	g++ -Wall -o run_game $(SRC_WINDOWS) $(INCLUDE) $(LIBS)

report:
	g++ -o run_game $(SRC_WINDOWS) $(INCLUDE) $(LIBS) -v -ftime-report

linux:
	g++ -o run_game $(SRC_LINUX) $(INCLUDE) -L$(SDL2_PATH)/lib~ -lSDL2main -lSDL2 

clean:
	rm run_game.exe

# rm --help

# rm *.o 
