# Program
EXECUTABLE	:= Main

# Compiler and Linker
CC	:= g++
LD	:= g++

# The Target Binary Program
TARGET	:= main

# The Directories, Source, Includes, Objects, Binary and Resources
MODULES	:= components entities gui resources states tiles
BIN		:= bin
SRC_DIR		:= $(addprefix src/,$(MODULES))
INCLUDE_DIR		:= $(addprefix include/,$(MODULES))
BUILD_DIR		:= $(addprefix build/,$(MODULES))
LIB_DIR		:= $(addprefix lib/,$(MODULES))

SRC		:= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ		:= $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDE		:= $(addprefix -I , $(INCLUDE_DIR))
LIB		::= $(addprefix -L , $(LIB_DIR))

# Flags, Libraries and Includes
CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb
LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system

vpath %.cpp $(SRC_DIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
# Default Make
all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

bear: clean all
	echo "Generated compile_commands.json"

$(BIN)/$(EXECUTABLE): src/*.cpp $(SRC)
	$(CXX) $(CXX_FLAGS) -I include $(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
