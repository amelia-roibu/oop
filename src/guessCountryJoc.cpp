#include <algorithm>
#include <iostream>
#include "../include/guessCountryJoc.h"
#include "../include/tariGlobal.h"

GuessCountryJoc::GuessCountryJoc() = default;

std::string GuessCountryJoc::getNume() const {
    return "Guess The Country: Speed Game";
}

std::pair<std::string, std::string> GuessCountryJoc::genereazaIntrebareRaspuns() {
    TariGlobal& bazaDate = TariGlobal::getInstance();
    auto prompt = bazaDate.getTariRandom(1,continent)[0];
    return {prompt.getCapitala(), prompt.getNume()};
}

void GuessCountryJoc::formateazaIntrebare(const std::string &prompt) const {
    std::cout << "Care este statul al carei capitala este " << prompt << "?\n";

}

bool GuessCountryJoc::verificaRaspuns(const std::string &input, const std::string &corect) const {
    auto& bazaDate = TariGlobal::getInstance();

    if (bazaDate.existaTara(input)) return bazaDate.getTara(corect) == bazaDate.getTara(input);
    return false;
    return input == corect;
}

GuessCountryJoc::~GuessCountryJoc() = default;