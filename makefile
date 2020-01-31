CC_CPP = gcc
C_FLAGS = -c -Wall -g -D _POSIX_C_SOURCE=200809L
LD_FLAGS = -lglut -lGLU -lGL -lstdc++
SRC_FILES = main.cpp game.cpp shape.cpp board.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
OUTPUT = FruitTetris

$(OUTPUT): $(SRC_FILES) 

	$(CC_CPP) $(C_FLAGS) $(SRC_FILES)

	$(CC_CPP) $(OBJ_FILES) $(LD_FLAGS) -o $@

clean: 
	-rm -f $(OBJ_FILES) $(OUTPUT)