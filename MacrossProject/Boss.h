#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Boss {

private:
	//textura y sprite
	Texture* bossTx;
	Sprite* bossSprite;

	//velocidad en x e y, aunque quiz�s s�lo utilicemos x
	float velocidadX;
	float velocidadY;

	//booleano para determinar si el enemigo est� elimnado y deba dibujarse o no
	bool activo;


public:
	//constructor
	Boss();

	//vector para la posici�n en x e y
	Vector2f position;

	//dibujar en la ventana
	void Dibujar(RenderWindow* ventana1);

	//actualizar el movimiento con el deltaTime de Juego

	void Actualizar(float deltaTime);

	//booleano para comprobar la colisi�n del rectangulo del sprite
	bool Colision(const FloatRect& rect);

	//metodos para determinar cu�ndo activar y desactivar el boss
	void desactivar();
	void activar();

	//metodo para devolver el estado activo a Juego
	bool estaActivo() const {
		return activo;
	}
	//metodo para obtener el sprite en la clase Juego
	Sprite* getSpriteBoss() { return bossSprite; }

	

}; 
