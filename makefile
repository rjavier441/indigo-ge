# PROJECT:         Indigo
# Author:          R. Javier
# File:            makefile
# Created:         March 23, 2019
# Last Modified:   March 23, 2019
# Details:
#                  This file contains definitions for error codes that pertain
#                  to errors or warnings in the game engine
# Dependencies:
#                  n/a

# Relevant Directories
DIR_CLASS = ./lib/class
DIR_SRC = ./src
DIR_TEMP = ./temp
DIR_OBJ = $(DIR_TEMP)/obj

# Compilation Options
CC = g++
CFLAGS = -I$(DIR_CLASS) -I$(DIR_OBJ) -I$(DIR_SRC)
REQS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
EXENAME = game.EXENAME

# BEGIN Make Rules
# The default; runs "game" make rules first, then unsets the compilation
# directories as cleanup
compile_epilogue: game
	@echo "[ Cleaning Up ]"
	@rm -fr $(DIR_OBJ)
	@rm -fr $(DIR_TEMP)
	@echo "Done"

# Compiles the game
# game: compile_prologue interface class
game: compile_prologue
	@echo "[ Compiling Game ]"

	@# 
	
	@echo "Done"

# Sets up the compile environment (i.e. relevant directories for compilation)
compile_prologue:
	@echo "[ Initializing Compile Environment ]"
	@mkdir -p $(DIR_TEMP)
	@mkdir -p $(DIR_OBJ)
	@echo "Done"

# Manually cleans up the compile environment
clean:
	@rm -fr $(DIR_OBJ)
# END Make Rules

# EOF makefile