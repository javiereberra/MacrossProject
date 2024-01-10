#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Disparo.h"

using namespace sf;

Disparo::Disparo(const Vector2f posicionInicial) {
    textura = new Texture;
    sprite = new Sprite;
    textura->loadFromFile("ruta/de/la/textura.png");
    sprite->setTexture(*textura);
    sprite->setPosition(posicionInicial);
    activo = false;
    velocidad = Vector2f(5.0f, 0.0f);


}

void Disparo::actualizar(float deltaTime) {
    if (activo) {
        sprite->move(velocidad * deltaTime);
        
    }
}

void Disparo::Dibujar(RenderWindow* ventana1) {

    ventana1->draw(*sprite);

}

void Disparo::activar() {
    activo = true;
}

void Disparo::desactivar() {
    activo = false;
}

FloatRect Disparo::getGlobalBounds() const {
    return sprite->getGlobalBounds();
}


Disparo::~Disparo() {
    delete textura;
    delete sprite;
}