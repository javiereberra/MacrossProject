#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Enemigos.h"

using namespace sf;

Enemigos::Enemigos()
{
	//para definir la textura y sprite de la mira con su posición, origen y tamaño.
	enemigoTx = new Texture;
	enemigoTx->loadFromFile("assets/enemigo1.png");
	naveEnemiga = new Sprite;
	naveEnemiga->setTexture(*enemigoTx);
	naveEnemiga->setOrigin(enemigoTx->getSize().x / 2.0f, enemigoTx->getSize().y / 2.0f);
	naveEnemiga->setScale(1.0f, 1.0f);


	velocidadX = 3.0f;
	velocidadY = 3.0f;

	position = Vector2f(700.0f, 300.0f);
}

void Enemigos::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*naveEnemiga);

}
//métodos para el movimiento y obtener la posición de la mira
void Enemigos::Movimiento(float deltaTime) {

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

void Enemigos::Actualizar(float deltaTime) {



	naveEnemiga->setPosition(position);

}

