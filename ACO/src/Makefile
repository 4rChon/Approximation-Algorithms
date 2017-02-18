#OBJS specifies which files to compile as part of the project
OBJS = adj_matrix.cpp tour_manager.cpp ant_colony.cpp ant.cpp city.cpp tour.cpp world.cpp util.cpp display.cpp main.cpp

#CC specifies which compiler we're using
CC = g++ -std=c++11

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\Users\Ben\workspace\C++\ICS2207\ACO\includes -IC:\MinGW\sdl\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\MinGW\sdl\lib -LC:\Users\Ben\workspace\C++\ICS2207\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Werror -Wall -Wfatal-errors

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = aco

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
    
    
