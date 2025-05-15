#include <iostream>
#include <limits>
#include "../include/joc.h"
#include "../include/tariGlobal.h"

std::string Joc::selectareContinent() {
    std::string continent = "";
    std::cout << "Doresti sa alegi continentul de pe care sa joci? [y/n] \n";
    char alegere;
    std::cin >> alegere;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (alegere == 'y') {
        std::cout << "Alege continentul: [Europa / Africa / Asia / America de Nord / America de Sud / Oceania] \n";
        std::getline(std::cin, continent);
        if (TariGlobal::getInstance().getTariDinContinent(continent).empty()) {
            std::cout << "Continent invalid. Se va selecta aleatoriu. Sorry!\n";
            continent = "";
        }
    }
    else {
        std::cout << "In regula. \n";
    }
    return continent;
}

Joc::~Joc() = default;