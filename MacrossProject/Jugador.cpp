#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"

using namespace sf;

Jugador::Jugador()
{
	//para definir la textura y sprite de la mira con su posición, origen y tamaño.
	jugadorTx = new Texture;
	jugadorTx->loadFromFile("assets/macross1.png");
	nave = new Sprite;
	nave->setTexture(*jugadorTx);
	nave->setOrigin(jugadorTx->getSize().x / 2.0f, jugadorTx->getSize().y / 2.0f);
	nave->setPosition(400, 300);
	nave->setScale(1.5f, 1.5f);

}

void Jugador::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*nave);

}
//métodos para el movimiento y obtener la posición de la mira
void Jugador::Movimiento(float x, float y) {

	nave->setPosition(x, y);


}

Vector2f Jugador::ObtenerPosicion() {

	return nave->getPosition();

}