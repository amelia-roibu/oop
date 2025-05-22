#include <algorithm>
#include <iostream>
#include "../include/guessCapitalJoc.h"

#include <util.h>

#include "../include/tariGlobal.h"
#include "../include/tari.h"

int GuessCapitalJoc::nrGuessCapitalJucate = 0;

GuessCapitalJoc::GuessCapitalJoc() = default;

std::string GuessCapitalJoc::getNume() const {
    return "Guess The Capital: Speed Game";
}

std::pair<std::string, std::string> GuessCapitalJoc::genereazaIntrebareRaspuns() {
    const TariGlobal& bazaDate = TariGlobal::getInstance();
    Tari prompt;
    do {
        prompt = bazaDate.getTariRandom(continent);
    } while (obiecteFolosite.contains(prompt.getNume()));
    obiecteFolosite.insert(prompt.getNume());
    return {prompt.getNume(), prompt.getCapitala()};
}

void GuessCapitalJoc::formateazaIntrebare(const std::string &prompt) const {
    std::cout << "Care este capitala statului " << prompt << "? (sau 'renunt')\n";

}

bool GuessCapitalJoc::verificaRaspuns(const std::string &input, const std::string &corect) const {
    return toLower(input) == toLower(corect);
}

void GuessCapitalJoc::afiseazaNumarGuessCapital() {
    std::cout << "Guess Capital a fost jucat de " << nrGuessCapitalJucate << " ori.\n";
}

void GuessCapitalJoc::porneste() {
    JocViteza::porneste();
    ++nrGuessCapitalJucate;
}


GuessCapitalJoc::~GuessCapitalJoc() = default;
