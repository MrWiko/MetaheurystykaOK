#include "menu.h"

const std::string HELP_MESSAGE = "Dostepne komendy:\n"
                             "Exit - Wyjscie z programu\n"
                             "Pomoc - Wyswietl liste komend\n"
                             "Wczytaj - Wczytaj dane problemu Pcmax z klawiatury\n"
                             "Wyswietl - Wyswietl aktualne dane\n"
                             "Zachlanny - Uruchom algorytm zachlanny dla Pcmax\n"; 

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
    else if (actionToken.token == "Wyswietl") {
        wyswietlDane();
    }
    else if (actionToken.token == "Zachlanny") {
        uruchomZachlanny();
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

// Wyświetlanie aktualnych danych
void Menu::wyswietlDane() {
    if (m == 0 || p.empty()) {
        std::cout << "Brak danych. Uzyj komendy 'Wczytaj' aby wczytac dane." << std::endl;
        return;
    }

    std::cout << "Liczba maszyn (m): " << m << std::endl;
    std::cout << "Liczba zadan (n): " << p.size() << std::endl;
    std::cout << "Czasy zadan: [";
    for (size_t i = 0; i < p.size(); i++) {
        std::cout << p[i];
        if (i < p.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Uruchomienie algorytmu zachłannego i wyświetlenie wyniku
void Menu::uruchomZachlanny() {
    if (m == 0 || p.empty()) {
        std::cout << "Brak danych. Uzyj komendy 'Wczytaj' aby wczytac dane." << std::endl;
        return;
    }

    // Wywołanie algorytmu zachłannego z namespace algosPcmax
    algosPcmax::Wynik wynik = algosPcmax::zachlanny(m, p);

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