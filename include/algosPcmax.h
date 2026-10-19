#pragma once

#include <vector>
#include <iostream>

namespace algosPcmax {

    // Struktura przechowująca wynik algorytmu
    struct Wynik {
        std::vector<int> czas_pracy;       // czas pracy każdej maszyny
        std::vector<int> przydzial_zadan;  // indeks maszyny dla każdego zadania
        int cmax;                          // maksymalny czas (Cmax)
    };

    // Algorytm zachłanny dla problemu Pcmax
    // Przydziela zadania do maszyny o najmniejszym aktualnym obciążeniu
    Wynik zachlanny(int m, const std::vector<int>& p);

}