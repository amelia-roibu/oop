#include <iostream>
#include <random>
#include "../include/util.h"
#include "../include/shortestPathJoc.h"

#include <exception.h>

#include "../include/tariGlobal.h"

int ShortestPathJoc::nrShortestPathJucate = 0;

ShortestPathJoc::ShortestPathJoc() : Joc() {}

ShortestPathJoc::ShortestPathJoc(const ShortestPathJoc &other)
    : Joc(other),
      taraStart(other.taraStart),
      taraFinal(other.taraFinal),
      drumOptim(other.drumOptim),
      drumJucator(other.drumJucator) {
}

ShortestPathJoc& ShortestPathJoc::operator=(const ShortestPathJoc& other) {
    if (this == &other)
        return *this;
    Joc::operator =(other);
    taraStart = other.taraStart;
    taraFinal = other.taraFinal;
    drumOptim = other.drumOptim;
    drumJucator = other.drumJucator;
    return *this;
}

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
        std::cout << "Obiectivul tau este sa ajungi din tara 'Start', catre tara 'Destinatie', folosind doar tari vecine, creand un lant\nde lungime cat mai scurta. Tarile introduse pot fi vecine cu oricare dintre tarile considerate corecte\npana in momentul acela, iar ultima tara introdusa trebuie sa fie destinatia. Daca vrei sa renunti, poti scrie 'renunt'.\nOrice drum final valid va fi penalizat cu 5 puncte pentru fiecare tara 'in plus' fata de lungimea drumului optim.\nNu recomand sa incerci cu Oceania, pentru ca nu exista tari vecine direct si doar se vor genera aleatoriu alte tari.\n\n";
        continent = selectareContinent();

        if (continent.empty()) {
            std::vector<std::string> continenteValide = {"Europa", "Asia", "America de Sud", "Africa"}; // pt Oceania nu prea merge, pt ca nu sunt tari vecine direct
            try {
                continent = alegeRandom(continenteValide);
            } catch (const std::out_of_range& e) {
                std::cout << e.what(); // vectorul este gol
            }
        }
        do {
            taraStart = bazaDate.getTariRandom(continent);
            taraFinal = bazaDate.getTariRandom(continent);
            drumOptim = gasesteDrumBFS(taraStart.getNume(), taraFinal.getNume());
        } while (drumOptim.empty() || drumOptim.size() < 4); // e prea usor daca nu e un drum de lungime macar 4

        drumJucator.push_back(taraStart);
        scorLocal = 0;
        std::cout << "Start: " << taraStart.getNume() << std::endl;
        std::cout << "Destinatie: " << taraFinal.getNume() << std::endl;
        bool renuntat = false;
        while (taraFinal != drumJucator.back() && jocInDesfasurare) {
            std::cout << "\n ============================= \n";
            std::cout << "Introdu numele unei tari (sau 'RENUNT'): \n";
                Tari tara;
            try {
                tara = citesteTaraDinConsola();
            } catch (const ExceptieRenuntare&) {
                renunta();
                scorLocal = 0;
                renuntat = true;
                break;
            } catch (const ExceptieTaraInexistenta& e) {
                std::cout << e.what() << '\n';
                continue;
            }

            if (!apartineDeDrum(tara.getNume()) && esteVecinaCuDrum(tara.getNume())) {
                drumJucator.push_back(tara);
                std::cout << "Raspuns valid! ";
            }
            else
                std::cout << "Tara introdusa nu e buna :P (nu este vecina sau deja a fost luata in considerare). \n";
        }

        stopTime();
        if (!renuntat) {
            scorLocal = std::max(0, 100 - static_cast<int>(drumJucator.size() - drumOptim.size())*5);
            afisareDateRaspuns();
        }
    } catch (const std::exception& e) { // pentru debug - cand nu aveam toate tarile in json si esua sa mi gaseasca anumiti vecini
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
