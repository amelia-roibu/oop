#include <iostream>
#include "../include/jocViteza.h"
#include <../include/util.h>

JocViteza::JocViteza() : scorLocal(0), durataTimpSecunde(0), continent("") {};

int JocViteza::getScor() {
    return scorLocal;
}

void JocViteza::seteazaTimp() {
    std::cout << "Alege durata de timp:\n 0. 30 secunde\n 1. 1 minut\n 2. 1 minut si 30 de secunde\n 3. 2 minute\n 4. 2 minute si 30 de secunde\n 5. 3 minute\n";
    int optiune;
    do {
        std::cin >> optiune;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            default:
                std::cout << "Optiune invalida! Indearca din nou.\n";
                durataTimpSecunde = -1;
        }
    } while (durataTimpSecunde == -1);
}


bool JocViteza::timpExpirat() const {
    auto acum = std::chrono::steady_clock::now();
    auto timpTrecut = std::chrono::duration_cast<std::chrono::seconds>(acum - startTimp).count();

    if (timpTrecut >= durataTimpSecunde) {
        return true;
    }
    std::cout << "Timp ramas: " << durataTimpSecunde - timpTrecut << " secunde.\n";
    return false;
}

void JocViteza::afisareDateRaspuns() {
    std::cout << "In final, statisticile sunt:\n";
    std::cout << "\nScor acumulat: " << scorLocal << '\n';

    std::cout << "\nRaspunsuri corecte:\n";
    for (const auto& r : raspunsuriGhicite)
        std::cout << r << "; ";
    std::cout << '\n';

    std::cout << "\nRaspunsurile pentru intrebarile la care ai dat pas:\n";
    for (const auto& r : raspunsuriPierdute)
        std::cout << r << "; ";
    std::cout << '\n';
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
    continent = selectareContinent();
    seteazaTimp();

    std::cout << "Incepe jocul! Vei avea la dispozitie " << durataTimpSecunde << " de secunde. Mult succes!\n";
    startTimp = std::chrono::steady_clock::now();

    while (!timpExpirat() && jocInDesfasurare)
        gestioneazaIntrebare();

    if (jocInDesfasurare && timpExpirat()) std::cout << "Timpul a expirat!\n";
    stopTime();
    afisareDateRaspuns();
}

void JocViteza::gestioneazaIntrebare() {
    int nrIncercari = 1;
    auto [prompt, raspunsCorect] = genereazaIntrebareRaspuns();
    formateazaIntrebare(prompt);

    std::string input;
    std::getline(std::cin, input);
    if (input == "renunt") {
        raspunsuriPierdute.push_back(raspunsCorect);
        renunta();
        jocInDesfasurare = false;
        return;
    }
    if (input == "pas") {
        scorLocal = scorLocal - 50;
        raspunsuriPierdute.push_back(raspunsCorect);
        return;
    }
    bool corect = verificaRaspuns(input, raspunsCorect);
    while (!corect && !timpExpirat()) {
        std::cout << "Gresit! Incearca din nou sau scrie 'pas' daca vrei sa sari! (te va costa din puncte)\n";
        std::getline(std::cin, input);
        if (input == "pas") {
            scorLocal = scorLocal - 20;
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
    if (corect) {
        if (nrIncercari == 1) scorLocal += 100;
        else scorLocal += std::max(0, 100 - 5 * nrIncercari);
        raspunsuriGhicite.push_back(raspunsCorect);
    }
    else raspunsuriPierdute.push_back(raspunsCorect);
    scorLocal = std::max(0, scorLocal);
}


void JocViteza::renunta() {
    std::cout << "Ai renuntat. \n";
    jocInDesfasurare = false;
}


JocViteza::~JocViteza() = default;
