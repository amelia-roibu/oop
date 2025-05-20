#include "../include/tariGlobal.h"
#include <fstream>
#include "../include/nlohmann/json.hpp"  // dacă aici parsezi JSON-ul
using json = nlohmann::json;
#include <algorithm>
#include <random>

TariGlobal::TariGlobal() {
    std::ifstream file("../resurse/tari.json");
    if (!file.is_open())
        throw std::runtime_error("Nu s-a putut deschide fisierul tari.json");

    json j;
    file >> j;

    for (auto& [numeTara, date] : j.items()) {
        std::string continent = date["continent"];
        std::string capitala = date["capitala"];
        std::string emisfera = date["emisfera"];
        double suprafata = date["suprafata"];
        double latitudine = date["latitudine"];
        double longitudine = date["longitudine"];

        std::map<std::string, std::vector<std::string>> vecini;
        for (const std::string directie : {"Nord", "Sud", "Est", "Vest"}) {
            vecini[directie] = date["vecini"][directie].get<std::vector<std::string>>();
        }

        tari[numeTara] = Tari(numeTara, capitala, continent, emisfera, suprafata, latitudine, longitudine, vecini);
    }
}

TariGlobal* TariGlobal::instanta = nullptr;

TariGlobal& TariGlobal::getInstance() {
    if (instanta == nullptr)
        instanta = new TariGlobal();
    return *instanta;
}

const Tari& TariGlobal::getTara(const std::string& nume) const {
    auto it = tari.find(nume);
    if (it == tari.end())
        throw std::invalid_argument("Tara nu a fost gasita: " + nume);
    return it->second;
}

const Tari& TariGlobal::getTaraByCapitala(const std::string& capitala) const {
    for (const auto& [_, tara] : tari)
        if (tara.getCapitala() == capitala)
            return tara;
    throw std::invalid_argument("Nu exista nicio tara cu aceasta capitala: " + capitala);
}

std::vector<Tari> TariGlobal::getTariDinContinent(const std::string& continent) const{
    std::vector<Tari> rezultat;
    for (const auto& [_, tara] : tari)
        if (tara.getContinent() == continent)
            rezultat.push_back(tara);
    return rezultat;
}

std::vector<Tari> TariGlobal::getTariRandom(std::size_t nr, const std::string& continent) const {
    std::vector<Tari> toateTarile;

    if (!continent.empty())
        toateTarile = getTariDinContinent(continent);
    else
        for (const auto& [_, tara] : tari)
            toateTarile.push_back(tara);

    std::random_device rd; // genereaza un generator de entropie din surse externe, un fel de seed aleator, mai bun decat rand()
    std::mt19937 gen(rd());
    /* mt19937 e un motor de generare de numere pseudo-aleatoare; numele vine de la „Mersenne Twister”
    primește seed de la rd() — deci va genera o secvență diferită de fiecare dată când rulezi programul. */

    std::shuffle(toateTarile.begin(), toateTarile.end(), gen);

    if (nr > toateTarile.size()) nr = toateTarile.size();
    return std::vector<Tari>(toateTarile.begin(), toateTarile.begin() + nr);
}

bool TariGlobal::existaTara(const std::string& nume) const {
    return tari.find(nume) != tari.end();
}
