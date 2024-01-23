#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class Misiles {
private:
    //Textura, sprite, velocidad y booleano para ver si est� activo
    Texture* textura;
    Sprite* sprite;
    Vector2f velocidad;
    bool activo;
    float aceleracion;


public:
    //constructor del disparo con posici�n inicial obtenida de Jugador
    Misiles(const Vector2f posicionInicial);


    //destructor de disparo
    ~Misiles();

    //actualizar movimiento
    void actualizar(float deltaTime);
    //actualizar movimiento boss
    void actualizarBoss(float deltaTime);
    //dibujar en ventana
    void Dibujar(RenderWindow* ventana1);
    //activar y desactivar disparo
    void activar();
    void desactivar();

    //obtener el rect�ngulo del sprite
    FloatRect bounds() const;

    //voltear sprite para el uso del Boss
    void voltear() {
        sprite->setScale(-2.0f, 2.0f);
    }

    //para devolver el estado activo a otras clases
    bool estaActivo() const {
        return activo;
    }


};