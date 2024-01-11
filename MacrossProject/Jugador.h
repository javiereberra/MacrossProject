#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Jugador {

private:
	//textura y sprite
	Texture* jugadorTx;
	Sprite* nave;
	//velocidad en x e y
	float velocidadX;
	float velocidadY;
	
	
	//posicion del sprite
	Vector2f position;

public:
	//constructor
	Jugador();
	//para dibujar en clase Juego
	void Dibujar(RenderWindow* ventana1);

	//gestionar el movimiento del cursor
	void Movimiento(float deltaTime);
	//actualizar el movimiento
	void Actualizar(float deltaTime);
	//comprobar las colisiones del sprite
	bool Colision(const FloatRect& rect);
	//para obtener el sprite en la clase Juego
	Sprite* getSpriteNaveJugador() { return nave; }

};
