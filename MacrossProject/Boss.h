#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Disparo.h"
#include "Misiles.h"

using namespace sf;

class Boss {

private:
	//textura y sprite
	Texture* bossTx;
	Sprite* bossSprite;

	//velocidad en x e y, aunque quizás sólo utilicemos x
	float velocidadX;
	float velocidadY;

	//booleano para determinar si el enemigo está elimnado y deba dibujarse o no
	bool activo;
	int vida;

	//generar un pool de disparos
	static const int maxDisparos = 5;
	Disparo* disparosPool[maxDisparos];

	//generar un pool de misiles
	static const int maxMisiles = 2;
	Misiles* misilesPool[maxMisiles];

public:
	//constructor
	Boss();

	//vector para la posición en x e y
	Vector2f position;

	//dibujar en la ventana
	void Dibujar(RenderWindow* ventana1);

	//actualizar el movimiento con el deltaTime de Juego

	void Actualizar(float deltaTime);

	//booleano para comprobar la colisión del rectangulo del sprite
	bool Colision(const FloatRect& rect);

	//metodos para determinar cuándo activar y desactivar el boss
	void desactivar();
	void activar();

	//metodo para devolver el estado activo a Juego
	bool estaActivo() const {
		return activo;
	}
	//metodo para obtener el sprite en la clase Juego
	Sprite* getSpriteBoss() { return bossSprite; }

	//método para actualizar la vida del boss
	void modificarVida(int nuevaVida) {
		vida = nuevaVida;
	}

	// Método para obtener la vida actual
	int obtenerVida() const {
		return vida;
	}


	//método para disparar
	void disparar();
	//método para gestionar los disparos
	void gestionarDisparos(float deltaTime);
	//método para dibujar disparos
	void dibujarDisparos(RenderWindow* deltaTime);

	//método para disparar
	void lanzarMisiles();
	//método para gestionar los disparos
	void gestionarMisiles(float deltaTime);
	//método para dibujar disparos
	void dibujarMisiles(RenderWindow* deltaTime);



	//metodo para obtener el arreglo de disparos en Juego
	Disparo** getDisparosPool() {
		return disparosPool;
	}
	//metodo para obtener el max de disparos en Juego
	int getMaxDisparos() const {
		return maxDisparos;
	}

	//metodo para obtener el arreglo de disparos en Juego
	Misiles** getMisilesPool() {
		return misilesPool;
	}
	//metodo para obtener el max de disparos en Juego
	int getMaxMisiles() const {
		return maxMisiles;
	}
}; 
