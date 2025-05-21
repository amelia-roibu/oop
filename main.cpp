#include <iostream>
#include "include/managerJoc.h"
#include "include/tariGlobal.h"

int main() {
    try {
        TariGlobal::getInstance();
        ManagerJoc manager;
        manager.porneste();
    } catch (const std::exception& e) {
        std::cerr << "Eroare la rulare: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
