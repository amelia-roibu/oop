#include <algorithm>
#include <iostream>
#include "../include/guessCapitalJoc.h"

#include <util.h>

#include "../include/tariGlobal.h"
#include "../include/tari.h"

int GuessCapitalJoc::nrGuessCapitalJucate = 0;

GuessCapitalJoc::GuessCapitalJoc() : JocViteza() {}

GuessCapitalJoc::GuessCapitalJoc(const GuessCapitalJoc &other) : JocViteza(other) {}

GuessCapitalJoc& GuessCapitalJoc::operator=(const GuessCapitalJoc& other) {
    if (this == &other)
        return *this;
    JocViteza::operator =(other);
    return *this;
}

void GuessCapitalJoc::afisareInstructiuni() {
    std::cout << "Vei avea la dispozitie un timp predefinit in care sa ghicesti cat mai multe capitale, pe baza promptului dat.\nPoti scrie 'pas' oricand, dar vei fi penalizat, iar daca treci peste o intrebare din prima, penalizarea va fi mai mare.\nDe asemenea, poti renunta la sesiunea curenta, daca scrii 'renunt'. Daca trimiti un raspuns dupa expirarea timpului,\nindiferent de corectitudinea lui, nu va fi luat in considerare.\n\n";
}

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
    std::cout << "Care este capitala statului " << prompt << "? (poti scrie 'PAS', sau 'RENUNT')\n";

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
