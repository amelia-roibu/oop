#include <iostream>
#include "../include/joc.h"
#include "../include/validareInput.h"

std::chrono::seconds Joc::durata_totala = std::chrono::seconds(0);
int Joc::numar_total_jocuri = 0;

Joc::Joc() : jocInDesfasurare(false) {}

std::string Joc::selectareContinent() {
    std::cout << "Doresti sa alegi continentul de pe care sa joci? [y/n] \n";

    std::string alegere = ValidareInput<std::string>::citesteValoare({"y", "n"});

    if (alegere == "y") {
        std::cout << "Alege continentul: [Europa / Africa / Asia / America de Nord / America de Sud / Oceania] \n";
        return ValidareInput<std::string>::citesteValoare({"europa", "asia", "america de nord", "america de sud", "africa", "oceania"});
    }

    return "";
}

void Joc::startTime() {
    start_time = std::chrono::steady_clock::now();
}

void Joc::stopTime() {
    end_time = std::chrono::steady_clock::now();
    auto durata = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    durata_totala += durata;
    std::cout << "Durata acestui joc: " << durata.count() << " secunde\n \n";
}

void Joc::afiseazaDurataTotala() {
    std::cout << "Durata totala a jocurilor: " << durata_totala.count() << " secunde\n";
}

void Joc::afiseazaNumarTotalJocuri() {
    std::cout << "Numar total de jocuri jucate: " << numar_total_jocuri << "\n Dintre care: \n";
}

void Joc::cresteContorJocuri() {
    ++numar_total_jocuri;
}


Joc::~Joc() = default;