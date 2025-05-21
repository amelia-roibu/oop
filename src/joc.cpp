#include <iostream>
#include <limits>
#include "../include/joc.h"
#include "../include/tariGlobal.h"
std::chrono::seconds Joc::durata_totala = std::chrono::seconds(0);
int Joc::numar_total_jocuri = 0;

Joc::Joc() : jocInDesfasurare(false) {}

std::string Joc::selectareContinent() {
    std::string continent = "";
    std::cout << "Doresti sa alegi continentul de pe care sa joci? [y/n] \n";
    char alegere;
    std::cin >> alegere;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (alegere == 'y') {
        std::cout << "Alege continentul: [Europa / Africa / Asia / America de Nord / America de Sud / Oceania] \n";
        std::getline(std::cin, continent);
        if (TariGlobal::getInstance().getTariDinContinent(continent).empty()) {
            std::cout << "Continent invalid. Se va selecta aleatoriu. Sorry!\n";
            continent = "";
        }
    }
    else {
        std::cout << "In regula. \n";
    }
    return continent;
}

void Joc::startTime() {
    start_time = std::chrono::steady_clock::now();
}

void Joc::stopTime() {
    end_time = std::chrono::steady_clock::now();
    auto durata = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    durata_totala += durata;
    std::cout << "Durata acestui joc: " << durata.count() << " secunde\n";
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