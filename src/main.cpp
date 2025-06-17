#include <iostream>
#include "sudoku.h"

int main() {
    int dificultad = 0;
    std::cout << "Selecciona la dificultad del Sudoku:\n";
    std::cout << "1. Facil\n2. Medio\n3. Dificil\nOpcion: ";
    std::cin >> dificultad;
    if (dificultad < 1 || dificultad > 3) dificultad = 1;
    Sudoku sudoku(dificultad);
    sudoku.jugar();
    return 0;
}
