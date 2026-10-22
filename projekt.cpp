#include <iostream>
#include <algorithm>


int main(){
    int m = 5; // liczba procesorow / maszyn
    int n = 9; // liczba procesow / zadan do wykonania
    int p[] = {1,2,3,4,3,6,7,10,3}; // wektor czasu zadan
    
    int czas_pracy[m];
    int indeksy_procesow[n];

    for(int i = 0; i < m; i++){
        czas_pracy[i] = 0;
    }

    for(int i = 0; i < n; i++){
        indeksy_procesow[i] = 0;
    }

    
    for(int i = 0; i < n; i++){

    int minimalna_wartosc = 100;
    int minimalny_indeks;

    for(int j = 0; j < m; j++){
        if(czas_pracy[j] < minimalna_wartosc){
            minimalna_wartosc = czas_pracy[j];
            minimalny_indeks = j;
        }
    }

    czas_pracy[minimalny_indeks] = czas_pracy[minimalny_indeks] + p[i];
    indeksy_procesow[i] = minimalny_indeks;
    }


    for(int i = 0; i < m; i++){
        std::cout << czas_pracy[i] << '\n';
    }
    
    return 0;
    }