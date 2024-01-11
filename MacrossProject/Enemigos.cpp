#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Enemigos.h"

using namespace sf;

Enemigos::Enemigos()
{
	//definir textura, tama�o, origen y velocidades del sprite
	//y su estado como activo

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

//para dibujar el sprite en la clase Juego
void Enemigos::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*naveEnemiga);

}

//para actualizar el movimiento seg�n su velocidad, el deltaTime

void Enemigos::Actualizar(float deltaTime) {

	position.x -= velocidadX * deltaTime;

	//condicional para generar un bucle que haga que las naves vuelvan cuando salen de la pantalla
	if (position.x <= -5.0f) {
		position.x = 810;
	}
	//para actualizar la posicion
	naveEnemiga->setPosition(position);

}

//un booleano para comprobar cu�ndo se produce una colisi�n con otro rect�ngulo de sprites
bool Enemigos::Colision(const FloatRect& rect) {

	FloatRect bounds = naveEnemiga->getGlobalBounds();

	return bounds.intersects(rect);


}
//m�todo para eliminar los enemigos en pantalla y dejen de ser dibujados
void Enemigos::desactivar() {

	activo = false;
}

void Enemigos::activar() {

	activo = true;
}

