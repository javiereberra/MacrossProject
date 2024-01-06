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

	float velocidadX;
	float velocidadY;
	

	Vector2f position;

public:
	//constructor
	Jugador();

	void Dibujar(RenderWindow* ventana1);

	//gestionar el movimiento del cursor
	void Movimiento(float deltaTime);
	void Actualizar(float deltaTime);
	

};
