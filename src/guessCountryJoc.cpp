#include <algorithm>
#include <iostream>
#include "../include/guessCountryJoc.h"
#include "../include/tariGlobal.h"

int GuessCountryJoc::nrGuessCountryJucate = 0;

GuessCountryJoc::GuessCountryJoc() = default;

void GuessCountryJoc::afisareInstructiuni() {
    std::cout << "Vei avea la dispozitie un timp predefinit in care sa ghicesti cat mai multe tari pe baza capitalelor lor.\nPoti scrie 'pas' oricand, dar vei fi penalizat, iar daca treci peste o intrebare din prima, penalizarea va fi mai mare.\nDe asemenea, poti renunta la sesiunea curenta, daca scrii 'renunt'. Daca trimiti un raspuns dupa expirarea timpului,\nindiferent de corectitudinea lui, nu va fi luat in considerare.\n\n";
}

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
    std::cout << "Care este statul al carei capitala este " << prompt << "? (poti scrie 'PAS', sau 'RENUNT')\n";

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