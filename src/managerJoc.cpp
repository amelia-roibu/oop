#include <iostream>
#include "../include/managerJoc.h"
#include "../include/countryle.h"
#include "../include/guessCapitalJoc.h"
#include "../include/guessCountryJoc.h"

ManagerJoc::ManagerJoc() : bazaDate(TariGlobal::getInstance()), scorTotal(0) {
  jocuriDisponibile.push_back(new CountryleJoc());
  jocuriDisponibile.push_back(new GuessCapitalJoc());
  jocuriDisponibile.push_back(new GuessCountryJoc());
}

void ManagerJoc::porneste() {
  std::cout << "Bine ai venit la joculetele mele de geografie!\n";
  alegeJoc();
}

void ManagerJoc::afiseazaMeniu() const {
  std::cout << "Alege un joc (0 pentru iesire).\n";
  std::cout << "\n ============================= \n          Meniu Jocuri \n ============================= \n";
  std::cout << "0. Iesire\n";
  for (auto i = 0; i < jocuriDisponibile.size(); i++)
    std::cout << i+1 << ". " << jocuriDisponibile[i]->getNume() << "\n";
}

void ManagerJoc::alegeJoc() {
  while (true) {
    afiseazaMeniu();
    int optiune;
    std::cin >> optiune;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (optiune == 0) break;
    if (optiune > 0 && static_cast<size_t>(optiune) <= jocuriDisponibile.size()) {
      char raspuns = 'y';
      Joc* joc = jocuriDisponibile[optiune - 1];
      while (raspuns == 'y') {
        joc->porneste();
        scorTotal += joc->getScor();
        std::cout << "Vrei sa mai joci o data " << joc->getNume() << "? [y/n] \n";
        std::cin >> raspuns;
      }
    }
    else
      std::cout << "Optiune invalida.\n";
  }
  std::cout << "\n Scorul total acumulat: " << scorTotal << "\n";
}

int ManagerJoc::getScorTotal() const {
  return scorTotal;
}

ManagerJoc::~ManagerJoc() {
  for (auto joc : jocuriDisponibile)
    delete joc;
}
