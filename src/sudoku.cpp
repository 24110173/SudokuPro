#include "sudoku.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

Sudoku::Sudoku(int dificultad) {
    generarTablero(dificultad);
}

bool Sudoku::resolver(int g[N][N]) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (g[r][c] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (esSeguroCelda(g, r, c, num)) {
                        g[r][c] = num;
                        if (resolver(g)) return true;
                        g[r][c] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::esSeguroCelda(int g[N][N], int r, int c, int num) {
    for (int x = 0; x < N; ++x)
        if (g[r][x] == num || g[x][c] == num) return false;
    int sr = r - r % 3, sc = c - c % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (g[sr + i][sc + j] == num) return false;
    return true;
}

void Sudoku::generarTablero(int dificultad) {
    // Generar tablero completo
    int temp[N][N] = {0};
    std::srand((unsigned)std::time(nullptr));
    std::vector<int> nums(N);
    for (int i = 0; i < N; ++i) nums[i] = i + 1;
    std::random_shuffle(nums.begin(), nums.end());
    for (int i = 0; i < N; ++i) temp[0][i] = nums[i];
    resolver(temp);
    // Copiar tablero resuelto
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            grid[r][c] = temp[r][c];
    // Quitar celdas según dificultad
    int vacias = dificultad == 1 ? 35 : (dificultad == 2 ? 45 : 55);
    while (vacias > 0) {
        int r = std::rand() % N;
        int c = std::rand() % N;
        if (grid[r][c] != 0) {
            grid[r][c] = 0;
            --vacias;
        }
    }
    // Marcar celdas fijas
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            fixed[r][c] = (grid[r][c] != 0);
}

void Sudoku::imprimir() {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            int v = grid[r][c];
            if (v == 0) {
                std::cout << ". ";
            } else {
                if (fixed[r][c]) {
                    std::cout << v << " ";
                } else {
                    bool correcto = true;
                    for (int i = 0; i < N; ++i)
                        if ((i != c && grid[r][i] == v) || (i != r && grid[i][c] == v))
                            correcto = false;
                    int sr = r - r % 3, sc = c - c % 3;
                    for (int i = 0; i < 3; ++i)
                        for (int j = 0; j < 3; ++j)
                            if ((sr + i != r || sc + j != c) && grid[sr + i][sc + j] == v)
                                correcto = false;
                    if (correcto)
                        std::cout << "\033[32m" << v << "\033[0m ";
                    else
                        std::cout << "\033[31m" << v << "\033[0m ";
                }
            }
        }
        std::cout << "\n";
    }
}

bool Sudoku::esSeguro(int r, int c, int num) {
    for (int x = 0; x < N; ++x)
        if (grid[r][x] == num || grid[x][c] == num) return false;
    int sr = r - r % 3, sc = c - c % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[sr + i][sc + j] == num) return false;
    return true;
}

void Sudoku::entradaUsuario() {
    int r, c, v;
    while (true) {
        imprimir();
        std::cout << "\nFila Columna Valor (0 0 0 para salir): ";
        std::cin >> r >> c >> v;
        if (r == 0 && c == 0 && v == 0) break;
        if (r < 1 || r > 9 || c < 1 || c > 9 || v < 1 || v > 9) {
            std::cout << "\033[31mEntrada fuera de rango\033[0m\n";
            continue;
        }
        if (fixed[r - 1][c - 1]) {
            std::cout << "\033[31mCelda bloqueada\033[0m\n";
            continue;
        }
        grid[r - 1][c - 1] = v;
    }
}

void Sudoku::jugar() {
    entradaUsuario();
}
