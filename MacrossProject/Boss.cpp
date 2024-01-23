#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Boss.h"

using namespace sf;

Boss::Boss()
{
	//definir textura, tamaño, origen y velocidades del sprite
	//y su estado como activo

	bossTx = new Texture;
	bossTx->loadFromFile("assets/boss1.png");
	bossSprite = new Sprite;
	bossSprite->setTexture(*bossTx);
	bossSprite->setOrigin(bossTx->getSize().x / 2.0f, bossTx->getSize().y / 2.0f);
	bossSprite->setScale(1.0f, 1.0f);
	position = Vector2f(850.0f, 300.0f);
	bossSprite->setPosition(position);

	velocidadX = 3.0f;
	velocidadY = 0.8f;

	activo = false;
	vida = 10;

	//inicializar el pool de disparos
	for (int i = 0; i < maxDisparos; ++i) {
		disparosPool[i] = new Disparo(Vector2f(0.0f, 0.0f));
	}
}

//para dibujar el sprite en la clase Juego
void Boss::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*bossSprite);

}

//para actualizar el movimiento según su velocidad, el deltaTime

void Boss::Actualizar(float deltaTime) {

	//// movimiento y comportamiento del bosss///

	if (position.x >= 650) {
		position.x -= velocidadX * deltaTime;
	}
	
	if (position.x <= 650) {
		position.y -= velocidadY * deltaTime;
	}

	if (position.y < 120) {
		velocidadY = -velocidadY;  // Invertir la dirección en el eje y
		
	}

	if (position.y >= 480) {
		velocidadY = -velocidadY;  // Invertir la dirección en el eje y
		
	}
	
	//para actualizar la posicion
	bossSprite->setPosition(position);

}
//un booleano para comprobar cuándo se produce una colisión con otro rectángulo de sprites
bool Boss::Colision(const FloatRect& rect) {

	FloatRect bounds = bossSprite->getGlobalBounds();

	return bounds.intersects(rect);


}
//método para disparar
void Boss::disparar() {

	//obtener la posición del cañon laser del boss
	Vector2f bossOrigen = bossSprite->getPosition();
	Vector2f PosicionCanon = sf::Vector2f(bossOrigen.x - 62, bossOrigen.y - 55);

	for (int i = 0; i < maxDisparos; ++i) {
		//si el disparo no está activo, se desactiva y se elimina para liberar memoria
		if (!disparosPool[i]->estaActivo()) {
			disparosPool[i]->desactivar();
			delete disparosPool[i];
			//se crea un nuevo disparo y se activa
			disparosPool[i] = new Disparo(PosicionCanon);
			disparosPool[i]->activar();
			break;
		}
	}

}

//si el disparo está activo, actualiza el movimiento
void Boss::gestionarDisparos(float deltaTime) {
	for (int i = 0; i < maxDisparos; ++i) {
		if (disparosPool[i]->estaActivo()) {
			disparosPool[i]->actualizarBoss(deltaTime);
		}
	}
}

void Boss::dibujarDisparos(RenderWindow* ventana1) {

	for (int i = 0; i < maxDisparos; ++i) {
		if (disparosPool[i]->estaActivo()) {
			disparosPool[i]->Dibujar(ventana1); disparosPool;
		}
	}
}

//método para eliminar los enemigos en pantalla y dejen de ser dibujados
void Boss::desactivar() {

	activo = false;
}

void Boss::activar() {

	activo = true;
}