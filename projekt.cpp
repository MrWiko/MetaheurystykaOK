#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>


int main(){
    int m; // liczba procesorow / maszyn
    int n; // liczba procesow / zadan do wykonania
    int Cmax = 0;
    std::vector<int> p; // wektor czasu zadan
    
    std::ifstream plik("dane.txt");

    plik >> m;
    
    int nowe_zadanie;
    
    while(plik >> nowe_zadanie){
        p.push_back(nowe_zadanie);
    }

    plik.close();
    n = p.size();

    std::vector<int> czas_pracy(m,0);
    std::vector<int> indeksy_procesow(n,0);

    /*
    for(int i = 0; i < m; i++){
        czas_pracy[i] = 0;
    }

    for(int i = 0; i < n; i++){
        indeksy_procesow[i] = 0;
    }
    */
    
    for(int i = 0; i < n; i++){

    int minimalna_wartosc = INT_MAX;
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
        std::cout << "Czas pracy " << i + 1 << "-tego procesora: " << czas_pracy[i] << '\n';
        if(czas_pracy[i] > Cmax){
            Cmax = czas_pracy[i];
        }
    }
    
    std::cout << '\n' << "Czas Cmax = " << Cmax << '\n';
    return 0;
    }