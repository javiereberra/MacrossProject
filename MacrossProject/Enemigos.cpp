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
	velocidadY = 2.5f;

	activo = true;
}

void Enemigos::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*naveEnemiga);

}


void Enemigos::Actualizar(float deltaTime) {

	position.x -= velocidadX * deltaTime;

	if (position.x <= -5.0f) {
		position.x = 810;
	}

	naveEnemiga->setPosition(position);

}

bool Enemigos::Colision(const FloatRect& rect) {

	FloatRect bounds = naveEnemiga->getGlobalBounds();

	return bounds.intersects(rect);


}

void Enemigos::desactivar() {

	activo = false;
}

