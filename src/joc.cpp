#include <iostream>
#include "../include/joc.h"
#include "../include/validareInput.h"

std::chrono::seconds Joc::durata_totala = std::chrono::seconds(0);
int Joc::numar_total_jocuri = 0;

Joc::Joc() : jocInDesfasurare(false) {}

Joc::Joc(const Joc &other)
    : start_time(other.start_time),
      end_time(other.end_time),
      jocInDesfasurare(other.jocInDesfasurare) {
}
Joc& Joc::operator=(const Joc &other) {
    if (this == &other)
        return *this;
    start_time = other.start_time;
    end_time = other.end_time;
    jocInDesfasurare = other.jocInDesfasurare;
    return *this;
}

std::string Joc::selectareContinent() {
    std::cout << "Doresti sa alegi un continent anume pentru aceasta sesiune a jocului?\n[Europa / Africa / Asia / America de Nord / America de Sud / Oceania / ENTER CA SA DAI SKIP] \n";
    std::string alegere = ValidareInput<std::string>::citesteValoare({"europa", "asia", "america de nord", "america de sud", "africa", "oceania", ""});

    if (alegere.empty()) {
        return alegere;
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