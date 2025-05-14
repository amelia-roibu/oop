#include <iostream>
#include <string>
#include <limits>
#include "../include/countryle.h"
#include "../include/tariGlobal.h"

CountryleJoc::CountryleJoc() : scorLocal(100), nrIncercari(0), continent("") {}

void CountryleJoc::afisareDateRaspuns(const Tari& input) {
    std::cout << "Informatii ajutatoare:\n";
    std::cout << "Tara introdusa: " << input.getNume() << '\n';
    std::cout << "Emisfera: " << input.getEmisfera() <<" ";
    if (input.getEmisfera() == taraTinta.getEmisfera())
        std::cout << "CORECT \n";
    else std::cout << "GREȘIT \n";

    std::cout << "Continent: " << input.getContinent() <<" ";
    if (input.getContinent() == taraTinta.getContinent())
        std::cout << "CORECT \n";
    else std::cout << "GREȘIT \n";

    std::cout << "Suprafata: ";
    if (input.getSuprafata() < taraTinta.getSuprafata())
        std::cout << "Mai mica decat suprafata tarii tinta.\n";
    else std::cout << "Mai mare decat suprafata tarii tinta.\n";

    std::cout << "Directia fata de tara tinta: " << input.directieFataDe(taraTinta) << "\n";
}


void CountryleJoc::porneste() {
    TariGlobal& bazaDate = TariGlobal::getInstance();

    std::cout << "Bine ai venit in Countryle!\n";
    std::cout << "Doresti sa alegi continentul de pe care sa joci? [y/n] \n";
    char alegere;
    std::cin >> alegere;
    if (alegere == 'y') {
        std::cout << "Alege continentul: [Europa / Africa / Asia / America de Nord / America de Sud / Australia] \n";
        std::cin >> continent;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (bazaDate.getTariDinContinent(continent).empty()) {
            std::cout << "Continent invalid. Se va selecta aleatoriu. Sorry!\n";
            continent = "";
        }
    }
    else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "In regula. Se va selecta aleatoriu o tara. \n";
    }

    taraTinta = bazaDate.getTariRandom(1, continent)[0];
    scorLocal = 100;
    nrIncercari = 0;

    while (true) {
        std::string taraInput;
        std::cout << "Incercarea " << ++nrIncercari << ". Introdu numele unei tari: ";
        std::getline(std::cin, taraInput);

        while (!bazaDate.existaTara(taraInput)) {
            std::cout << "Nu exista tara " << taraInput <<". Incearca din nou.\n";
            std::getline(std::cin, taraInput);
        }

        Tari input = bazaDate.getTara(taraInput);

        if (input == taraTinta) {
            std::cout << "Felicitari!! \n Ai ghicit tara: " << taraTinta.getNume() << '\n';
            afisareFinala();
            break;
        }

        scorLocal -= 5;

        bonusVecin(taraInput);

        if (scorLocal <= 0) {
            std::cout << "Ai ramas fara puncte!\n";
            std::cout << "Tara corecta era: " << taraTinta.getNume() << '\n';
            afisareFinala();
            break;
        }

        afisareDateRaspuns(input);
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
