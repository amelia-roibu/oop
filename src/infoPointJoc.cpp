#include <iostream>
#include "../include/infoPointJoc.h"
#include "../include/validareInput.h"
#include "../include/tari.h"
#include "../include/exception.h"
#include "../include/tariGlobal.h"

int InfoPointJoc::nrInfoPointJucate = 0;

InfoPointJoc::InfoPointJoc() : Joc(), modJoc(1) {}

InfoPointJoc::InfoPointJoc(const InfoPointJoc &other)
        : Joc(other),
          taraInfo(other.taraInfo),
          modJoc(other.modJoc) {
}

InfoPointJoc& InfoPointJoc::operator=(const InfoPointJoc& other) {
    if (this == &other)
        return *this;
    Joc::operator =(other);
    taraInfo = other.taraInfo;
    modJoc = other.modJoc;
    return *this;
}

void InfoPointJoc::porneste() {
    jocInDesfasurare = true;
    scorLocal = 0;
    cresteContorJocuri();
    cresteContorInfoPoint();
    startTime();

    std::cout << "Bine ai venit in Info Point!\nAici este un loc chill in care sa iti imbogatesti sau improspatezi cunostintele despre tarile lumii.\nAi optiunea sa consulti rapid o tara, daca vrei doar sa iti amintesti rapid o informatie, sau sa parcurgi\nun tur virtual prin diverse tari ale lumii, alese de tine sau alese aleatoriu.\nPoti iesi oricand, scriind 'renunt'. Cu cat consulti mai multe tari, cu atat iti poate creste scorul.\nBucura-te de calatorie!\n";
    std::cout << "\nAlege modul de joc:\n0. Single\n1. Tur virtual\n2. Renunt\n\n";
    modJoc = ValidareInput<int>::citesteValoare(0,2);
    if (modJoc == 2)
        renunta();

    if (modJoc == 0) modSingle();
}

void InfoPointJoc::modSingle() {
    std::cout << "Vrei sa afli informatii despre o tara anume? [Y / ENTER CA DAI SKIP / RENUNT]\n";
    std::string alegere = ValidareInput<std::string>::citesteValoare({"y","","renunt"});

    if (alegere == "renunt")
        renunta();
    else if (alegere.empty()) generareTara();
    else citireTara();
}

void InfoPointJoc::modExtins() {
    porneste();

    while (jocInDesfasurare && modJoc == 1) {
        modSingle();
    }
    stopTime();
}

void InfoPointJoc::afisareDateRaspuns() {
    std::cout << "Uite cateva informatii despre " << taraInfo.getNume() << ":\n";
    std::cout << taraInfo;
}

void InfoPointJoc::renunta() {
    std::cout << "Ai renuntat la turul virtual.\n";
    std::cout << "Tari consultate: " << scorLocal << "\n";
    jocInDesfasurare = false;
}

std::string InfoPointJoc::getNume() const {
    return "Info Point";
}

int InfoPointJoc::getScor() {
    return scorLocal;
}

void InfoPointJoc::citireTara() {
    while (jocInDesfasurare) {
        std::cout << "\n ============================= \n";
        std::cout << "Introdu numele tarii:\n";
        try {
            taraInfo = citesteTaraDinConsola();
            afisareDateRaspuns();
            scorLocal++;
            break;
        } catch (const ExceptieRenuntare&) {
            renunta();
        } catch (const ExceptieTaraInexistenta& e) {
            std::cout << e.what();
        }
    }
}

void InfoPointJoc::generareTara() {
    const TariGlobal& bazaDate = TariGlobal::getInstance();

    continent = selectareContinent();
    taraInfo = bazaDate.getTariRandom(continent);
    afisareDateRaspuns();
    scorLocal++;
}


void InfoPointJoc::cresteContorInfoPoint() {
    ++nrInfoPointJucate;
}

void InfoPointJoc::afiseazaNumarInfoPoint() {
    std::cout << "Info Point a fost consultat de " << nrInfoPointJucate << " ori.\n";
}

InfoPointJoc::~InfoPointJoc() = default;