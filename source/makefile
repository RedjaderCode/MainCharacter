
OBJS = main.cpp
CC = g++

INCLUDE_PATHS = -IC:\mingw_SDL_lib\include\SDL2
LIBRARY_PATHS = -LC:\mingw_SDL_lib\lib

COMPILER_FLAGS = -w
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -fstack-usage

OBJ_NAME = MainCharacter

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

