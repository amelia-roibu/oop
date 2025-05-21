#include <iostream>
#include "../include/managerJoc.h"
#include "../include/countryle.h"
#include "../include/guessCapitalJoc.h"
#include "../include/guessCountryJoc.h"
#include "../include/shortestPathJoc.h"

ManagerJoc::ManagerJoc() : bazaDate(TariGlobal::getInstance()), scorTotal(0) {
  jocuriDisponibile.push_back(new CountryleJoc());
  jocuriDisponibile.push_back(new GuessCapitalJoc());
  jocuriDisponibile.push_back(new GuessCountryJoc());
  jocuriDisponibile.push_back(new ShortestPathJoc());
}

void ManagerJoc::porneste() {
  std::cout << "Bine ai venit la joculetele mele de geografie!\n";
  alegeJoc();
}

void ManagerJoc::afiseazaMeniu() const {
  std::cout << "Alege un joc (0 pentru iesire).\n";
  std::cout << "\n ============================= \n          Meniu Jocuri \n ============================= \n";
  std::cout << "0. Iesire\n";
  for (std::size_t i = 0; i < jocuriDisponibile.size(); i++)
    std::cout << i+1 << ". " << jocuriDisponibile[i]->getNume() << "\n";
  std::cout << " ============================= \n";
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
  std::cout << " ============================= \n";
  std::cout << "Scorul total acumulat: " << scorTotal << "\n";
  Joc::afiseazaDurataTotala();
  Joc::afiseazaNumarTotalJocuri();
  CountryleJoc::afiseazaNumarCountryle();
  GuessCapitalJoc::afiseazaNumarGuessCapital();
  GuessCountryJoc::afiseazaNumarGuessCountry();
  ShortestPathJoc::afiseazaNumarShortestPath();

}

// int ManagerJoc::getScorTotal() const {
//   return scorTotal;
// }

ManagerJoc::~ManagerJoc() {
  for (auto joc : jocuriDisponibile)
    delete joc;
}
