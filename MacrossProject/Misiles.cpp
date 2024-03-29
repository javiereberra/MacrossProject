#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Misiles.h"

using namespace sf;


//constructor para el disparo del jugador
Misiles::Misiles(const Vector2f posicionInicial) {
    //textura y sprite
    textura = new Texture;
    sprite = new Sprite;
    textura->loadFromFile("assets/misil1.png");
    sprite->setTexture(*textura);
    sprite->setScale(2.0f, 2.0f);
    //la posici�n ser� obtenida de la clase jugador
    sprite->setPosition(posicionInicial);
    //para iniciarlo en falso
    activo = false;
    //la velocidad del disparo
    velocidad = Vector2f(0.0f, 0.0f);
    aceleracion = 0.1f;


}




//actualizar la posici�n del disparo
void Misiles::actualizar(float deltaTime) {
    if (activo) {

        velocidad.x += aceleracion * deltaTime;


        sprite->move(velocidad * deltaTime);

        //condici�n para desactivar cuando sale de la pantalla
        Vector2f posicion = sprite->getPosition();
        if (posicion.x > 800) {
            desactivar();
        }
    }
}

//actualizar la posici�n de los misiles del boss
void Misiles::actualizarBoss(float deltaTime) {
    if (activo) {

        velocidad.x += aceleracion * deltaTime;


        sprite->move(-velocidad * deltaTime);

        //condici�n para desactivar cuando sale de la pantalla
        Vector2f posicion = sprite->getPosition();
        if (posicion.x < 0) {
            desactivar();
        }
    }
}
//dibujar en ventana
void Misiles::Dibujar(RenderWindow* ventana1) {

    ventana1->draw(*sprite);

}

//para activar y desactivar el disparo
void Misiles::activar() {
    activo = true;
}

void Misiles::desactivar() {
    activo = false;
}

//para obtener el rect�ngulo del disparo en Juego
FloatRect Misiles::bounds() const {
    return sprite->getGlobalBounds();
}

//destructor de disparo
Misiles::~Misiles() {
    delete textura;
    delete sprite;
}