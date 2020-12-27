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

# ANSI Escape Sequence (Echo Color Scheme) Shortcuts
AES_RESET = \e[0m
AES_TXGREEN_BGBLACK = \e[1;92m
AES_TXRED_BGBLACK = \e[1;31m
AES_TXBLUE_BGBLACK = \e[1;34m
AES_TXCYAN_BGBLACK = \e[1;96m
AES_TXYELLOW_BGBLACK = \e[1;33m
AES_THEME_DANGER = \e[1;41;37m
AES_THEME_WARNING = \e[0;43;30m
AES_THEME_SUCCESS = \e[0;42;37m
AES_THEME_INFO = \e[0;46;37m
AES_THEME_PRIMARY = \e[0;44;37m

# Relevant Directories
DIR_CLASS = ./lib/class
DIR_IFACE = ./lib/interface
DIR_MODULE = ./lib/modules
DIR_SRC = ./src
DIR_TEST = ./test
DIR_BUILD = ./build
DIR_OBJ = $(DIR_BUILD)/obj

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
TEST_FILES = $(shell find $(DIR_TEST) -regex '.*.\(cpp\|hpp\|h\)')

# BEGIN Make Rules
# The default; runs "game" make rules first, then unsets the compilation
# directories as cleanup
compile_epilogue:
	@echo "$(AES_THEME_PRIMARY)[ Cleaning Up ]$(AES_RESET)"
	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Compiles the game
# game: compile_prologue interface class
game: compile_prologue
	@echo "$(AES_THEME_PRIMARY)[ Compiling Game ]$(AES_RESET)"
	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Compiles the unit tests
compile_tests:
	@echo "$(AES_THEME_PRIMARY)[ Gathering Source Files ]$(AES_RESET)"

	@# DEBUG
	@echo "module files: $(MODULE_FILES)"
	@echo "interface files: $(IFACE_FILES)"
	@echo "class files: $(CLASS_FILES)"
	@echo "test files: $(TEST_FILES)"

	@echo "$(AES_THEME_PRIMARY)[ Compiling Tests ]$(AES_RESET)"
	$(CC) -c -Wall $(MODULE_FILES) $(IFACE_FILES) $(CLASS_FILES) $(TEST_FILES)

	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Collects test object files
collect_tests:
	@echo "$(AES_THEME_PRIMARY)[ Collecting Test Objects ]$(AES_RESET)"

	$(shell mv *.o $(DIR_OBJ))

	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Sets up the compile environment (i.e. relevant directories for compilation)
compile_prologue:
	@echo "$(AES_THEME_PRIMARY)[ Initializing Compile Environment ]$(AES_RESET)"
	@mkdir -p $(DIR_BUILD)
	@mkdir -p $(DIR_OBJ)
	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Links generated objects
link_objects:
	@echo "$(AES_THEME_PRIMARY)[ Linking Objects ]$(AES_RESET)"
	$(CC) $(DIR_OBJ)/* -o $(TESTNAME) $(REQS)
	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Manually cleans up the compile environment and precompiled headers (.gch)
clean:
	@echo "$(AES_THEME_PRIMARY)[ Cleaning ]$(AES_RESET)"
	@rm -fr $(DIR_OBJ)
	@rm -fr $(DIR_BUILD)
	@rm -fr $(shell find . -name '*.gch')
	@rm -fr ./*.o
	@echo "$(AES_TXGREEN_BGBLACK)[ Done ]$(AES_RESET)"

# Compiles the unit tests
test: compile_prologue compile_tests collect_tests link_objects compile_epilogue
# END Make Rules

# EOF makefile