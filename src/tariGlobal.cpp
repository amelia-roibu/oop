#include "../include/tariGlobal.h"
#include "../include/util.h"
#include <fstream>
#include "../include/nlohmann/json.hpp"  // dacă aici parsezi JSON-ul
using json = nlohmann::json;

TariGlobal::TariGlobal() {
    std::ifstream file("resurse/tari.json");
    if (!file.is_open())
        file.open("../resurse/tari.json");
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

// TariGlobal& TariGlobal::getInstance() {
//     if (instanta == nullptr)
//         instanta = new TariGlobal();
//     return *instanta;
// }

TariGlobal& TariGlobal::getInstance() {
    static TariGlobal instance;
    return instance;
}

const Tari& TariGlobal::getTara(const std::string& nume) const {
    std::string numeLower = toLower(nume);
    for (const auto& [numeTara, dateTara] : tari) {
        if (toLower(numeTara) == numeLower)
            return dateTara;
    }
    throw std::invalid_argument("Tara nu a fost gasita: " + nume);
}

const Tari& TariGlobal::getTaraByCapitala(const std::string& capitala) const {
    for (const auto& [_, tara] : tari)
        if (toLower(tara.getCapitala()) == toLower(capitala))
            return tara;
    throw std::invalid_argument("Nu exista nicio tara cu aceasta capitala: " + capitala);
}

std::vector<Tari> TariGlobal::getTariDinContinent(const std::string& continent) const{
    std::vector<Tari> rezultat;
    for (const auto& [_, tara] : tari)
        if (toLower(tara.getContinent()) == toLower(continent))
            rezultat.push_back(tara);
    return rezultat;
}

Tari TariGlobal::getTariRandom(const std::string& continent) const {
    std::vector<Tari> toateTarile;
    if (!continent.empty())
        toateTarile = getTariDinContinent(continent);
    else
        for (const auto& [_, tara] : tari)
            toateTarile.push_back(tara);

    return alegeRandom(toateTarile);
}

bool TariGlobal::existaTara(const std::string& nume) const {
    std::string numeLower = toLower(nume);
    for (const auto& [cheie, _] : tari) {
        if (toLower(cheie) == numeLower)
            return true;
    }
    return false;
}
