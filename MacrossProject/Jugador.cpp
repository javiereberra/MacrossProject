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
	nave->setScale(1.5f, 1.5f);

	
	
	velocidadX = 3.0f;
	velocidadY = 3.0f;

	position = Vector2f(100.0f, 300.0f);
}

void Jugador::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*nave);

}
//métodos para el movimiento y obtener la posición de la mira
void Jugador::Movimiento(float deltaTime) {

	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		position.y -= velocidadY * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		position.y += velocidadY * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		position.x -= velocidadX * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		position.x += velocidadX * deltaTime;
	}

	



}

void Jugador::Actualizar(float deltaTime) {

	

	nave->setPosition(position);

}

bool Jugador::Colision(float x, float y) {

	FloatRect bounds = nave->getGlobalBounds();

	if (bounds.contains(x, y)) {
		return true;
	}


}
