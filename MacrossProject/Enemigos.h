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

	//velocidad en x e y, aunque quizás sólo utilicemos x
	float velocidadX;
	float velocidadY;

	//booleano para determinar si el enemigo está elimnado y deba dibujarse o no
	bool activo;
	

public:
	//constructor
	Enemigos();

	//vector para la posición en x e y
	Vector2f position;

	//dibujar en la ventana
	void Dibujar(RenderWindow* ventana1);

	//actualizar el movimiento con el deltaTime de Juego
	
	void Actualizar(float deltaTime);

	//booleano para comprobar la colisión del rectangulo del sprite
	bool Colision(const FloatRect& rect);

	//un método para marcar como eliminado al enemigo y desactivarlo
	void desactivar();
	void activar();

	//metodo para devolver el estado activo a Juego
	bool estaActivo() const {
		return activo;
	}
	//metodo para obtener el sprite en la clase Juego
	Sprite* getSpriteNaveEnemiga() { return naveEnemiga; }

	//para poder modificar la velocidad de los enemigos en Juego
	void setVelocidadX(float nuevaVelocidadX) {
		velocidadX = nuevaVelocidadX;
	}

};
