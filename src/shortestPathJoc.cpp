#include <iostream>
#include <queue>
#include <unordered_set>
#include <map>
#include <algorithm>
#include "../include/shortestPathJoc.h"
#include "../include/tariGlobal.h"

ShortestPathJoc::ShortestPathJoc() : scorLocal(0) {}

std::string ShortestPathJoc::getNume() const {
    return "Shortest Path";
}

int ShortestPathJoc::getScor() {
    return scorLocal;
}

std::vector<Tari> ShortestPathJoc::gasesteDrumBFS(const std::string& start, const std::string& final) const {
    std::queue<std::string> coada;
    coada.push(start);
    std::string current;

    std::unordered_set<std::string> vizitate;
    vizitate.insert(start);

    std::map<std::string, std::string> parinte;
    parinte[start] = "";

    while (!coada.empty()) {
        current = coada.front();
        coada.pop();

        if (current == final)
            break;

        auto vecini = TariGlobal::getInstance().getTara(current).getVeciniPeDirectie();
        for (const auto& vecin : vecini)
            if (!vizitate.contains(vecin)) {
                coada.push(vecin);
                vizitate.insert(vecin);
                parinte[vecin] = current;
            }
    }

    if (!parinte.contains(final))
        return {};

    std::vector<Tari> drum;
    current = final;
    while (!current.empty()) {
        drum.push_back(TariGlobal::getInstance().getTara(current));
        current = parinte[current];
    }

    std::ranges::reverse(drum.begin(), drum.end());
    return drum;
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
    const TariGlobal& bazaDate = TariGlobal::getInstance();

    std::cout << "Bine ai venit la Shortest Path Game! \n";

    continent = selectareContinent();

    if (continent.empty()) {
        std::vector<std::string> continenteValide = {"Europa", /*"Asia",*/ "America de Sud", "Africa"};
        continent = continenteValide[rand() % continenteValide.size()];
    }
    do {
        std::vector<Tari> destinatii = bazaDate.getTariRandom(2, continent);
        if (destinatii.size() < 2) continue;

        taraStart = destinatii[0];
        taraFinal = destinatii[1];
        drumOptim = gasesteDrumBFS(taraStart.getNume(), taraFinal.getNume());
    } while (drumOptim.empty() || drumOptim.size() < 4);

    drumJucator.push_back(taraStart);
    scorLocal = 0;
    std::cout << "Start: " << taraStart.getNume() << std::endl;
    std::cout << "Destinatie: " << taraFinal.getNume() << std::endl;
    std::cout << "Introdu tarile vecine pe care poti sa le strabati pentru a ajunge la destinatie.\n";

    while (taraFinal != drumJucator.back()) {
        std::cout << "Introdu numele unei tari: \n";
        std::string guess;
        std::getline(std::cin, guess);
        if (bazaDate.existaTara(guess) && !apartineDeDrum(guess) && esteVecinaCuDrum(guess))
            drumJucator.push_back(bazaDate.getTara(guess));
        else
            std::cout << "Tara introdusa nu e buna :P \n";

    }

    scorLocal = 100 - (drumJucator.size() - drumOptim.size())*5;
    if (scorLocal < 0) scorLocal = 0;
    afisareDateRaspuns();
    } catch (const std::exception& e) {
        std::cout << "Exceptie prinsa: " << e.what() << '\n';
    }
}

void ShortestPathJoc::afisareDateRaspuns() {
    std::cout << "Felicitari! Ai ajuns in " << taraFinal.getNume() << std::endl;
    std::cout << "Scor: " << scorLocal << std::endl;
    std::cout << "Drumul tau: ";
    for (const auto& tara : drumJucator)
        std::cout << tara.getNume() << " -> ";
    std::cout << "\b\b\b\b \n";
    drumJucator.clear();

    std::cout << "Drumul optim: ";
    for (const auto& tara : drumOptim)
        std::cout << tara.getNume() << " -> ";
    std::cout << "\b\b\b\b \n";
    drumOptim.clear();
}

ShortestPathJoc::~ShortestPathJoc() = default;
