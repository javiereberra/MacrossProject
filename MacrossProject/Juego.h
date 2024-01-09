#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"
#include "Enemigos.h"


using namespace std;
using namespace sf;

class Juego {

private:

	//variables ventana
	RenderWindow* ventana1;

	//variables para el fondo
	Texture* textura1;
	Sprite* fondo;
	Texture* textura2;
	Sprite* fondoMenu;
	Texture* textura3;
	Sprite* vidasSprite;
	Texture* explText;
	Sprite* explSprite;


	Font* fuente;
	Text* menu;

	Jugador* jugador;
	
	Enemigos* enemigos[5];

	float deltaTime;

	int vidas;
	int ptos;

	Text* vidasText;
	Text* puntajeText;

	bool start;
	float fondoSpeed;
	bool explosionActiva;

	Vector2f posicionExplosion;

public:
	//constructor de juego
	Juego(int ancho, int alto, std::string titulo);

	//método para iniciar el juego desde un menú
	void ejecutar();
	//métodos de bucle, dibujo, actualizar y procesar eventos
	void gameLoop();
	void dibujar();
	void actualizar();
	void procesar_eventos();
	// método para gestionar el disparo del mouse y colisiones

	void detectar_colisiones();

	

	//destructor de juego
	~Juego();
};