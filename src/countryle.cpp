#include <iostream>
#include <string>
#include "../include/countryle.h"
#include "../include/tariGlobal.h"
#include "../include/util.h"

int CountryleJoc::nrCountryleJucate = 0;

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

    std::cout << "Directia fata de tara tinta: " << taraInput.directieFataDe(taraTinta) << "\n \n";
}


void CountryleJoc::porneste() {
    jocInDesfasurare = true;
    cresteContorJocuri();
    cresteContorCountryle();
    startTime();
    const TariGlobal& bazaDate = TariGlobal::getInstance();

    std::cout << "Bine ai venit in Countryle!\n";
    continent = selectareContinent();

    taraTinta = bazaDate.getTariRandom(continent);
    scorLocal = 100;
    nrIncercari = 0;

    while (jocInDesfasurare) {
        std::cout << "Incercarea " << ++nrIncercari << ". Introdu numele unei tari (sau 'renunt' daca vrei sa renunti):\n";

        try {
            taraInput = citesteTaraDinConsola();
        } catch (const std::runtime_error&) {
            scorLocal = 0;
            renunta();
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << "\n";
            --nrIncercari;
            continue;
        }

        if (taraInput == taraTinta) {
            std::cout << "Felicitari!! \nAi ghicit tara: " << taraTinta << '\n';
            afisareFinala();
            break;
        }

        scorLocal -= 5;
        bonusVecin(taraInput.getNume());

        if (scorLocal <= 0) {
            std::cout << "Ai ramas fara puncte!\n";
            std::cout << "Tara corecta era: " << taraTinta << '\n';
            afisareFinala();
            break;
        }
        afisareDateRaspuns();
    }
    stopTime();
}

void CountryleJoc::renunta() {
    std::cout << "Ai renuntat. Raspunsul era: \n" << taraTinta << std::endl;
    std::cout << "Scor: " << scorLocal << "\n";
    jocInDesfasurare = false;
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

void CountryleJoc::cresteContorCountryle() {
    ++nrCountryleJucate;
}


void CountryleJoc::afiseazaNumarCountryle() {
    std::cout << "Countryle a fost jucat de " << nrCountryleJucate << " ori.\n";
}

CountryleJoc::~CountryleJoc() = default;
