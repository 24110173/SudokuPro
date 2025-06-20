#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

const std::string MENU_IMG = "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.55 PM.jpeg";
const std::string MODO_FACIL_IMG = "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.56 PM (1).jpeg";
const std::string MODO_MEDIO_IMG = "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.56 PM (2).jpeg";
const std::string MODO_DIFICIL_IMG = "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.56 PM (3).jpeg";
const std::string TABLERO_IMG = "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.56 PM (4).jpeg";
const std::string NUM_IMG[9] = {
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.57 PM.jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.57 PM (1).jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.57 PM (2).jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.57 PM (3).jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.57 PM (4).jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.32.30 PM.jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.32.31 PM.jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.32.31 PM (1).jpeg",
    "../Imagenes/WhatsApp Image 2025-06-19 at 10.30.56 PM.jpeg"
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku Interactivo");
    sf::Texture menuTexture, facilTexture, medioTexture, dificilTexture;
    menuTexture.loadFromFile(MENU_IMG);
    facilTexture.loadFromFile(MODO_FACIL_IMG);
    medioTexture.loadFromFile(MODO_MEDIO_IMG);
    dificilTexture.loadFromFile(MODO_DIFICIL_IMG);
    sf::Sprite menuSprite(menuTexture);
    sf::Sprite facilSprite(facilTexture);
    sf::Sprite medioSprite(medioTexture);
    sf::Sprite dificilSprite(dificilTexture);
    menuSprite.setPosition(100, 30);
    facilSprite.setPosition(200, 300);
    medioSprite.setPosition(350, 300);
    dificilSprite.setPosition(500, 300);
    int estado = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (estado == 0 && event.type == sf::Event::MouseButtonPressed) {
                auto x = event.mouseButton.x, y = event.mouseButton.y;
                if (facilSprite.getGlobalBounds().contains(x, y)) estado = 1;
                else if (medioSprite.getGlobalBounds().contains(x, y)) estado = 2;
                else if (dificilSprite.getGlobalBounds().contains(x, y)) estado = 3;
            }
        }
        window.clear(sf::Color::White);
        if (estado == 0) {
            window.draw(menuSprite);
            window.draw(facilSprite);
            window.draw(medioSprite);
            window.draw(dificilSprite);
        } else {
        }
        window.display();
    }
    return 0;
}
