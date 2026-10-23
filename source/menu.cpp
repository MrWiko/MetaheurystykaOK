#include "menu.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <random>

const std::string HELP_MESSAGE = "Dostepne komendy:\n"
                             "Exit - Wyjscie z programu\n"
                             "Pomoc - Wyswietl liste komend\n"
                             "Wczytaj - Wczytaj dane problemu Pcmax z klawiatury\n"
                             "WczytajPlik - Wczytaj dane z pliku\n"
                             "Generuj - Wygeneruj losowa instancje problemu Pcmax\n"
                             "Wyswietl - Wyswietl aktualne dane\n"
                             "Zachlanny - Uruchom algorytm zachlanny dla Pcmax\n"
                             "Wizualizuj - Wyswietl graficzna wizualizacje ostatniego wyniku\n"; 

Menu::Menu(message& msg){
    #ifdef DEBUG
        std::cout<<"Menu constructor called"<<std::endl;
    #endif
    messageParser = &msg;
}

Menu::~Menu() {
    #ifdef DEBUG
        std::cout<<"Menu destructor called"<<std::endl;
    #endif
}

int64_t Menu::InputNumData(std::string message, int64_t left, int64_t right, int64_t default_num ) {
    int64_t num = default_num;
    while (num == default_num) {
        std::cout<<message+">";
        if (messageParser->isTokenQueueEmpty()) {
            messageParser->getInputStdin();
        }
        Token token = messageParser->getToken();
        try{
            size_t count;
            num = std::stoll(token.token, &count);
            if (count != token.token.length()) throw std::invalid_argument("Invalid argument");
           // num = static_cast<float>(conn) / 100.0f; // Assuming the input is a percentage
            if (num <= left || num > right) {
                throw std::out_of_range("Input out of range");
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout<<"Invalid argument."<<std::endl;
            num = default_num;
        }
        catch (const std::out_of_range& e) {
            std::cout<<"Number out of range."<<std::endl;
            num = default_num;
        }
    }
    return num;
}

double Menu::InputFloatData(std::string message, double left, double right, double default_num ) {
    double num = default_num;
    while (num == default_num) {
        std::cout<<"message>";
        if (messageParser->isTokenQueueEmpty()) {
            messageParser->getInputStdin();
        }
        Token token = messageParser->getToken();
        try{
            size_t count;
            num = std::stod(token.token, &count);
            if (count != token.token.length()) throw std::invalid_argument("Invalid argument");
           // num = static_cast<float>(conn) / 100.0f; // Assuming the input is a percentage
            if (num <= left || num > right) {
                throw std::out_of_range("Input out of range");
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout<<"Invalid argument."<<std::endl;
            num = default_num;
        }
        catch (const std::out_of_range& e) {
            std::cout<<"Number out of range."<<std::endl;
            num = default_num;
        }
    }
    return num;
}

int Menu::processIO() {
    #ifdef DEBUG
        std::cout<<"Menu processIO called"<<std::endl;
    #endif

    std::cout<<"akcja>";
    if (messageParser->isTokenQueueEmpty()) {
        messageParser->getInputStdin();
    }
    Token actionToken = messageParser->getToken();

    #ifdef DEBUG
        std::cout<<actionToken.token<<std::endl;
    #endif

    if (actionToken.token == "Exit") {
        std::cout<<"Wychodzenie z programu."<<std::endl;
        return 0;
    }
    else if (actionToken.token == "Pomoc") {
        std::cout<<HELP_MESSAGE;
    }
    else if (actionToken.token == "Wczytaj") {
        wczytajDane();
    }
    else if (actionToken.token == "WczytajPlik") {
        wczytajZPliku();
    }
    else if (actionToken.token == "Generuj") {
        generujDane();
    }
    else if (actionToken.token == "Wyswietl") {
        wyswietlDane();
    }
    else if (actionToken.token == "Zachlanny") {
        uruchomZachlanny();
    }
    else if (actionToken.token == "Wizualizuj") {
        wizualizujWynik();
    }
    else {
        std::cout<<"Nieznana komenda. Wpisz 'Help' aby zobaczyc liste komend."<<std::endl;
    }

    return 1; // kontynuuj przetwarzanie
}

// Wczytywanie danych problemu Pcmax z klawiatury
void Menu::wczytajDane() {
    m = InputNumData("Podaj liczbe maszyn (m)", 0, 1000000, 0);
    int n = InputNumData("Podaj liczbe zadan (n)", 0, 1000000, 0);

    p.clear();
    p.resize(n);

    std::cout << "Podaj czasy trwania zadan:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::string prompt = "Czas zadania " + std::to_string(i + 1);
        p[i] = InputNumData(prompt, -1, 1000000, -1);
    }

    std::cout << "Dane zostaly wczytane pomyslnie." << std::endl;
}

// Wczytywanie danych problemu Pcmax z pliku
// Format pliku: pierwsza linia - liczba maszyn (m), kolejne linie - czasy zadań
void Menu::wczytajZPliku() {
    std::cout << "Podaj sciezke do pliku>";
    if (messageParser->isTokenQueueEmpty()) {
        messageParser->getInputStdin();
    }
    Token token = messageParser->getToken();
    std::string sciezka = token.token;

    std::ifstream plik(sciezka);
    if (!plik.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku: " << sciezka << std::endl;
        return;
    }

    int wczytane_m;
    if (!(plik >> wczytane_m) || wczytane_m <= 0) {
        std::cout << "Blad: nieprawidlowa liczba maszyn w pliku." << std::endl;
        return;
    }
    int wczytane_z;
        if (!(plik >> wczytane_z) || wczytane_z <= 0) {
        std::cout << "Blad: nieprawidlowa liczba zadan w pliku." << std::endl;
        return;
    }

    std::vector<int> wczytane_p;
    int czas;
    while (plik >> czas) {
        if (czas <= 0) {
            std::cout << "Blad: nieprawidlowy czas zadania (" << czas << ") w pliku." << std::endl;
            return;
        }
        wczytane_p.push_back(czas);
    }

    if (wczytane_p.empty()) {
        std::cout << "Blad: nie znaleziono zadnych zadan w pliku." << std::endl;
        return;
    }

    m = wczytane_m;
    p = wczytane_p;
    maWynik = false;

    std::cout << "Wczytano dane z pliku: " << m << " maszyn, "
              << p.size() << " zadan." << std::endl;
}

// Generowanie losowej instancji problemu Pcmax
void Menu::generujDane() {
    m = InputNumData("Podaj liczbe maszyn (m)", 0, 1000000, 0);
    int n = InputNumData("Podaj liczbe zadan (n)", 0, 1000000, 0);
    int pmin = InputNumData("Minimalny czas zadania", 0, 1000000, 0);
    int pmax = InputNumData("Maksymalny czas zadania", pmin - 1, 1000000, pmin - 1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(pmin, pmax);

    p.clear();
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = dist(gen);
    }

    maWynik = false;

    std::cout << "Wygenerowano " << n << " zadan z czasami z zakresu ["
              << pmin << ", " << pmax << "]." << std::endl;
}

// Wyświetlanie aktualnych danych
void Menu::wyswietlDane() {
    if (m == 0 || p.empty()) {
        std::cout << "Brak danych. Uzyj komendy 'Wczytaj' aby wczytac dane." << std::endl;
        return;
    }

    std::cout << "Dane dla problemu PCmax:\n"; 
    std::cout << m << std::endl;
    std::cout << p.size() << std::endl;
    for (size_t i = 0; i < p.size(); i++) 
        std::cout << p[i] << std::endl;
    
}

// Uruchomienie algorytmu zachłannego i wyświetlenie wyniku
void Menu::uruchomZachlanny() {
    if (m == 0 || p.empty()) {
        std::cout << "Brak danych. Uzyj komendy 'Wczytaj' aby wczytac dane." << std::endl;
        return;
    }

    // Wywołanie algorytmu zachłannego z namespace algosPcmax
    algosPcmax::Wynik wynik = algosPcmax::zachlanny(m, p);

    // Zapisanie wyniku do wizualizacji
    ostatniWynik = wynik;
    maWynik = true;

    // Wyświetlenie wyników
    std::cout << "\n=== Wynik algorytmu zachlannego ===" << std::endl;
    std::cout << "Cmax (makespan): " << wynik.cmax << std::endl;
    std::cout << "\nObciazenie maszyn:" << std::endl;
    for (int i = 0; i < m; i++) {
        std::cout << "  Maszyna " << i + 1 << ": " << wynik.czas_pracy[i] << std::endl;
    }
    std::cout << "\nPrzydzial zadan:" << std::endl;
    for (size_t i = 0; i < p.size(); i++) {
        std::cout << "  Zadanie " << i + 1 << " (czas=" << p[i]
                  << ") -> Maszyna " << wynik.przydzial_zadan[i] + 1 << std::endl;
    }
    std::cout << "==================================\n" << std::endl;
}

// Wizualizacja wyniku jako wykres Gantta w terminalu
void Menu::wizualizujWynik() {
    if (!maWynik) {
        std::cout << "Brak wyniku do wizualizacji. Najpierw uruchom algorytm (np. 'Zachlanny')." << std::endl;
        return;
    }

    // Zbierz zadania dla każdej maszyny z ich pozycjami czasowymi
    // Struktura: maszyna -> lista (start, czas, numer_zadania)
    struct ZadanieNaMaszynie {
        int start;
        int czas;
        int numer; // numer zadania (1-indexed)
    };

    std::vector<std::vector<ZadanieNaMaszynie>> maszyny(m);

    // Odtwórz harmonogram: zadania przydzielane w kolejności, kumulując czas
    std::vector<int> aktualny_czas(m, 0);
    for (size_t i = 0; i < p.size(); i++) {
        int masz = ostatniWynik.przydzial_zadan[i];
        ZadanieNaMaszynie z;
        z.start = aktualny_czas[masz];
        z.czas = p[i];
        z.numer = i + 1;
        maszyny[masz].push_back(z);
        aktualny_czas[masz] += p[i];
    }

    int cmax = ostatniWynik.cmax;
    if (cmax == 0) {
        std::cout << "Cmax = 0, brak czego wizualizowac." << std::endl;
        return;
    }

    // Szerokość wykresu w znakach (dopasowanie do terminala)
    const int SZEROKOSC = 60;

    // Kolory ANSI do rozróżniania zadań
    const std::string kolory[] = {
        "\033[41m", // czerwony
        "\033[42m", // zielony
        "\033[43m", // żółty
        "\033[44m", // niebieski
        "\033[45m", // magenta
        "\033[46m", // cyjan
        "\033[47m", // biały
        "\033[100m", // jasny czarny
        "\033[101m", // jasny czerwony
        "\033[102m", // jasny zielony
        "\033[103m", // jasny żółty
        "\033[104m", // jasny niebieski
    };
    const std::string reset = "\033[0m";
    const int LICZBA_KOLOROW = 12;

    std::cout << "\n╔══════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║             WYKRES GANTTA - WIZUALIZACJA ROZWIAZANIA                ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════════╝\n" << std::endl;

    // Etykieta osi czasu (nagłówek)
    std::cout << "            ";
    // Oś czasu: oznaczenia co ~10 znaków
    for (int i = 0; i <= SZEROKOSC; i += 10) {
        int wartosc = (int)((double)i / SZEROKOSC * cmax);
        std::string label = std::to_string(wartosc);
        std::cout << label;
        // Dopełnij spacjami do 10 znaków
        int padding = 10 - (int)label.length();
        if (i + 10 <= SZEROKOSC) {
            for (int s = 0; s < padding; s++) std::cout << " ";
        }
    }
    std::cout << std::endl;

    // Linia górna
    std::cout << "            ┌";
    for (int i = 0; i < SZEROKOSC; i++) std::cout << "─";
    std::cout << "┐" << std::endl;

    // Rysowanie paska dla każdej maszyny
    for (int i = 0; i < m; i++) {
        // Etykieta maszyny
        std::ostringstream label;
        label << " Maszyna " << std::setw(2) << (i + 1) << " │";
        std::cout << label.str();

        // Tworzenie paska znakowego
        std::vector<std::string> pasek(SZEROKOSC, " ");
        std::vector<std::string> kolor_pasek(SZEROKOSC, "");
        std::vector<std::string> reset_pasek(SZEROKOSC, "");

        for (const auto& z : maszyny[i]) {
            int start_col = (int)((double)z.start / cmax * SZEROKOSC);
            int end_col = (int)((double)(z.start + z.czas) / cmax * SZEROKOSC);
            if (end_col > SZEROKOSC) end_col = SZEROKOSC;
            if (start_col >= SZEROKOSC) continue;

            std::string kolor = kolory[(z.numer - 1) % LICZBA_KOLOROW];

            // Etykieta zadania do wpisania w pasek
            std::string etykieta = "Z" + std::to_string(z.numer);
            int srodek = (start_col + end_col) / 2 - (int)etykieta.length() / 2;

            for (int c = start_col; c < end_col; c++) {
                kolor_pasek[c] = kolor;
                reset_pasek[c] = reset;

                // Wstaw etykietę na środku bloku
                int pos_in_label = c - srodek;
                if (pos_in_label >= 0 && pos_in_label < (int)etykieta.length()) {
                    pasek[c] = std::string(1, etykieta[pos_in_label]);
                } else {
                    pasek[c] = "░";
                }
            }
        }

        // Wypisz pasek
        for (int c = 0; c < SZEROKOSC; c++) {
            std::cout << kolor_pasek[c] << pasek[c] << reset_pasek[c];
        }
        std::cout << "│ " << ostatniWynik.czas_pracy[i] << std::endl;
    }

    // Linia dolna
    std::cout << "            └";
    for (int i = 0; i < SZEROKOSC; i++) std::cout << "─";
    std::cout << "┘" << std::endl;

    // Oś czasu (powtórzona na dole)
    std::cout << "            ";
    for (int i = 0; i <= SZEROKOSC; i += 10) {
        int wartosc = (int)((double)i / SZEROKOSC * cmax);
        std::string lab = std::to_string(wartosc);
        std::cout << lab;
        int padding = 10 - (int)lab.length();
        if (i + 10 <= SZEROKOSC) {
            for (int s = 0; s < padding; s++) std::cout << " ";
        }
    }
    std::cout << std::endl;

    // Legenda
    std::cout << "\n  Legenda: ";
    for (size_t i = 0; i < p.size(); i++) {
        std::string kolor = kolory[i % LICZBA_KOLOROW];
        std::cout << kolor << " Z" << (i + 1) << "=" << p[i] << " " << reset << " ";
        if ((i + 1) % 8 == 0 && i + 1 < p.size()) {
            std::cout << "\n           ";
        }
    }
    std::cout << std::endl;

    std::cout << "\n  Cmax (makespan) = " << ostatniWynik.cmax << std::endl;
    std::cout << std::endl;
}