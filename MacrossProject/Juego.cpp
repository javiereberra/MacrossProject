#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"

using namespace sf;
using namespace std;

Juego::Juego(int ancho, int alto, std::string titulo) {

	//Ventana
	ventana1 = new RenderWindow(VideoMode(ancho, alto), titulo);

	//Textura y Sprite de fondo
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("assets/fondo1.jpg");
	fondo->setTexture(*textura1);
	fondo->setScale(2.0f,2.0f);
	
	textura2 = new Texture;
	fondoMenu = new Sprite;
	textura2->loadFromFile("assets/menu.jpg");
	fondoMenu->setTexture(*textura2);

	textura3 = new Texture;
	vidasSprite = new Sprite;
	textura3->loadFromFile("assets/macross1.png");
	vidasSprite->setTexture(*textura3);
	vidasSprite->setScale(1.0f, 1.0f);
	vidasSprite->setPosition(10, 10);

	fuente = new Font;
	menu = new Text;
	fuente->loadFromFile("assets/arial.ttf");
	menu->setFont(*fuente);
	menu->setString("PRESIONA 'S' PARA COMENZAR");
	menu->setCharacterSize(15);
	menu->setPosition(290, 450);

	jugador = new Jugador();
	
	enemigos[0] = new Enemigos();
	enemigos[0]->position = Vector2f(690.0f, 300.0f);
	enemigos[1] = new Enemigos();
	enemigos[1]->position = Vector2f(700.0f, 500.0f);
	enemigos[2] = new Enemigos();
	enemigos[2]->position = Vector2f(710.0f, 100.0f);
	enemigos[3] = new Enemigos();
	enemigos[3]->position = Vector2f(680.0f, 400.0f);
	enemigos[4] = new Enemigos();
	enemigos[4]->position = Vector2f(730.0f, 200.0f);

	fondoSpeed = 2.0f;

	//para que siempre inicie el menú
	start = false;

	deltaTime = 1.0f / 60.0f;

	vidas = 3;
	ptos = 0;

	puntajeText = new Text;
	puntajeText->setFont(*fuente);
	puntajeText->setCharacterSize(20);
	puntajeText->setString("SCORE: " + to_string(ptos));
	puntajeText->setPosition(650, 10);

	vidasText = new Text;
	vidasText->setFont(*fuente);
	vidasText->setCharacterSize(20);
	vidasText->setString(to_string(vidas));
	vidasText->setPosition(50, 10);

}

//metodo para iniciar un menu simple antes de iniciar el juego
void Juego::ejecutar() {

	while (ventana1->isOpen()) {
		Event evento;
		while (ventana1->pollEvent(evento)) {
			if (evento.type == Event::Closed)
				ventana1->close();
			//Presionar "s" para iniciar el gameloop
			if (evento.type == Event::KeyPressed) {
				if (evento.key.code == Keyboard::Key::S && !start) {

					start = true;


				}
			}
		}

		ventana1->clear(Color::Black);

		if (start) {
			//iniciar el loop si start es true
			gameLoop();

		}
		else {
			//Menu de fondo si start es false
			ventana1->draw(*fondoMenu);
			ventana1->draw(*menu);
			
			
		}

		ventana1->display();
	}
}

void Juego::gameLoop() {

	

	while (ventana1->isOpen() && start) {

		procesar_eventos();
		actualizar();

		dibujar();

	}
}

void Juego::procesar_eventos() {
	Event evento1;
	while (ventana1->pollEvent(evento1)) {
		switch (evento1.type) {
		case Event::Closed:
			ventana1->close();
			break;
		}
	}

	jugador->Movimiento(deltaTime);
	

}

void Juego::actualizar() {
	fondo->move(-fondoSpeed * deltaTime, 0);

	if (fondo->getPosition().x <= (-665.0f)) {
	fondo->setPosition(0, 0); // Reinicia la posición del fondo
	}

	jugador->Actualizar(deltaTime);

	
	for (int i = 0; i < 5; ++i) {  
		enemigos[i]->Actualizar(deltaTime); 
	}
	
}

void Juego::dibujar() {

	ventana1->clear();

	ventana1->draw(*fondo);
	
	jugador->Dibujar(ventana1);

	// para los 5 va un for
	for (int i = 0; i < 5; ++i) {  
		enemigos[i]->Dibujar(ventana1);  
	}

	ventana1->draw(*puntajeText);
	ventana1->draw(*vidasText);
	ventana1->draw(*vidasSprite);

	ventana1->display();


}