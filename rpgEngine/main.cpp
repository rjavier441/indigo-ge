#include "lib/Game.h"
using namespace std;

/*	To compile: g++ -c *.h *.cpp
	To link: g++ *.o -o game -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
*/

int main(int argc, char* argv[]){
	Game game("The Arc Stones");
	
	game.Start();

	return EXIT_SUCCESS;
}
