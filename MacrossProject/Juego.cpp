﻿#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
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
	fondo->setScale(2.0f, 2.0f);


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


	//fuente
	fuente = new Font;

	//textos para el menú de inicio
	menu = new Text;
	fuente->loadFromFile("assets/arial.ttf");
	menu->setFont(*fuente);
	menu->setString("PRESIONA 'S' PARA COMENZAR");
	menu->setCharacterSize(15);
	menu->setPosition(290, 400);

	instrucc = new Text;
	instrucc->setFont(*fuente);
	instrucc->setString("PRESIONA 'ARRIBA, ABAJO, IZQUIERDA, DERECHA' PARA MOVERTE");
	instrucc->setCharacterSize(15);
	instrucc->setPosition(180, 430);

	instrucc2 = new Text;
	instrucc2->setFont(*fuente);
	instrucc2->setString("PRESIONA 'SPACE' PARA DISPARAR Y 'CONTROL' PARA MISIL");
	instrucc2->setCharacterSize(15);
	instrucc2->setPosition(200, 460);

	instrucc3 = new Text;
	instrucc3->setFont(*fuente);
	instrucc3->setString("DERROTA AL BOSS PARA GANAR");
	instrucc3->setCharacterSize(15);
	instrucc3->setPosition(290, 490);


	//texturas y sprite de menu fin del juego
	textura4 = new Texture;
	fondoGameOver = new Sprite;
	textura4->loadFromFile("assets/gameover.jpg");
	fondoGameOver->setTexture(*textura4);

	//cargar texturas de explosion
	for (int i = 0; i < 3; ++i) {
		explosionFrames[i] = new Texture;
		explosionFrames[i]->loadFromFile("assets/explosion_frame_" + to_string(i) + ".png");
	}
	//cargar la textura inicial del sprite
	explosionAnimation.setTexture(*explosionFrames[0]);

	//textos para gameover (puntuación y reiniciar el juego)
	finDelJuego = new Text;
	finDelJuego->setFont(*fuente);
	finDelJuego->setString("FINAL DEL JUEGO, TU PUNTUACIÓN ES:" + to_string(ptos));
	finDelJuego->setCharacterSize(15);
	finDelJuego->setPosition(260, 400);

	
	restart = new Text;
	restart->setFont(*fuente);
	restart->setString("PRESIONA 'R' PARA EL MENU INICIAL");
	restart->setCharacterSize(15);
	restart->setPosition(270, 450);


	//sonidos fx de disparos, misiles y explosiones
	disparoBff = new SoundBuffer;
	disparoBff->loadFromFile("assets/shoot.wav");
	disparoSnd = new Sound;
	disparoSnd->setBuffer(*disparoBff);
	disparoSnd->setVolume(25.0f);

	misileBff = new SoundBuffer;
	misileBff->loadFromFile("assets/misile.wav");
	misileSnd = new Sound;
	misileSnd->setBuffer(*misileBff);
	misileSnd->setVolume(25.0f);

	explosionBff = new SoundBuffer;
	explosionBff->loadFromFile("assets/explosion.wav");
	explosionSnd = new Sound;
	explosionSnd->setBuffer(*explosionBff);
	explosionSnd->setVolume(15.0f);

	//musicas de menu inicio, gameloop y gameover
	intro.openFromFile("assets/intro.ogg");
	intro.setVolume(20);
	intro.setLoop(true);
	game.openFromFile("assets/game.ogg");
	game.setVolume(20);
	game.setLoop(true);
	end.openFromFile("assets/end.ogg");
	end.setVolume(20);
	
	

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

	//booleandos para gestionar transciciones entre el menú, el juego y el gameover
	start = false;
	jugando = false;

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

	//setear el contador del último disparo en 0
	ultimoDisparo = 0.0f;
	ultimoMisil = 0.0f;

	//contador para la explosion y duración de cada frame de la animación
	explosionTime = 0.0f;
	explosionFrameDuration = 2.5f;

	
}

