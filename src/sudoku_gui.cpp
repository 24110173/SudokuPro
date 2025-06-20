#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

const std::string MENU_IMG = "Imagenes/Menu del sudoku.jpeg";
const std::string MODO_FACIL_IMG = "Imagenes/Modo facil.jpeg";
const std::string MODO_MEDIO_IMG = "Imagenes/Modo mediano.jpeg";
const std::string MODO_DIFICIL_IMG = "Imagenes/Modo dificil.jpeg";
const std::string TABLERO_IMG = "Imagenes/Tabla de Sudoku.jpeg";
const std::string NUM_IMG[9] = {
    "Imagenes/Numero 1.jpeg",
    "Imagenes/Numero 2.jpeg",
    "Imagenes/Numero 3.jpeg",
    "Imagenes/Numero 4.jpeg",
    "Imagenes/Numero 5.jpeg",
    "Imagenes/Numero 6.jpeg",
    "Imagenes/Numero 7.jpeg",
    "Imagenes/Numero 8.jpeg",
    "Imagenes/Numero 9.jpeg"
};

struct Celda {
    int valor; // 0 = vacía
    bool fija;
};

std::vector<std::vector<Celda>> generarTablero(int vacias) {
    std::vector<std::vector<Celda>> tablero(9, std::vector<Celda>(9, {0, false}));
    // Generar una solución simple (no única, solo para demo)
    int n = 1;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            tablero[i][j] = {((i*3 + i/3 + j)%9)+1, true};
    // Quitar celdas
    srand(time(0));
    for (int k = 0; k < vacias; ++k) {
        int i = rand()%9, j = rand()%9;
        tablero[i][j] = {0, false};
    }
    return tablero;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sudoku Interactivo");
    sf::Texture menuTexture, facilTexture, medioTexture, dificilTexture, tableroTexture;
    menuTexture.loadFromFile(MENU_IMG);
    facilTexture.loadFromFile(MODO_FACIL_IMG);
    medioTexture.loadFromFile(MODO_MEDIO_IMG);
    dificilTexture.loadFromFile(MODO_DIFICIL_IMG);
    tableroTexture.loadFromFile(TABLERO_IMG);
    sf::Sprite menuSprite(menuTexture);
    sf::Sprite facilSprite(facilTexture);
    sf::Sprite medioSprite(medioTexture);
    sf::Sprite dificilSprite(dificilTexture);
    sf::Sprite tableroSprite(tableroTexture);
    sf::Texture numTextures[9];
    sf::Sprite numSprites[9];
    for (int i = 0; i < 9; ++i) {
        numTextures[i].loadFromFile(NUM_IMG[i]);
        numSprites[i].setTexture(numTextures[i]);
        numSprites[i].setScale(0.15f, 0.15f);
        numSprites[i].setPosition(60 + i*80, 700);
    }
    menuSprite.setOrigin(menuTexture.getSize().x/2, menuTexture.getSize().y/2);
    menuSprite.setPosition(400, 480);
    facilSprite.setScale(0.6f, 0.6f);
    medioSprite.setScale(0.6f, 0.6f);
    dificilSprite.setScale(0.6f, 0.6f);
    float botonesY = 610 - 450 + 90; // 3 cm (aprox 90px) más abajo
    float espacioY = 180;
    float anchoFacil = facilSprite.getGlobalBounds().width;
    float anchoMedio = medioSprite.getGlobalBounds().width;
    float anchoDificil = dificilSprite.getGlobalBounds().width;
    facilSprite.setPosition(400 - anchoFacil/2, botonesY);
    medioSprite.setPosition(400 - anchoMedio/2, botonesY + espacioY);
    dificilSprite.setPosition(400 - anchoDificil/2, botonesY + 2*espacioY);
    tableroSprite.setScale(0.8f, 0.8f);
    tableroSprite.setPosition(80, 40);
    int estado = 0;
    int dificultad = 0;
    std::vector<std::vector<Celda>> tablero;
    int seleccionado = -1;
    int selFila = -1, selCol = -1;
    auto nuevoTablero = [&](int dif) {
        int vacias = 0;
        if (dif == 1) vacias = 30; // fácil
        else if (dif == 2) vacias = 45; // medio
        else if (dif == 3) vacias = 60; // difícil
        return generarTablero(vacias);
    };
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (estado == 0 && event.type == sf::Event::MouseButtonPressed) {
                auto x = event.mouseButton.x, y = event.mouseButton.y;
                if (facilSprite.getGlobalBounds().contains(x, y)) {
                    dificultad = 1; estado = 1;
                    tablero = nuevoTablero(dificultad);
                } else if (medioSprite.getGlobalBounds().contains(x, y)) {
                    dificultad = 2; estado = 1;
                    tablero = nuevoTablero(dificultad);
                } else if (dificilSprite.getGlobalBounds().contains(x, y)) {
                    dificultad = 3; estado = 1;
                    tablero = nuevoTablero(dificultad);
                }
            }
            if (estado == 1 && event.type == sf::Event::MouseButtonPressed) {
                auto x = event.mouseButton.x, y = event.mouseButton.y;
                if (y > 700 && y < 780) {
                    for (int i = 0; i < 9; ++i) {
                        if (numSprites[i].getGlobalBounds().contains(x, y)) seleccionado = i+1;
                    }
                } else if (x > 80 && x < 720 && y > 40 && y < 680) {
                    int col = (x-80)/71;
                    int fil = (y-40)/71;
                    if (!tablero[fil][col].fija) {
                        selFila = fil; selCol = col;
                        if (seleccionado > 0) {
                            tablero[fil][col].valor = seleccionado;
                            seleccionado = -1;
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        if (estado == 0) {
            window.draw(menuSprite);
            window.draw(facilSprite);
            window.draw(medioSprite);
            window.draw(dificilSprite);
        } else if (estado == 1) {
            window.draw(tableroSprite);
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (tablero[i][j].valor > 0) {
                        numSprites[tablero[i][j].valor-1].setPosition(80 + j*71, 40 + i*71);
                        window.draw(numSprites[tablero[i][j].valor-1]);
                        numSprites[tablero[i][j].valor-1].setPosition(60 + (tablero[i][j].valor-1)*80, 700);
                    }
                    if (i == selFila && j == selCol) {
                        sf::RectangleShape rect(sf::Vector2f(71,71));
                        rect.setPosition(80 + j*71, 40 + i*71);
                        rect.setFillColor(sf::Color(0,0,255,60));
                        window.draw(rect);
                    }
                }
            }
            for (int i = 0; i < 9; ++i) window.draw(numSprites[i]);
        }
        window.display();
    }
    return 0;
}
