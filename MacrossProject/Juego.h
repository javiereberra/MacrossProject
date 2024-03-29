#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
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

	//fuente para todos los textos del juego
	Font* fuente;
	//texto para el menu de inicio
	Text* menu;
	Text* instrucc;
	Text* instrucc2;
	Text* instrucc3;
	Text* finDelJuego;
	Text* restart;

	//Textura y sprite de game Over
	Texture* textura4;
	Sprite* fondoGameOver;

	//Texturas y sprite de animacion de la explosion
	Texture* explosionFrames[3];
	Sprite explosionAnimation;


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

	//booleando para determinar cu�ndo se producen las explosiones
	bool explosionActiva;

	//posici�n de las explosiones
	Vector2f posicionExplosion;
	
	int posAleatoria;

	Vector2f posiciones[10];

	//variables para automatizar los disparos y misiles del boss
	float ultimoDisparo;
	const float intervaloDisparo = 60.0f;

	float ultimoMisil;
	const float intervaloMisiles = 120.0f;

	float explosionTime;
	float explosionFrameDuration;

	bool jugando;


	//agregar sonido
	SoundBuffer* disparoBff;
	Sound* disparoSnd;

	SoundBuffer* misileBff;
	Sound* misileSnd;

	SoundBuffer* explosionBff;
	Sound* explosionSnd;
	
	//Musica
	Music intro;
	Music game;
	Music end;
	
	

public:
	//constructor de juego
	Juego(int ancho, int alto, std::string titulo);

	//m�todo para iniciar el juego desde un men�
	void ejecutar();
	//m�todos de bucle, dibujo, actualizar y procesar eventos
	void gameLoop();
	void dibujar();
	void actualizar();
	void procesar_eventos();
	
	// m�todo para gestionar colisiones
	void detectar_colisiones();
	// para organizar las distintas colisiones
	void colisiones_jugador_enemigos();
	void colisiones_disparos_enemigos();
	void colisiones_misiles_enemigos();
	void colisiones_disparos_boss();
	void colisiones_misiles_boss();
	void colisiones_jugador_boss();
	void colisiones_jugador_disparos();
	void colisiones_jugador_misiles();

	//un metodo para aumentar la dificultard
	void dificultad();
	
	//metodos para el gameover y reiniciar el juego
	void reiniciar();
	void gameOver();

	void explosionAnimada();

	//destructor de juego
	~Juego();
};