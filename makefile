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
DIR_IFACE = ./lib/interface
DIR_MODULE = ./lib/modules
DIR_SRC = ./src
DIR_TEST = ./test
DIR_TEMP = ./temp
DIR_OBJ = $(DIR_TEMP)/obj

# Compilation Options
CC = g++
CFLAGS = -I$(DIR_CLASS) -I$(DIR_OBJ) -I$(DIR_SRC) -I$(DIR_IFACE)
REQS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
EXENAME = game.exe
TESTNAME = test.exe

# File Sets
MODULE_FILES = $(shell find $(DIR_MODULE) -regex '.*.\(cpp\|hpp\|h\)')
SRC_FILES = $(shell find $(DIR_SRC) -regex '.*.\(cpp\|hpp\|h\)')
IFACE_FILES = $(shell find $(DIR_IFACE) -regex '.*.\(cpp\|hpp\|h\)')
CLASS_FILES = $(shell find $(DIR_CLASS) -regex '.*.\(cpp\|hpp\|h\)')

# BEGIN Make Rules
# The default; runs "game" make rules first, then unsets the compilation
# directories as cleanup
compile_epilogue:
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

# Compiles the unit tests
compile_tests:
	@echo "[ Gathering Source Files ]"

	# DEBUG
	@echo "module files: $(MODULE_FILES)"
	@echo "interface files: $(IFACE_FILES)"
	@echo "class files: $(CLASS_FILES)"

	@# @echo "[ Compiling Tests ]"
	@# $(CC) -c -Wall $(CFLAGS)
	@# @echo "Done"

# Sets up the compile environment (i.e. relevant directories for compilation)
compile_prologue:
	@echo "[ Initializing Compile Environment ]"
	@mkdir -p $(DIR_TEMP)
	@mkdir -p $(DIR_OBJ)
	@echo "Done"

# Manually cleans up the compile environment
clean:
	@rm -fr $(DIR_OBJ)

# Compiles the unit tests
test: compile_prologue compile_tests compile_epilogue
# END Make Rules

# EOF makefile