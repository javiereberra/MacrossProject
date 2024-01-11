#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Disparo {
private:
    //Textura, sprite, velocidad y booleano para ver si est� activo
    Texture* textura;
    Sprite* sprite;
    Vector2f velocidad;
    bool activo;


public:
    //constructor del disparo con posici�n inicial obtenida de Jugador
    Disparo(const Vector2f posicionInicial);
    //destructor de disparo
    ~Disparo();

    //actualizar movimiento
    void actualizar(float deltaTime);
    //dibujar en ventana
    void Dibujar(RenderWindow* ventana1);
    //activar y desactivar disparo
    void activar();
    void desactivar();

    //obtener el rect�ngulo del sprite
    FloatRect bounds() const;

    //para devolver el estado activo a otras clases
    bool estaActivo() const {
        return activo;
    }
};