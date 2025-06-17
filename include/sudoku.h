#ifndef SUDOKU_H
#define SUDOKU_H
#include <random>

const int N = 9;

class Sudoku {
public:
    Sudoku(int dificultad = 1); // dificultad: 1=fácil, 2=medio, 3=difícil
    void imprimir();
    bool esSeguro(int r, int c, int num);
    void entradaUsuario();
    void jugar();
private:
    int grid[N][N];
    bool fixed[N][N];
    bool resolver(int g[N][N]);
    void generarTablero(int dificultad);
};

#endif // SUDOKU_H
