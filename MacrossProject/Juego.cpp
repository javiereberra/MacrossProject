#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"

using namespace sf;
using namespace std;

Juego::Juego(int ancho, int alto, std::string titulo) {

	//Ventana
	ventana1 = new RenderWindow(VideoMode(ancho, alto), titulo);

	//Textura y Sprite del fondo del nivel
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("assets/fondo1.jpg");
	fondo->setTexture(*textura1);
	fondo->setScale(2.0f,2.0f);
	
	//Textura y Sprite del fondo de inicio
	textura2 = new Texture;
	fondoMenu = new Sprite;
	textura2->loadFromFile("assets/menu.jpg");
	fondoMenu->setTexture(*textura2);

	//Textura y Sprite del ícono para marcador de vidas
	textura3 = new Texture;
	vidasSprite = new Sprite;
	textura3->loadFromFile("assets/macross1.png");
	vidasSprite->setTexture(*textura3);
	vidasSprite->setScale(1.0f, 1.0f);
	vidasSprite->setPosition(10, 10);

	////Textura y Sprite de las explosiones
	explText = new Texture;
	explSprite = new Sprite;
	explText->loadFromFile("assets/exp2tr.png");
	explSprite->setTexture(*explText);
	
	//fuente
	fuente = new Font;

	//texto para el menú de inicio
	menu = new Text;
	fuente->loadFromFile("assets/arial.ttf");
	menu->setFont(*fuente);
	menu->setString("PRESIONA 'S' PARA COMENZAR");
	menu->setCharacterSize(15);
	menu->setPosition(290, 450);

	//jugador
	jugador = new Jugador();
	
	//los 5 enemigos con sus posiciones iniciales
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

	//velocidad para la animación del fondo
	fondoSpeed = 2.0f;

	//para que siempre inicie el menú
	start = false;

	//establecer los 60fps por segundo
	deltaTime = 1.0f / 60.0f;

	//establecer vidas y puntaje inicial
	vidas = 3;
	ptos = 0;

	//textos para puntaje y para las vidas
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


	//para inciar en falso las explosiones
	explosionActiva = false;
	

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

//el loop del juego iniciado, procesando eventos, actualizando moviemientos y dibujando todo
void Juego::gameLoop() {
	
	while (ventana1->isOpen() && start) {

		procesar_eventos();
		actualizar();
		dibujar();
	}
}

//prosecar los eventos para cerrar ventana y el movimiento del Jugador con los controles
void Juego::procesar_eventos() {
	Event evento1;
	while (ventana1->pollEvent(evento1)) {
		switch (evento1.type) {
		case Event::Closed:
			ventana1->close();
			break;
		case Event::KeyPressed:
		// Presionar SPACE para disparar
		if (evento1.key.code == Keyboard::Key::Space) {
			jugador->disparar();
		}
		break;
}
	}

	jugador->Movimiento(deltaTime);
	
}

//actualizar todos los movimientos
void Juego::actualizar() {
	
	//movimiento del fondo para que tenga una animación
	fondo->move(-fondoSpeed * deltaTime, 0);

	//generar un bucle para que parezca un fondo infinito
	if (fondo->getPosition().x <= (-665.0f)) {
	fondo->setPosition(0, 0); // Reinicia la posición del fondo
	}

	//actualizar movimiento del jugador
	jugador->Actualizar(deltaTime);

	//actualizar los movimientos de los enemigos sólo si están activos
	for (int i = 0; i < 5; ++i) {
		if (enemigos[i] && enemigos[i]->estaActivo()) {
			enemigos[i]->Actualizar(deltaTime);
		}
	}

	// actualizar los disparos
	jugador->gestionarDisparos(deltaTime);

	//detectar las colisiones	
	detectar_colisiones();

}

//dibujar fondo, jugador
void Juego::dibujar() {

	ventana1->clear();

	ventana1->draw(*fondo);
	
	jugador->Dibujar(ventana1);

	// dibujar los enemigos si están activos
	for (int i = 0; i < 5; ++i) { 
		if (enemigos[i] && enemigos[i]->estaActivo()) {
			enemigos[i]->Dibujar(ventana1);
		}
	}
	//dibujar disparos
	jugador->dibujarDisparos(ventana1);
	//dibujar los puntaje y las vidas
	ventana1->draw(*puntajeText);
	ventana1->draw(*vidasText);
	ventana1->draw(*vidasSprite);

	//dibujar las explosiones en caso de haberlas
	if (explosionActiva) {
		ventana1->draw(*explSprite);
	}

	ventana1->display();


}

//detección de colisiones
void Juego::detectar_colisiones() {

	//sprite para obtener el sprite de jugador
	Sprite* spriteNave = jugador->getSpriteNaveJugador();



	//obtener el rectangulo del sprite de jugador
	if (spriteNave) {
		FloatRect jugadorRect = spriteNave->getGlobalBounds();

		//Comprobar con los enemigos que estén activos
		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Obtener el sprite de cada enemigo
				Sprite* spriteEnemigo = enemigos[i]->getSpriteNaveEnemiga();
				// obtener el rectángulo de cada sprite
				FloatRect enemigoRect = spriteEnemigo->getGlobalBounds();

				//detectar las colisiones entre jugadores y enemigos
				if (jugadorRect.intersects(enemigoRect)) {
					//sumar puntaje por enemigo eliminado
					ptos++;
					puntajeText->setString("SCORE: " + to_string(ptos));

					//ajustar la posición de la explosión a la posición del enemigo colisionado
					posicionExplosion = enemigos[i]->getSpriteNaveEnemiga()->getPosition();
					explSprite->setPosition(posicionExplosion);

					//activar la explosión
					explosionActiva = true;
					//desactivar el enemigo
					enemigos[i]->desactivar();

				}

				for (int j = 0; j < jugador->getMaxDisparos(); ++j) {
					if (jugador->getDisparosPool()[j]->estaActivo()) {
						// Obtener el rectángulo de cada disparo
						FloatRect disparoRect = jugador->getDisparosPool()[j]->bounds();

						// Detectar colisiones entre disparo y enemigo
						if (enemigos[i]->Colision(disparoRect)) {
							// Desactivar el disparo
							jugador->getDisparosPool()[j]->desactivar();

							// Ajustar la posición de la explosión a la posición del enemigo colisionado
							posicionExplosion = enemigos[i]->getSpriteNaveEnemiga()->getPosition();
							explSprite->setPosition(posicionExplosion);

							// Activar la explosión
							explosionActiva = true;
							// Desactivar el enemigo
							enemigos[i]->desactivar();

							// Sumar puntaje por impacto de disparo
							ptos += 10; // Puedes ajustar la puntuación según tu lógica
							puntajeText->setString("SCORE: " + to_string(ptos));
						}




					}
				}

			}




		}
	}
}