#ifndef SUDOKU_H
#define SUDOKU_H

const int N = 9;

class Sudoku {
public:
    Sudoku();
    void imprimir();
    bool esSeguro(int r, int c, int num);
    void entradaUsuario();
    void jugar();
private:
    int grid[N][N];
    bool fixed[N][N];
};

#endif // SUDOKU_H
