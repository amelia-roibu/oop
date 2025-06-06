#include <iostream>
#include "../include/jocViteza.h"
#include "../include/exception.h"
#include <../include/validareInput.h>

JocViteza::JocViteza() : Joc(), durataTimpSecunde(0) {};

JocViteza::JocViteza(const JocViteza &other)
    : Joc(other),
      durataTimpSecunde(other.durataTimpSecunde),
      startTimp(other.startTimp),
      raspunsuriGhicite(other.raspunsuriGhicite),
      raspunsuriPierdute(other.raspunsuriPierdute),
      obiecteFolosite(other.obiecteFolosite) {
}

JocViteza& JocViteza::operator=(const JocViteza& other) {
    if (this == &other)
        return *this;
    Joc::operator =(other);
    durataTimpSecunde = other.durataTimpSecunde;
    startTimp = other.startTimp;
    raspunsuriGhicite = other.raspunsuriGhicite;
    raspunsuriPierdute = other.raspunsuriPierdute;
    obiecteFolosite = other.obiecteFolosite;
    return *this;
}

int JocViteza::getScor() {
    return scorLocal;
}

void JocViteza::seteazaTimp() {
    std::cout << "Alege durata de timp:\n 0. 30 secunde\n 1. 1 minut\n 2. 1 minut si 30 de secunde\n 3. 2 minute\n 4. 2 minute si 30 de secunde\n 5. 3 minute\n";
    int optiune = ValidareInput<int>::citesteValoare(0, 5);
    switch (optiune) {
        case 0:
            durataTimpSecunde = 30;
            break;
        case 1:
            durataTimpSecunde = 60;
            break;
        case 2:
            durataTimpSecunde = 90;
            break;
        case 3:
            durataTimpSecunde = 120;
            break;
        case 4:
            durataTimpSecunde = 150;
            break;
        case 5:
            durataTimpSecunde = 180;
            break;
        }
    }

bool JocViteza::timpExpirat() const {
    auto acum = std::chrono::steady_clock::now();
    auto timpTrecut = std::chrono::duration_cast<std::chrono::seconds>(acum - startTimp).count();

    if (timpTrecut >= durataTimpSecunde) {
        return true;
    }
    return false;
}

void JocViteza::afisareTimpRamas() const {
    auto acum = std::chrono::steady_clock::now();
    auto timpTrecut = std::chrono::duration_cast<std::chrono::seconds>(acum - startTimp).count();
    std::cout << "Timp ramas: " << durataTimpSecunde - timpTrecut << " secunde.\n";
}

void JocViteza::afisareDateRaspuns() {
    std::cout << "In final, statisticile sunt:\n";
    std::cout << "\nScor acumulat: " << scorLocal << '\n';

    std::cout << "\nRaspunsuri corecte:\n";
    for (const auto& raspuns : raspunsuriGhicite)
        std::cout << raspuns << "; ";
    std::cout << '\n';

    std::cout << "\nRaspunsurile pentru intrebarile la care ai dat pas:\n";
    for (const auto& raspuns : raspunsuriPierdute)
        std::cout << raspuns << "; ";
    std::cout << "\n\n";
    raspunsuriGhicite.clear();
    raspunsuriPierdute.clear();
}

void JocViteza::stopTime() {
    end_time = std::chrono::steady_clock::now();
    auto durata = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    durata_totala += durata;
}

void JocViteza::porneste() {
    scorLocal = 0;
    jocInDesfasurare = true;
    cresteContorJocuri();
    startTime();
    std::cout << "Bine ai venit in " << getNume() <<"!\n";
    afisareInstructiuni();
    seteazaTimp();
    continent = selectareContinent();

    std::cout << "Incepe jocul! Vei avea la dispozitie " << durataTimpSecunde << " de secunde. Mult succes!\n";
    startTimp = std::chrono::steady_clock::now();

    try {
        while (!timpExpirat() && jocInDesfasurare) {
            std::cout << "\n ============================= \n";
            gestioneazaIntrebare();
        }
    } catch (const ExceptieTimeoutUtilizator& e) {
        std::cout << e.what() << '\n';
    }

    stopTime();
    scorLocal = std::max(0, scorLocal);
    afisareDateRaspuns();
}

void JocViteza::gestioneazaIntrebare() {
    int nrIncercari = 1;
    auto [prompt, raspunsCorect] = genereazaIntrebareRaspuns();
    formateazaIntrebare(prompt);

    std::string input;

    afisareTimpRamas();
    std::getline(std::cin, input);
    if (timpExpirat()) throw ExceptieTimeoutUtilizator();

    if (input == "renunt") {
        raspunsuriPierdute.push_back(raspunsCorect);
        renunta();
        jocInDesfasurare = false;
        return;
    }
    if (input == "pas") {
        scorLocal -= 50;
        raspunsuriPierdute.push_back(raspunsCorect);
        return;
    }
    bool corect = verificaRaspuns(input, raspunsCorect);
    while (!corect) {
        if (timpExpirat()) throw ExceptieTimeoutUtilizator();
        std::cout << "Gresit! Incearca din nou sau scrie 'pas' daca vrei sa sari! (te va costa din puncte)\n";
        std::getline(std::cin, input);
        if (input == "pas") {
            scorLocal -= 20;
            raspunsuriPierdute.push_back(raspunsCorect);
            return;
        }
        if (input == "renunt") {
            raspunsuriPierdute.push_back(raspunsCorect);
            renunta();
            return;
        }
        nrIncercari++;
        corect = verificaRaspuns(input, raspunsCorect);
    }
    if (nrIncercari == 1) scorLocal += 100;
    else scorLocal = scorLocal + (100 - 5 * nrIncercari);
    raspunsuriGhicite.push_back(raspunsCorect);
}


void JocViteza::renunta() {
    std::cout << "Ai renuntat. \n";
    jocInDesfasurare = false;
}


JocViteza::~JocViteza() = default;
