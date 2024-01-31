#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Disparo.h"
#include "Misiles.h"

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

	//generar un pool de disparos
	static const int maxDisparos = 5;
	Disparo* disparosPool[maxDisparos];

	//generar un pool de misiles
	static const int maxMisiles = 2;
	Misiles* misilesPool[maxMisiles];

public:
	//constructor
	Jugador();
	//destructor de jugador
	~Jugador();
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
	//método para reiniciar la posición del Jugador desde Juego
	void setPosition(Vector2f nuevaPosicion);

};
