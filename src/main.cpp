#include <iostream>
#include "sudoku.h"

int main() {
    while (true) {
        int dificultad = 0;
        std::cout << "Selecciona la dificultad del Sudoku:\n";
        std::cout << "1. Facil\n2. Medio\n3. Dificil\n4. Salir\nOpcion: ";
        std::cin >> dificultad;
        if (dificultad == 4) break;
        if (dificultad < 1 || dificultad > 3) dificultad = 1;
        Sudoku sudoku(dificultad);
        sudoku.jugar();
    }
    std::cout << "Hasta luego!\n";
    return 0;
}
