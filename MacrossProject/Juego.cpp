#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"
#include <iostream>

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

	//boss
	boss = new Boss();
	
	//establecer las posiciones de spawn de los enemigos
	posiciones[0] = Vector2f(890.0f, 100.0f);
	posiciones[1] = Vector2f(890.0f, 150.0f);
	posiciones[2] = Vector2f(850.0f, 200.0f);
	posiciones[3] = Vector2f(830.0f, 250.0f);
	posiciones[4] = Vector2f(850.0f, 300.0f);
	posiciones[5] = Vector2f(890.0f, 350.0f);
	posiciones[6] = Vector2f(830.0f, 400.0f);
	posiciones[7] = Vector2f(890.0f, 450.0f);
	posiciones[8] = Vector2f(850.0f, 500.0f);
	posiciones[9] = Vector2f(830.0f, 550.0f);

	//los 5 enemigos con sus posiciones iniciales
	enemigos[0] = new Enemigos();
	enemigos[0]->position = posiciones[0];
	enemigos[1] = new Enemigos();
	enemigos[1]->position = posiciones[2];
	enemigos[2] = new Enemigos();
	enemigos[2]->position = posiciones[4];
	enemigos[3] = new Enemigos();
	enemigos[3]->position = posiciones[6];
	enemigos[4] = new Enemigos();
	enemigos[4]->position = posiciones[8];

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
	
	posAleatoria = 0;

	ultimoDisparo = 0.0f;

	
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
		else if (evento1.key.code == Keyboard::Key::M) {
			jugador->lanzarMisiles();
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
	//actualizar el comportamiento del boss
	if (boss->estaActivo()) {
		boss->Actualizar(deltaTime);
	}


	// actualizar los disparos
	jugador->gestionarDisparos(deltaTime);

	// actualizar los disparos
	jugador->gestionarMisiles(deltaTime);

	ultimoDisparo += deltaTime;

	if (boss->estaActivo()) {
		// Verificar el intervalo de tiempo desde el último disparo del boss
		if (ultimoDisparo >= intervaloDisparo) {
			// Disparar automáticamente
			boss->disparar();
			// Reiniciar el contador de tiempo
			ultimoDisparo = 0.0f;
		}
	}
	// actualizar los disparos
	boss->gestionarDisparos(deltaTime);
	

	//detectar las colisiones	
	detectar_colisiones();

	//metodo para dificultad
	dificultad();

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
	// dibjar al boss sólo si está activo
	if (boss->estaActivo()) {
		boss->Dibujar(ventana1);
	}

	//dibujar disparos
	jugador->dibujarDisparos(ventana1);

	//dibujar misiles
	jugador->dibujarMisiles(ventana1);

	//dibujar disparos
	boss->dibujarDisparos(ventana1);
	
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

	colisiones_jugador_enemigos();
	colisiones_disparos_enemigos();
	colisiones_misiles_enemigos();
	colisiones_disparos_boss();
	colisiones_misiles_boss();


}

void Juego::colisiones_jugador_enemigos() {
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
					ptos += 10;
					vidas -= 1;
					puntajeText->setString("SCORE: " + to_string(ptos));
					vidasText->setString(to_string(vidas));

					//ajustar la posición de la explosión a la posición del enemigo colisionado
					posicionExplosion = enemigos[i]->getSpriteNaveEnemiga()->getPosition();
					explSprite->setPosition(posicionExplosion);

					//activar la explosión
					explosionActiva = true;
					//desactivar el enemigo
					enemigos[i]->desactivar();
					//nuevo enemigo
					delete enemigos[i];
					//se crea un nuevo enemigo y se activa
					enemigos[i] = new Enemigos;
					enemigos[i]->activar();
					//se genera una posicion aleatoria para el spawn
					posAleatoria = rand() % 10;
					enemigos[i]->position = posiciones[posAleatoria];

				}
			}
		}
	}
}

