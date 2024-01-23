#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"
#include "Enemigos.h"
#include "Disparo.h"
#include "Boss.h"
#include "Misiles.h"


using namespace std;
using namespace sf;

class Juego {

private:

	//ventana
	RenderWindow* ventana1;

	//Textura y sprite para el fondo
	Texture* textura1;
	Sprite* fondo;

	//Textura y sprite para un menu de inicio
	Texture* textura2;
	Sprite* fondoMenu;

	//Textura y sprite para un marcador de vidas
	Texture* textura3;
	Sprite* vidasSprite;

	//Textura y sprite para una explosión cuando naves son eliminadas
	Texture* explText;
	Sprite* explSprite;

	//fuente para todos los textos del juego
	Font* fuente;
	//texto para el menu de inicio
	Text* menu;

	//variable de jugador
	Jugador* jugador;
	
	//arreglo para 5 enemigos comunes
	Enemigos* enemigos[5];

	//variable boss
	Boss* boss;

	//deltaTime para gestionar los frames por segundos
	float deltaTime;

	//variables para las vidas y puntaje del juegador
	int vidas;
	int ptos;

	//textos para las vidas y puntajes
	Text* vidasText;
	Text* puntajeText;

	//un booleando para iniciar el loop del juego desde el menu
	bool start;

	//velocidad para aplicar y animar al fondo del nivel
	float fondoSpeed;

	//booleando para determinar cuándo se producen las explosiones
	bool explosionActiva;

	//posición de las explosiones
	Vector2f posicionExplosion;
	
	int posAleatoria;

	Vector2f posiciones[10];

	float ultimoDisparo;
	const float intervaloDisparo = 10.0f;

	float ultimoMisil;
	const float intervaloMisiles = 30.0f;

	

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
	
	// método para gestionar colisiones
	void detectar_colisiones();
	// para organizar las distintas colisiones
	void colisiones_jugador_enemigos();
	void colisiones_disparos_enemigos();
	void colisiones_misiles_enemigos();
	void colisiones_disparos_boss();
	void colisiones_misiles_boss();

	//un metodo para aumentar la dificultard
	void dificultad();
	


	//destructor de juego
	~Juego();
};