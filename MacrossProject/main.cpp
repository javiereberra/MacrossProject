#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"


using namespace sf;



int main(int argc, char* argv[]) {

	Juego* partida1;

	partida1 = new Juego(800, 600, "Macross");
	partida1->ejecutar();

	return 0;
}