void Juego::colisiones_disparos_enemigos() {
	
	//Comprobar con los enemigos que estén activos
	for (int i = 0; i < 5; ++i) {
		if (enemigos[i] && enemigos[i]->estaActivo()) {
			// Obtener el sprite de cada enemigo
			Sprite* spriteEnemigo = enemigos[i]->getSpriteNaveEnemiga();
			// obtener el rectángulo de cada sprite
			FloatRect enemigoRect = spriteEnemigo->getGlobalBounds();
			//comprobar las colisiones de los disparos con los enemigos
			for (int j = 0; j < jugador->getMaxDisparos(); ++j) {
				if (jugador->getDisparosPool()[j]->estaActivo()) {
					// Obtener el rectángulo de cada disparo
					FloatRect disparoRect = jugador->getDisparosPool()[j]->bounds();

					// Detectar colisiones 
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
						delete enemigos[i];
						//se crea un nuevo enemigo y se activa
						enemigos[i] = new Enemigos;
						enemigos[i]->activar();
						//se genera una posicion aleatoria para el spawn
						posAleatoria = rand() % 10;
						enemigos[i]->position = posiciones[posAleatoria];


						// Sumar puntaje por impacto de disparo
						ptos += 10; // Puedes ajustar la puntuación según tu lógica
						puntajeText->setString("SCORE: " + to_string(ptos));
					}
				}
			}
		}
	}
}
void Juego::colisiones_misiles_enemigos() {
	//Comprobar con los enemigos que estén activos
	for (int i = 0; i < 5; ++i) {
		if (enemigos[i] && enemigos[i]->estaActivo()) {
			// Obtener el sprite de cada enemigo
			Sprite* spriteEnemigo = enemigos[i]->getSpriteNaveEnemiga();
			// obtener el rectángulo de cada sprite
			FloatRect enemigoRect = spriteEnemigo->getGlobalBounds();
			//comprobar las colisiones de los misiles con los enemigos
			for (int j = 0; j < jugador->getMaxMisiles(); ++j) {
				if (jugador->getMisilesPool()[j]->estaActivo()) {
					// Obtener el rectángulo de cada misil
					FloatRect misilesRect = jugador->getMisilesPool()[j]->bounds();

					// Detectar colisiones 
					if (enemigos[i]->Colision(misilesRect)) {
						// Desactivar el misil
						jugador->getMisilesPool()[j]->desactivar();

						// Ajustar la posición de la explosión a la posición del enemigo colisionado
						posicionExplosion = enemigos[i]->getSpriteNaveEnemiga()->getPosition();
						explSprite->setPosition(posicionExplosion);

						// Activar la explosión
						explosionActiva = true;
						// Desactivar el enemigo
						enemigos[i]->desactivar();
						delete enemigos[i];
						//se crea un nuevo enemigo y se activa
						enemigos[i] = new Enemigos;
						enemigos[i]->activar();
						//se genera una posicion aleatoria para el spawn
						posAleatoria = rand() % 10;
						enemigos[i]->position = posiciones[posAleatoria];


						// Sumar puntaje por impacto de misil
						ptos += 10; // Puedes ajustar la puntuación según tu lógica
						puntajeText->setString("SCORE: " + to_string(ptos));
					}
				}
			}
		}
	}
}
void Juego::colisiones_disparos_boss() {
	
			//comprobar las colisiones de los disparos con el boss
			for (int i = 0; i < jugador->getMaxDisparos(); ++i) {
				if (jugador->getDisparosPool()[i]->estaActivo()) {
					// Obtener el rectángulo de cada disparo
					FloatRect disparoRect = jugador->getDisparosPool()[i]->bounds();

					// Detectar colisiones 
					if ((boss->estaActivo()) && (boss->Colision(disparoRect))) {
						// Desactivar el disparo
						jugador->getDisparosPool()[i]->desactivar();

						//posicion del impacto
						posicionExplosion = boss->getSpriteBoss()->getPosition();
						explSprite->setPosition(posicionExplosion);
						explosionActiva = true;
						//restar una vida a boss
						int nuevaVida = boss->obtenerVida();
						nuevaVida -= 1;
						boss->modificarVida(nuevaVida);
						//controlar por consola
						std::cout << "Vida actual del Boss: " << boss->obtenerVida() << std::endl;
					}
				}
			}
		

}

void Juego::colisiones_misiles_boss() {
	//comprobar las colisiones de los disparos con el boss
	for (int i = 0; i < jugador->getMaxMisiles(); ++i) {
		if (jugador->getMisilesPool()[i]->estaActivo()) {
			// Obtener el rectángulo de cada disparo
			FloatRect misilesRect = jugador->getMisilesPool()[i]->bounds();

			// Detectar colisiones 
			if ((boss->estaActivo()) && (boss->Colision(misilesRect))) {
				// Desactivar el disparo
				jugador->getMisilesPool()[i]->desactivar();

				//posicion del impacto
				posicionExplosion = boss->getSpriteBoss()->getPosition();
				explSprite->setPosition(posicionExplosion);
				explosionActiva = true;
				//restar una vida a boss
				int nuevaVida = boss->obtenerVida();
				nuevaVida -= 10;
				boss->modificarVida(nuevaVida);
				//controlar por consola
				std::cout << "Vida actual del Boss: " << boss->obtenerVida() << std::endl;
			}
		}
	}


}


void Juego::dificultad() {
//condicionales para incrementar la dificultad aumentando la velocidad de los enemigos

	if (ptos >= 100) {

		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Establecer la nueva velocidadX
				enemigos[i]->setVelocidadX(4.5f);
			}
		}

	}

	if (ptos >= 200) {

		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Establecer la nueva velocidadX
				enemigos[i]->setVelocidadX(6.0f);
			}
		}

	}

	if (ptos >= 300) {

		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Establecer la nueva velocidadX
				enemigos[i]->setVelocidadX(7.5f);
			}
		}

	}
	// condicional para desactivar enemigos y activar al boss
	if (ptos >= 400) {

		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Establecer la nueva velocidadX
				enemigos[i]->desactivar();
			}
		}
	boss->activar();
	
	}


}