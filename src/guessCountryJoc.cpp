#include <algorithm>
#include <iostream>
#include "../include/guessCountryJoc.h"
#include "../include/tariGlobal.h"

int GuessCountryJoc::nrGuessCountryJucate = 0;

GuessCountryJoc::GuessCountryJoc() = default;

std::string GuessCountryJoc::getNume() const {
    return "Guess The Country: Speed Game";
}

std::pair<std::string, std::string> GuessCountryJoc::genereazaIntrebareRaspuns() {
    const TariGlobal& bazaDate = TariGlobal::getInstance();
    Tari prompt;
    do {
        prompt = bazaDate.getTariRandom(continent);
    } while (obiecteFolosite.contains(prompt.getNume()));
    obiecteFolosite.insert(prompt.getNume());
    return {prompt.getCapitala(), prompt.getNume()};
}

void GuessCountryJoc::formateazaIntrebare(const std::string &prompt) const {
    std::cout << "Care este statul al carei capitala este " << prompt << "? (sau 'renunt')\n";

}

bool GuessCountryJoc::verificaRaspuns(const std::string &input, const std::string &corect) const {
    const auto& bazaDate = TariGlobal::getInstance();

    if (bazaDate.existaTara(input)) return bazaDate.getTara(corect) == bazaDate.getTara(input);
    return false;
}

void GuessCountryJoc::afiseazaNumarGuessCountry() {
    std::cout << "Guess Country a fost jucat de " << nrGuessCountryJucate << " ori.\n";
}

void GuessCountryJoc::porneste() {
    JocViteza::porneste();
    ++nrGuessCountryJucate;
}


GuessCountryJoc::~GuessCountryJoc() = default;