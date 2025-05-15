#include <iostream>
#include <string>
#include "../include/countryle.h"
#include "../include/tariGlobal.h"

CountryleJoc::CountryleJoc() : scorLocal(100), nrIncercari(0), continent("") {}

void CountryleJoc::afisareDateRaspuns() {
    std::cout << "Informatii ajutatoare:\n";
    std::cout << "Tara introdusa: " << taraInput.getNume() << '\n';
    std::cout << "Emisfera: " << taraInput.getEmisfera() <<" ";
    if (taraInput.getEmisfera() == taraTinta.getEmisfera())
        std::cout << "CORECT \n";
    else std::cout << "GRESIT \n";

    std::cout << "Continent: " << taraInput.getContinent() <<" ";
    if (taraInput.getContinent() == taraTinta.getContinent())
        std::cout << "CORECT \n";
    else std::cout << "GRESIT \n";

    std::cout << "Suprafata: ";
    if (taraInput.getSuprafata() < taraTinta.getSuprafata())
        std::cout << "Tara misterioasa are o suprafata mai mare decat " << taraInput.getNume() << ".\n";
    else std::cout << "Tara misterioasa are o suprafata mai mica decat " << taraInput.getNume() << ".\n";

    std::cout << "Directia fata de tara tinta: " << taraInput.directieFataDe(taraTinta) << "\n";
}


void CountryleJoc::porneste() {
    const TariGlobal& bazaDate = TariGlobal::getInstance();

    std::cout << "Bine ai venit in Countryle!\n";

    continent = Joc::selectareContinent();

    taraTinta = bazaDate.getTariRandom(1, continent)[0];
    scorLocal = 100;
    nrIncercari = 0;

    while (true) {
        std::string numeInput;
        std::cout << "Incercarea " << ++nrIncercari << ". Introdu numele unei tari: ";
        std::getline(std::cin, numeInput);

        while (!bazaDate.existaTara(numeInput)) {
            std::cout << "Nu exista tara " << numeInput <<". Incearca din nou.\n";
            std::getline(std::cin, numeInput);
        }

        taraInput = bazaDate.getTara(numeInput);

        if (taraInput == taraTinta) {
            std::cout << "Felicitari!! \n Ai ghicit tara: " << taraTinta.getNume() << '\n';
            afisareFinala();
            break;
        }

        scorLocal -= 5;

        bonusVecin(numeInput);

        if (scorLocal <= 0) {
            std::cout << "Ai ramas fara puncte!\n";
            std::cout << "Tara corecta era: " << taraTinta.getNume() << '\n';
            afisareFinala();
            break;
        }

        afisareDateRaspuns();
    }
}

int CountryleJoc::getScor() {
    return scorLocal;
}

std::string CountryleJoc::getNume() const {
    return "Countryle";
}

void CountryleJoc::afisareFinala() const {
    if (nrIncercari == 1)
        std::cout << "WOW! Din prima!\n";
    else if (nrIncercari <= 4)
        std::cout << "Super joc!\n";
    else
        std::cout << "Buna treaba!\n";

    std::cout << "Numar de incercari: " << nrIncercari << "\n";
    std::cout << "Scor: " << scorLocal << "\n\n";
}

void CountryleJoc::bonusVecin(const std::string& tara) {
    if (taraTinta.esteVecinCu(tara)) {
        std::cout << "Tara este chiar vecina a tarii tinta! Primesti un bonus :) \n";
        scorLocal += 3;
    }
}


CountryleJoc::~CountryleJoc() = default;
