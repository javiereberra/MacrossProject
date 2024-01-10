#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Disparo {
private:
    Texture* textura;
    Sprite* sprite;
    Vector2f velocidad;
    bool activo;

public:
    Disparo(const Vector2f posicionInicial);
    ~Disparo();

    void actualizar(float deltaTime);
    void Dibujar(RenderWindow* ventana1);
    void activar();
    void desactivar();

    FloatRect getGlobalBounds() const;
};