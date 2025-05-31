#include <iostream>
#include "../include/managerJoc.h"
#include "../include/countryle.h"
#include "../include/guessCapitalJoc.h"
#include "../include/guessCountryJoc.h"
#include "../include/shortestPathJoc.h"
#include "../include/jocFactory.h"

ManagerJoc::ManagerJoc() : bazaDate(TariGlobal::getInstance()), scorTotal(0) {
  for (int i = 0; i < 5; i++) {
    Joc* joc = JocFactory::creeazaJoc(i);
    if (joc) jocuriDisponibile.push_back(joc);
  }
}

void ManagerJoc::porneste() {
  std::cout << "\nBine ai venit la joculetele mele de geografie!\n";
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
    if (optiune == 0) break;
    if (optiune > 0 && static_cast<size_t>(optiune) <= jocuriDisponibile.size()) {
      std::string raspuns = "y";
      Joc* joc = jocuriDisponibile[optiune - 1];
      while (raspuns == "y") {
        joc->porneste();
        scorTotal += joc->getScor();
        std::cout << "Vrei sa mai joci o data " << joc->getNume() << "? [y/n] \n";
        std::cin >> raspuns;
        while (raspuns != "y" && raspuns != "n") {
          std::cout << "Optiune invalida. Incearca din nou.\n";
          std::cin >> raspuns;
        }
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
