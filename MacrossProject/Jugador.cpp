#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"

using namespace sf;

//Constructor
Jugador::Jugador()
{
	//para definir la textura y sprite de la mira con su posición, origen y tamaño.
	jugadorTx = new Texture;
	jugadorTx->loadFromFile("assets/macross1.png");
	nave = new Sprite;
	nave->setTexture(*jugadorTx);
	nave->setOrigin(jugadorTx->getSize().x / 2.0f, jugadorTx->getSize().y / 2.0f);
	nave->setScale(1.5f, 1.5f);

	
	//velocidades en x e y
	velocidadX = 3.0f;
	velocidadY = 3.0f;

	//posición inicial del sprite
	position = Vector2f(100.0f, 300.0f);
}

//para dibujar el sprite en la clase Juego
void Jugador::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*nave);

}

//para manejar el movimiento con las flechas del teclado
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

//para actualizar la posición del sprite
void Jugador::Actualizar(float deltaTime) {

	nave->setPosition(position);

}

//booleano para comprobar la colisión
bool Jugador::Colision(const FloatRect& rect) {

	FloatRect bounds = nave->getGlobalBounds();

			return bounds.intersects(rect);
	}


