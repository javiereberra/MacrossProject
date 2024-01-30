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

	//inicializar el pool de disparos
	for (int i = 0; i < maxDisparos; ++i) {
		disparosPool[i] = new Disparo(Vector2f(0.0f, 0.0f));
	}

	//inicializar el pool de misiles
	for (int i = 0; i < maxMisiles; ++i) {
		misilesPool[i] = new Misiles(Vector2f(0.0f, 0.0f));
	}

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

//método para disparar
void Jugador::disparar() {
	for (int i = 0; i < maxDisparos; ++i){
		//si el disparo no está activo, se desactiva y se elimina para liberar memoria
		if (!disparosPool[i]->estaActivo()) {
			disparosPool[i]->desactivar();
			delete disparosPool[i];
			//se crea un nuevo disparo y se activa
			disparosPool[i] = new Disparo(nave->getPosition());
			disparosPool[i]->activar();
			break;
		}
	}

}


//método para disparar misiles
void Jugador::lanzarMisiles() {
	for (int i = 0; i < maxMisiles; ++i) {
		//si el disparo no está activo, se desactiva y se elimina para liberar memoria
		if (!misilesPool[i]->estaActivo()) {
			misilesPool[i]->desactivar();
			delete misilesPool[i];
			//se crea un nuevo disparo y se activa
			misilesPool[i] = new Misiles(nave->getPosition());
			misilesPool[i]->activar();
			
			
			break;
		}
	}

}


//si el disparo está activo, actualiza el movimiento
void Jugador::gestionarDisparos(float deltaTime) {
	for (int i = 0; i < maxDisparos; ++i) {
		if (disparosPool[i]->estaActivo()) {
			disparosPool[i]->actualizar(deltaTime);
		}
	}
}

void Jugador::gestionarMisiles(float deltaTime) {
	for (int i = 0; i < maxMisiles; ++i) {
		if (misilesPool[i]->estaActivo()) {
			misilesPool[i]->actualizar(deltaTime);
		}
	}
}

void Jugador::dibujarDisparos(RenderWindow* ventana1) {

	for (int i = 0; i < maxDisparos; ++i) {
		if (disparosPool[i]->estaActivo()) {
			disparosPool[i]->Dibujar(ventana1); disparosPool;
			}
	}
}

void Jugador::dibujarMisiles(RenderWindow* ventana1) {

	for (int i = 0; i < maxMisiles; ++i) {
		if (misilesPool[i]->estaActivo()) {
			misilesPool[i]->Dibujar(ventana1); misilesPool;
		}
	}
}

void Jugador::setPosition(Vector2f nuevaPosicion) {

	position = nuevaPosicion;
	nave->setPosition(position);
}

//liberar memoria de los pools
Jugador::~Jugador() {

	for (int i = 0; i < maxDisparos; ++i) {
		delete disparosPool[i];
	}

	for (int i = 0; i < maxMisiles; ++i) {
		delete misilesPool[i];
	}
}