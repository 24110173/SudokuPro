#include "sudoku.h"
#include <iostream>

Sudoku::Sudoku() {
    int temp[N][N] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c) {
            grid[r][c] = temp[r][c];
            fixed[r][c] = (temp[r][c] != 0);
        }
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
