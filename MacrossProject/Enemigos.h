#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Enemigos {

private:
	//textura y sprite
	Texture* enemigoTx;
	Sprite* naveEnemiga;

	float velocidadX;
	float velocidadY;


	

public:
	//constructor
	Enemigos();

	Vector2f position;

	void Dibujar(RenderWindow* ventana1);

	//gestionar el movimiento del cursor
	
	void Actualizar(float deltaTime);

	bool Colision(const FloatRect& rect);

	Sprite* getSpriteNaveEnemiga() { return naveEnemiga; }

};