//metodo para iniciar un menu simple antes de iniciar el juego
void Juego::ejecutar() {

	intro.play();
	
	while (ventana1->isOpen()) {
		Event evento;
		while (ventana1->pollEvent(evento)) {
			if (evento.type == Event::Closed)
				ventana1->close();
			
			//Presionar "s" para iniciar el gameloop
			else if (evento.type == Event::KeyPressed) {
				if (evento.key.code == Keyboard::Key::S && !start) {

					start = true;
					jugando = true;
					
					intro.stop();
					
				}
				
				
			}
		}
		
	

		ventana1->clear(Color::Black);

		if (jugando) {
			//iniciar el loop si start es true
			gameLoop();
			intro.play();
		}
		else {
			if (start){
				gameOver();
				
				
		}
			else {
				//Menu de fondo si start es false
				ventana1->draw(*fondoMenu);
				ventana1->draw(*menu);
				ventana1->draw(*instrucc);
				ventana1->draw(*instrucc2);
				ventana1->draw(*instrucc3);

			}
		}

		ventana1->display();
		
	}
}

//el loop del juego iniciado, procesando eventos, actualizando moviemientos y dibujando todo
void Juego::gameLoop() {
	game.play();
	while (ventana1->isOpen() && jugando) {
		
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
		// Presionar SPACE para disparar y reproducir el sonido
		if (evento1.key.code == Keyboard::Key::Space) {
			jugador->disparar();	
			disparoSnd->play();
			

		}
		// Presionar CONTROL IZQ para misiles y reproducir el sonido
		else if (evento1.key.code == Keyboard::Key::LControl) {
			jugador->lanzarMisiles();
			misileSnd->play();
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
	//actualizar el comportamiento del boss si está activo
	if (boss->estaActivo()) {
		boss->Actualizar(deltaTime);
	}

	// actualizar los disparos del jugador
	jugador->gestionarDisparos(deltaTime);

	// actualizar los misiles del jugador
	jugador->gestionarMisiles(deltaTime);

	//DISPARO AUTOMATICO DEL BOSS
	//iniciar el contador del último disparo
	ultimoDisparo += deltaTime;
	if (boss->estaActivo()) {
		// cuando el contador supera el intervalo se activa
		if (ultimoDisparo >= intervaloDisparo) {
			// Dispara, se reinicia el contador y reproduce el sonido
			ultimoDisparo = 0.0f;
			boss->disparar();
			disparoSnd->play();
			
			
		}
	}
	// actualizar los disparos
	boss->gestionarDisparos(deltaTime);
	

	//MISILES AUTOMATICOS DEL BOSS
	//iniciar el contador del último misil
	ultimoMisil += deltaTime;
	if (boss->estaActivo()) {
		//cuando el contador supera el intervalo se activa
		if (ultimoMisil >= intervaloMisiles) {
			// Dispara, se reinicia el contador y reproduce el sonido
			ultimoMisil = 0.0f;
			boss->lanzarMisiles();
			misileSnd->play();
		

			
			
			
		}
		
	}
	//alctualizar el movimiento
	boss->gestionarMisiles(deltaTime);

	//detectar las colisiones	
	detectar_colisiones();

	//actualizar la animación de la explosion
	explosionAnimada();

	//actualizar la dificultad
	dificultad();


	//Si las vidas del jugador llegan a 0, jugando false y se activa el gameover
	if (vidas <= 0) {
		jugando = false;
		
		
	}
	//Si las vidas del boss llegan a 0, jugando false y se activa el gameover
	if (boss->obtenerVida() <= 0) {
		ptos += 600;
		puntajeText->setString("SCORE: " + to_string(ptos));
		jugando = false;
				
	}

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

	//dibujar disparos del jugador
	jugador->dibujarDisparos(ventana1);
	//dibujar misiles del jugador
	jugador->dibujarMisiles(ventana1);

	//dibujar disparos de boss
	boss->dibujarDisparos(ventana1);
	//dibujar misiles de boss
	boss->dibujarMisiles(ventana1);
	
	
	//dibujar los puntaje y las vidas
	ventana1->draw(*puntajeText);
	ventana1->draw(*vidasText);
	ventana1->draw(*vidasSprite);

	//dibujar las explosiones en caso de haberlas
	if (explosionActiva) {
		ventana1->draw(explosionAnimation);
		explosionSnd->play();
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
	colisiones_jugador_boss();
	colisiones_jugador_disparos();
	colisiones_jugador_misiles();


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
					explosionAnimation.setPosition(posicionExplosion);

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

void Juego::colisiones_jugador_boss() {
	//sprite para obtener el sprite de jugador
	Sprite* spriteNave = jugador->getSpriteNaveJugador();


	//obtener el rectangulo del sprite de jugador
	if (spriteNave) {
		FloatRect jugadorRect = spriteNave->getGlobalBounds();

		//si el boss está activo, obtener el sprite y obtener el rectángulo
		if (boss->estaActivo()) {
			Sprite* spriteBoss = boss->getSpriteBoss();
			FloatRect bossRect = spriteBoss->getGlobalBounds();
			//comprobar la colisión entre ambos rectángulos
			if (jugadorRect.intersects(bossRect)) {
				//restar vida y generar explosión
				vidas -= 1;
				vidasText->setString(to_string(vidas));
				posicionExplosion = spriteNave->getPosition();
				explosionAnimation.setPosition(posicionExplosion);
				explosionActiva = true;
			}


		}
		
		}
	
}
void Juego::colisiones_jugador_disparos() {
	//sprite para obtener el sprite de jugador
	Sprite* spriteNave = jugador->getSpriteNaveJugador();
	//obtener el rectangulo del sprite de jugador
	if (spriteNave) {
		FloatRect jugadorRect = spriteNave->getGlobalBounds();
		for (int i = 0; i < boss->getMaxDisparos(); ++i) {
			if (boss->getDisparosPool()[i]->estaActivo()) {
				// Obtener el rectángulo de cada disparo
				FloatRect disparoRect = boss->getDisparosPool()[i]->bounds();
				if (jugadorRect.intersects(disparoRect)) {
					// Desactivar el disparo
					boss->getDisparosPool()[i]->desactivar();
					vidas -= 1;
					vidasText->setString(to_string(vidas));
					// Ajustar la posición de la explosión a la posición del enemigo colisionado
					posicionExplosion = spriteNave->getPosition();
					explosionAnimation.setPosition(posicionExplosion);

					// Activar la explosión
					explosionActiva = true;

				}
			}
		}
	}
}

void Juego::colisiones_jugador_misiles() {
	//sprite para obtener el sprite de jugador
	Sprite* spriteNave = jugador->getSpriteNaveJugador();
	//obtener el rectangulo del sprite de jugador
	if (spriteNave) {
		FloatRect jugadorRect = spriteNave->getGlobalBounds();
		for (int i = 0; i < boss->getMaxMisiles(); ++i) {
			if (boss->getMisilesPool()[i]->estaActivo()) {
				// Obtener el rectángulo de cada misil
				FloatRect misilesRect = boss->getMisilesPool()[i]->bounds();
				if (jugadorRect.intersects(misilesRect)) {
					// Desactivar el misil
					boss->getMisilesPool()[i]->desactivar();
					vidas -= 3;
					vidasText->setString(to_string(vidas));
					// Ajustar la posición de la explosión a la posición del enemigo colisionado
					posicionExplosion = spriteNave->getPosition();
					explosionAnimation.setPosition(posicionExplosion);

					// Activar la explosión
					explosionActiva = true;



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
			//obtener los disparos activos
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
						explosionAnimation.setPosition(posicionExplosion);

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
						explosionAnimation.setPosition(posicionExplosion);

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
						explosionAnimation.setPosition(posicionExplosion);
						explosionActiva = true;
						//restar una vida a boss
						int nuevaVida = boss->obtenerVida();
						nuevaVida -= 1;
						boss->modificarVida(nuevaVida);
						
					}
				}
			}
	

}

void Juego::colisiones_misiles_boss() {
	//comprobar las colisiones de los misiles con el boss
	for (int i = 0; i < jugador->getMaxMisiles(); ++i) {
		if (jugador->getMisilesPool()[i]->estaActivo()) {
			// Obtener el rectángulo de cada misil
			FloatRect misilesRect = jugador->getMisilesPool()[i]->bounds();

			// Detectar colisiones 
			if ((boss->estaActivo()) && (boss->Colision(misilesRect))) {
				// Desactivar el misil
				jugador->getMisilesPool()[i]->desactivar();

				//posicion del impacto
				posicionExplosion = boss->getSpriteBoss()->getPosition();
				explosionAnimation.setPosition(posicionExplosion);
				explosionActiva = true;
				//restar diez vidas al boss
				int nuevaVida = boss->obtenerVida();
				nuevaVida -= 10;
				boss->modificarVida(nuevaVida);
				
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
				enemigos[i]->setVelocidadX(4.0f);
			}
		}

	}

	if (ptos >= 200) {

		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Establecer la nueva velocidadX
				enemigos[i]->setVelocidadX(5.0f);
			}
		}

	}

	if (ptos >= 300) {

		for (int i = 0; i < 5; ++i) {
			if (enemigos[i] && enemigos[i]->estaActivo()) {
				// Establecer la nueva velocidadX
				enemigos[i]->setVelocidadX(6.0f);
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
//metodo para reiniciar las posiciones del jugador, enemigos y boss
//desactivar disparos y misiles, reiniciar vidas y puntajes
void Juego::reiniciar() {

	
	
	//Reiniciar posición del jugador
	jugador->setPosition(Vector2f(100.0f, 300.0));
	//Desactivar disparos de jugador
	for (int i = 0; i < jugador->getMaxDisparos(); ++i) {
		if (jugador->getDisparosPool()[i]->estaActivo()) {
			jugador->getDisparosPool()[i]->desactivar();
		}
	}
	//Desactivar misiles de jugador
	for (int i = 0; i < jugador->getMaxMisiles(); ++i) {
		if (jugador->getMisilesPool()[i]->estaActivo()) {
			jugador->getMisilesPool()[i]->desactivar();
		}
	}
	//Reiniciar posición del boss
	boss->setPosition(Vector2f(850.0f, 300.0f));
	//Desactivar disparos Boss
	for (int i = 0; i < boss->getMaxDisparos(); ++i) {
		if (boss->getDisparosPool()[i]->estaActivo()) {
			boss->getDisparosPool()[i]->desactivar();
		}
	}
	//Desactivar misiles de boss
	for (int i = 0; i < boss->getMaxMisiles(); ++i) {
		if (boss->getMisilesPool()[i]->estaActivo()) {
			boss->getMisilesPool()[i]->desactivar();
		}
	}

	//Desactivar explosiones
	explosionActiva = false;

	//Reiniciar posiciones del pool de enemigos
	for (int i = 0; i < 5; ++i) {
		enemigos[i]->activar();
	}

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

	// Restablecer vida y puntaje
	vidas = 3;
	ptos = 0;
	puntajeText->setString("SCORE: " + to_string(ptos));
	vidasText->setString(to_string(vidas));
	//Reiniciar el fondo
	fondo->setPosition(0, 0);

	//desactivar boss si está activo
	if (boss->estaActivo()) {
		boss->desactivar();
	}	
	//reiniciar la vida del boss
	int nuevaVida = boss->obtenerVida();
	nuevaVida = 100;
	boss->modificarVida(nuevaVida);

	jugando = false;
	start = false;
	

}
//método para la pantalla gameOver tanto cuando pierda
//como cuando derrote al boss
void Juego::gameOver() {
		
	//detener canciones y reproducir musica de fin de juego
	end.play();		
	intro.stop();
	game.stop();
		
	//dibujar fondo y texto de gameover
	ventana1->draw(*fondoGameOver);
	finDelJuego->setString("FINAL DEL JUEGO, TU PUNTUACIÓN ES:" + to_string(ptos));
	ventana1->draw(*finDelJuego);
	ventana1->draw(*restart);
	ventana1->display();  // Mostrar los elementos renderizados
	
	//booleano para detectar si se presionó REINICIAR
	bool reiniciarPresionado = false;

	//detectar eventos para reiniciar
	while (ventana1->isOpen() && !reiniciarPresionado) {
		Event evento;
		if (ventana1->pollEvent(evento)) {
			if (evento.type == Event::Closed) {
				ventana1->close();
			}
			else if (evento.type == Event::KeyPressed) {
				if (evento.key.code == Keyboard::Key::R) {
					reiniciarPresionado = true;
				}
			}
		}
	}
	//si reiniciar es presionado, se activa el metodo reiniciar, detiene musica e inicia musica de inicio
	if (reiniciarPresionado) {
		reiniciar();
		end.stop();
		intro.play();
	}
}
//metodo para la animación de la explosión
void Juego::explosionAnimada(){
		

	if (explosionActiva) { // Actualizar el tiempo de la explosión
		explosionTime += deltaTime;

		// el frame actual es igual a la division entre el contador y la duración de los frames
		//pasado a un número entero
		int currentFrame = static_cast<int>(explosionTime / explosionFrameDuration);
		if (currentFrame < 3) {
			explosionAnimation.setTexture(*explosionFrames[currentFrame]);
		}
		else {
			explosionActiva = false;
			explosionTime = 0.0f;
		}
	}
}

//liberar memoria de las instancias
Juego::~Juego() {

	delete boss;
	delete enemigos;
	delete jugador;

}