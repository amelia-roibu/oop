#include <iostream>
#include "../include/infoPointJoc.h"
#include "../include/validareInput.h"
#include "../include/tari.h"
#include "../include/exception.h"
#include "../include/tariGlobal.h"


int InfoPointJoc::nrInfoPointJucate = 0;

InfoPointJoc::InfoPointJoc() : modJoc(0), scorLocal(0), continent("") {}

void InfoPointJoc::porneste() {
    jocInDesfasurare = true;
    scorLocal = 0;
    cresteContorJocuri();
    cresteContorInfoPoint();
    startTime();

    std::cout << "Bine ai venit in Info Point!\nAici este un loc chill in care sa iti imbogatesti sau improspatezi cunostintele despre tarile lumii. Ai optiunea sa consulti rapid o tara, daca vrei doar sa iti amintesti rapid o informatie, sau sa parcurgi un tur virtual prin diverse tari ale lumii, alese de tine sau alese aleatoriu.\n";
    std::cout << "\nAlege modul de joc:\n0. Single\n1. Tur virtual\n2. Renunt\n\n";
    modJoc = ValidareInput<int>::citesteValoare(0,2);
    if (modJoc == 2)
        renunta();

    if (modJoc == 0) modSingle();
}

void InfoPointJoc::modSingle() {
    const TariGlobal& bazaDate = TariGlobal::getInstance();

    std::cout << "Vrei sa (mai) afli informatii despre o tara anume? [y/n/renunt]\n";
    std::string alegere = ValidareInput<std::string>::citesteValoare({"y","n","renunt"});

    if (alegere == "renunt")
        renunta();
    else {
        if (alegere == "n") {
            continent = selectareContinent();
            taraInfo = bazaDate.getTariRandom(continent);
            afisareDateRaspuns();
            scorLocal++;
        }
        else {
            while (jocInDesfasurare) {
                std::cout << "Introdu numele unei tari:\n";
                try {
                    taraInfo = citesteTaraDinConsola();
                    afisareDateRaspuns();
                    scorLocal++;
                    jocInDesfasurare = false;
                } catch (const ExceptieRenuntare&) {
                    renunta();
                } catch (const ExceptieTaraInexistenta& e) {
                    std::cout << e.what();
                }
            }
        }
    }
}

void InfoPointJoc::modExtins() {
    porneste();
    const TariGlobal& bazaDate = TariGlobal::getInstance();

    while (jocInDesfasurare && modJoc == 1) {
        std::cout << "Vrei sa afli informatii despre o tara anume? [y/n/renunt]\n";
        std::string alegere = ValidareInput<std::string>::citesteValoare({"y","n", "renunt"});

        if (alegere == "renunt") {
            renunta();
            break;
        }

        if (alegere == "n") {
            continent = selectareContinent();
            taraInfo = bazaDate.getTariRandom(continent);
            afisareDateRaspuns();
            scorLocal++;
        }
        else {
            while (jocInDesfasurare) {
                std::cout << "Introdu numele unei tari:\n";
                try {
                    taraInfo = citesteTaraDinConsola();
                    afisareDateRaspuns();
                    scorLocal++;
                } catch (const ExceptieRenuntare&) {
                    renunta();
                } catch (const ExceptieTaraInexistenta& e) {
                    std::cout << e.what();
                }
            }
        }
    }
    stopTime();
}

void InfoPointJoc::afisareDateRaspuns() {
    std::cout << "Uite cateva informatii despre " << taraInfo.getNume() << ":\n";
    std::cout << taraInfo;
}

void InfoPointJoc::renunta() {
    std::cout << "Ai renuntat la turul virtual.\n";
    jocInDesfasurare = false;
}

std::string InfoPointJoc::getNume() const {
    return "Info Point";
}

int InfoPointJoc::getScor() {
    return scorLocal;
}

void InfoPointJoc::cresteContorInfoPoint() {
    ++nrInfoPointJucate;
}

void InfoPointJoc::afiseazaNumarInfoPoint() {
    std::cout << "Info Point a fost jucat de " << nrInfoPointJucate << " ori.\n";
}

InfoPointJoc::~InfoPointJoc() = default;