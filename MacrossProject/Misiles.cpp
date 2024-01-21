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
    //la posición será obtenida de la clase jugador
    sprite->setPosition(posicionInicial);
    //para iniciarlo en falso
    activo = false;
    //la velocidad del disparo
    velocidad = Vector2f(1.0f, 0.0f);


}




//actualizar la posición del disparo
void Misiles::actualizar(float deltaTime) {
    if (activo) {
        sprite->move(velocidad * deltaTime);

        //condición para desactivar cuando sale de la pantalla
        Vector2f posicion = sprite->getPosition();
        if (posicion.x > 800) {
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

//para obtener el rectángulo del disparo en Juego
FloatRect Misiles::bounds() const {
    return sprite->getGlobalBounds();
}

//destructor de disparo
Misiles::~Misiles() {
    delete textura;
    delete sprite;
}