#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Disparo.h"

using namespace sf;


//constructor para el disparo del jugador
Disparo::Disparo(const Vector2f posicionInicial) {
    //textura y sprite
    textura = new Texture;
    sprite = new Sprite;
    textura->loadFromFile("assets/shoot1.png");
    sprite->setTexture(*textura);
    //la posición será obtenida de la clase jugador
    sprite->setPosition(posicionInicial);
    //para iniciarlo en falso
    activo = false;
    //la velocidad del disparo
    velocidad = Vector2f(7.0f, 0.0f);


}


//actualizar la posición del disparo
void Disparo::actualizar(float deltaTime) {
    if (activo) {
        sprite->move(velocidad * deltaTime);
        
        //condición para desactivar cuando sale de la pantalla
        Vector2f posicion = sprite->getPosition();
        if (posicion.x > 800) {
            desactivar();
        }
    }
}

//actualizar la posición del disparo laser del boss
void Disparo::actualizarBoss(float deltaTime) {
    if (activo) {
        sprite->move(-velocidad * deltaTime);

        //condición para desactivar cuando sale de la pantalla
        Vector2f posicion = sprite->getPosition();
        if (posicion.x < 0) {
            desactivar();
        }
    }
}

//dibujar en ventana
void Disparo::Dibujar(RenderWindow* ventana1) {

    ventana1->draw(*sprite);

}

//para activar y desactivar el disparo
void Disparo::activar() {
    activo = true;
}

void Disparo::desactivar() {
    activo = false;
}

//para obtener el rectángulo del disparo en Juego
FloatRect Disparo::bounds() const {
    return sprite->getGlobalBounds();
}

//destructor de disparo
Disparo::~Disparo() {
    delete textura;
    delete sprite;
}

