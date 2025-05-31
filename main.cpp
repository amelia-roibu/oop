#include <iostream>
#include "include/managerJoc.h"
#include "include/exception.h"

int main() {
    try {
        ManagerJoc manager;
        manager.porneste();
    } catch (const ExceptieFisier& e) {
        std::cerr << "Eroare la deschiderea fisierului: " << e.what() << "\n";
        return 1;
    } catch (const ExceptieParsareJson& e) {
        std::cerr << "Eroare de parsare: " << e.what() << '\n';
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Eroare la rulare: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
