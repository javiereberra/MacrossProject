#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Disparo {
private:
    //Textura, sprite, velocidad y booleano para ver si está activo
    Texture* textura;
    Sprite* sprite;
    Vector2f velocidad;
    bool activo;


public:
    //constructor del disparo con posición inicial obtenida de Jugador
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

    //obtener el rectángulo del sprite
    FloatRect bounds() const;

    //para devolver el estado activo a otras clases
    bool estaActivo() const {
        return activo;
    }
};