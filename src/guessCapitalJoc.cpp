#include <algorithm>
#include <iostream>
#include "../include/guessCapitalJoc.h"
#include "../include/tariGlobal.h"
#include "../include/tari.h"

GuessCapitalJoc::GuessCapitalJoc() = default;

std::string GuessCapitalJoc::getNume() const {
    return "Guess The Capital: Speed Game";
}

std::pair<std::string, std::string> GuessCapitalJoc::genereazaIntrebareRaspuns() {
    const TariGlobal& bazaDate = TariGlobal::getInstance();
    auto prompt = bazaDate.getTariRandom(1,continent)[0];
    return {prompt.getNume(), prompt.getCapitala()};
}

void GuessCapitalJoc::formateazaIntrebare(const std::string &prompt) const {
    std::cout << "Care este capitala statului " << prompt << "?\n";

}

bool GuessCapitalJoc::verificaRaspuns(const std::string &input, const std::string &corect) const {
    // auto& bazaDate = TariGlobal::getInstance();
    // auto tara = bazaDate.getTaraByCapitala(input);
    // if (bazaDate.existaTara(tara.getNume())) return bazaDate.getTaraByCapitala(corect) == tara;
    // return false;
    return input == corect;
}

GuessCapitalJoc::~GuessCapitalJoc() = default;
