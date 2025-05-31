#include "../include/tariGlobal.h"
#include "../include/util.h"
#include <fstream>
#include "../include/nlohmann/json.hpp"  // de aici parsez JSON-ul
#include <../include/exception.h>
using json = nlohmann::json;

TariGlobal::TariGlobal() {
    incarcaDinFisier();
}

TariGlobal* TariGlobal::instanta = nullptr;

void TariGlobal::incarcaDinFisier() {
    std::ifstream file("resurse/tari.json");
    if (!file.is_open())
        file.open("../resurse/tari.json");
    if (!file.is_open())
        throw ExceptieFisier("Nu s-a putut deschide fisierul tari.json");

    json j;
    file >> j;

    for (auto& [numeTara, date] : j.items()) {
        // tratarea unor exceptii de parsare

        if (!date.contains("continent"))
            throw ExceptieParsareJson("camp lipsa: continent la tara " + numeTara);
        if (!date.contains("capitala"))
            throw ExceptieParsareJson("camp lipsa: capitala la tara " + numeTara);
        if (!date.contains("emisfera"))
            throw ExceptieParsareJson("camp lipsa: emisfera la tara " + numeTara);
        if (!date.contains("suprafata"))
            throw ExceptieParsareJson("camp lipsa: suprafata la tara " + numeTara);
        if (!date.contains("latitudine") || !date.contains("longitudine"))
            throw ExceptieParsareJson("coordonate lipsa la tara " + numeTara);
        if (!date.contains("vecini"))
            throw ExceptieParsareJson("camp lipsa: vecini la tara " + numeTara);
        for (const std::string directie : {"Nord", "Sud", "Est", "Vest"}) {
            if (!date["vecini"].contains(directie))
                throw ExceptieParsareJson("lipseste cheia '" + directie + "' din vecini pentru tara " + numeTara);
        }

        // parsarea efectiva
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
    throw ExceptieTaraInexistenta(nume);
}

const Tari& TariGlobal::getTaraByCapitala(const std::string& capitala) const {
    for (const auto& [_, tara] : tari)
        if (toLower(tara.getCapitala()) == toLower(capitala))
            return tara;
    throw ExceptieTaraInexistenta("Nu exista nicio tara cu aceasta capitala: " + capitala);
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
