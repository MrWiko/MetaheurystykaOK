#pragma once
#include "message.h"
#include <iostream>
#include <vector>
#include "token-struct.h"
#include "algosPcmax.h"

class Menu {
    private:
        message *messageParser;
        bool initialized = false;
        int64_t InputNumData(std::string message, int64_t left, int64_t right, int64_t default_num);
        double InputFloatData(std::string message, double left, double right, double default_num);

        // Dane problemu Pcmax
        int m = 0;                 // liczba maszyn / procesorów
        std::vector<int> p;        // wektor czasów zadań

        // Ostatni wynik algorytmu
        algosPcmax::Wynik ostatniWynik;
        bool maWynik = false;      // czy jest zapisany wynik do wizualizacji

        // Metody pomocnicze
        void wczytajDane();        // wczytywanie danych z klawiatury
        void wyswietlDane();       // wyświetlanie aktualnych danych
        void uruchomZachlanny();   // uruchomienie algorytmu zachłannego
        void wizualizujWynik();    // wizualizacja wyniku jako wykres Gantta w terminalu

    public:
        Menu(message& msg);
        virtual ~Menu();
        
        int processIO();
      //  void displayMenu();

};