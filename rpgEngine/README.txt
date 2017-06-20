RPG Template - Taken from commit 1cc1666 of the "york" game in indigo/games/york (project:Indigo)

To Compile and Run game on linux (assuming you have installed g++):
Option 1: Manually enter the following:
	g++ -c *.h *.cpp
	g++ *.o -o game -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
	./game

Option 2: Use the make file:
	make
	./game
