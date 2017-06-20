# MAKEFILE - to be run in the game's top level dir
# Relevant directories
INCL = ./lib/
OBJDIR = ./obj/

# Compilation Commands/Options
CC = g++
CFLAGS = -I$(INCL)
REQS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
EXENAME = game

# Dependencies
DEPS = Character.h Game.h Items.h Menu2.h Scaling.h Utilities.h World.h
OBJDEPS = Character.o Game.o Items.o Menu2.o Scaling.o Utilities.o World.o
# OBJ := $(OBJDIR)main.o $(OBJDIR)Character.o $(OBJDIR)Game.o $(OBJDIR)Items.o $(OBJDIR)Menu2.o $(OBJDIR)Scaling.o $(OBJDIR)Utilities.o $(OBJDIR)World.o
OBJ := $(OBJDIR)main.o $(OBJDIR)Character.o $(OBJDIR)Game.o $(OBJDIR)Menu2.o $(OBJDIR)Scaling.o $(OBJDIR)Utilities.o $(OBJDIR)World.o

# MAKE RULES
## For all files in OBJDEPS, compile their prereqs (i.e. header and cpp files) and store the resulting obj files in ./obj
$(OBJDEPS): main.o
	$(CC) -c $(INCL)*.h $(INCL)*.cpp
	mv *.o $(OBJDIR)
	$(CC) $(OBJ) -o $(EXENAME) $(REQS)
	exit
# %.o: %.cpp $(DEPS)
# 	$(CC) -c -o $@ $<
# 	mv *.o ./obj/

main.o: main.cpp
	$(CC) -c -o $(OBJDIR)$@ $^

# MAKE RECIPES ($^ = $(OBJ) (right of ":"))
# game: $(OBJ)
# 	$(CC) $^ -o $@ $(REQS)
# game: main.o $(OBJDEPS)
# 	$(CC) $^ -o $@ $(REQS)