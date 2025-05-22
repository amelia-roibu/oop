#include <iostream>
#include <random>
#include "../include/util.h"
#include "../include/shortestPathJoc.h"
#include "../include/tariGlobal.h"

int ShortestPathJoc::nrShortestPathJucate = 0;

ShortestPathJoc::ShortestPathJoc() : scorLocal(0) {}

std::string ShortestPathJoc::getNume() const {
    return "Shortest Path";
}

int ShortestPathJoc::getScor() {
    return scorLocal;
}

bool ShortestPathJoc::apartineDeDrum(const std::string& taraNoua) const {
    if (!TariGlobal::getInstance().existaTara(taraNoua)) return false;

    for (const auto& tara : drumJucator)
        if (tara == TariGlobal::getInstance().getTara(taraNoua))
            return true;
    return false;
}
bool ShortestPathJoc::esteVecinaCuDrum(const std::string& taraNoua) const {
    if (!TariGlobal::getInstance().existaTara(taraNoua)) return false;

    for (const auto& tara : drumJucator)
        if (TariGlobal::getInstance().getTara(taraNoua).esteVecinCu(tara.getNume()))
            return true;
    return false;
}


void ShortestPathJoc::porneste() {
    try {
        jocInDesfasurare = true;
        cresteContorJocuri();
        cresteContorShortestPath();
        startTime();
        const TariGlobal& bazaDate = TariGlobal::getInstance();

        std::cout << "Bine ai venit la Shortest Path Game! \n";

        continent = selectareContinent();

        if (continent.empty()) {
            std::vector<std::string> continenteValide = {"Europa", "Asia", "America de Sud", "Africa"};
            continent = alegeRandom(continenteValide);
        }
        do {
            taraStart = bazaDate.getTariRandom(continent);
            taraFinal = bazaDate.getTariRandom(continent);
            drumOptim = gasesteDrumBFS(taraStart.getNume(), taraFinal.getNume());
        } while (drumOptim.empty() || drumOptim.size() < 4);

        drumJucator.push_back(taraStart);
        scorLocal = 0;
        std::cout << "Start: " << taraStart.getNume() << std::endl;
        std::cout << "Destinatie: " << taraFinal.getNume() << std::endl;
        std::cout << "Introdu tarile vecine pe care poti sa le strabati pentru a ajunge la destinatie.\n";
        bool renuntat = false;
        while (taraFinal != drumJucator.back() && jocInDesfasurare) {
            std::cout << "Introdu numele unei tari (sau 'renunt'): \n";
                Tari tara;
            try {
                tara = citesteTaraDinConsola();
            } catch (const std::runtime_error&) {
                renunta();
                scorLocal = 0;
                renuntat = true;
                break;
            } catch (const std::exception& e) {
                std::cout << e.what() << '\n';
                continue;
            }

            if (!apartineDeDrum(tara.getNume()) && esteVecinaCuDrum(tara.getNume()))
                drumJucator.push_back(tara);
            else
                std::cout << "Tara introdusa nu e buna :P (nu este vecina sau deja a fost parcursa). \n";
        }

        if (!renuntat) scorLocal = std::max(0, 100 - static_cast<int>(drumJucator.size() - drumOptim.size())*5);
        stopTime();
        if (!renuntat) afisareDateRaspuns();

    } catch (const std::exception& e) {
        std::cout << "Exceptie prinsa: " << e.what() << '\n';
    }
}

void ShortestPathJoc::renunta() {
    std::cout << "Ai renuntat. Drumul optim era: ";
    for (std::size_t i = 0; i < drumOptim.size(); ++i) {
        std::cout << drumOptim[i].getNume();
        if (i != drumOptim.size() - 1)
            std::cout << " -> ";
    }
    std::cout << '\n';
    std::cout << "Scor: " << scorLocal << std::endl;
    drumJucator.clear();
    drumOptim.clear();
}


void ShortestPathJoc::afisareDateRaspuns() {
    std::cout << "Felicitari! Ai ajuns in " << taraFinal.getNume() << "!\n";
    std::cout << "Scor: " << scorLocal << std::endl;
    std::cout << "Drumul tau: ";
    for (const auto& tara : drumJucator)
        std::cout << tara.getNume() << " -> ";
    std::cout << '\n';
    drumJucator.clear();

    std::cout << "Drumul optim: ";
    for (std::size_t i = 0; i < drumOptim.size(); ++i) {
        std::cout << drumOptim[i].getNume();
        if (i != drumOptim.size() - 1)
            std::cout << " -> ";
    }
    std::cout << '\n';
    drumOptim.clear();
}

void ShortestPathJoc::cresteContorShortestPath() {
    ++nrShortestPathJucate;
}


void ShortestPathJoc::afiseazaNumarShortestPath() {
    std::cout << "Shortest Path a fost jucat de " << nrShortestPathJucate << " ori.\n";
}


ShortestPathJoc::~ShortestPathJoc() = default;
