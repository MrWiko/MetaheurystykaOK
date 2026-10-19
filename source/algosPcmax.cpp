#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "algosPcmax.h"

namespace algosPcmax {

    // Algorytm zachłanny (LPT - Longest Processing Time)
    // Przydziela każde zadanie do maszyny o najmniejszym aktualnym obciążeniu
    Wynik zachlanny(int m, const std::vector<int>& p) {
        int n = p.size(); // liczba zadań

        Wynik wynik;
        wynik.czas_pracy.resize(m, 0);        // inicjalizacja czasów pracy maszyn na 0
        wynik.przydzial_zadan.resize(n, 0);    // inicjalizacja przydziału zadań

        // Dla każdego zadania znajdź maszynę o najmniejszym obciążeniu
        for (int i = 0; i < n; i++) {
            int minimalna_wartosc = INT_MAX;
            int minimalny_indeks = 0;

            // Szukanie maszyny z minimalnym czasem pracy
            for (int j = 0; j < m; j++) {
                if (wynik.czas_pracy[j] < minimalna_wartosc) {
                    minimalna_wartosc = wynik.czas_pracy[j];
                    minimalny_indeks = j;
                }
            }

            // Przydziel zadanie do maszyny o najmniejszym obciążeniu
            wynik.czas_pracy[minimalny_indeks] += p[i];
            wynik.przydzial_zadan[i] = minimalny_indeks;
        }

        // Oblicz Cmax (maksymalny czas pracy wśród maszyn)
        wynik.cmax = *std::max_element(wynik.czas_pracy.begin(), wynik.czas_pracy.end());

        return wynik;
    }

}
