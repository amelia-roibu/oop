#include <iostream>
#include "../include/validareInput.h"
#include "../include/exception.h"
#include "../include/managerJoc.h"
#include "../include/countryle.h"
#include "../include/guessCapitalJoc.h"
#include "../include/guessCountryJoc.h"
#include "../include/shortestPathJoc.h"
#include "../include/infoPointJoc.h"
#include "../include/jocFactory.h"

ManagerJoc::ManagerJoc() : bazaDate(TariGlobal::getInstance()), scorTotal(0) {
  for (int i = 1; i <= 5; i++) {
    try {
      std::shared_ptr<Joc> joc = JocFactory::creeazaJoc(i);
      if (joc) jocuriDisponibile.push_back(joc);
    } catch (const ExceptieJocInvalid&) {
      std::cout << "Eroare la incarcarea jocului. " << '\n';
    }

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
    int optiune = ValidareInput<int>::citesteValoare(0, static_cast<int>(jocuriDisponibile.size()));
    if (optiune == 0) break;
    std::string raspuns = "y";
    std::shared_ptr<Joc> joc = jocuriDisponibile[optiune - 1];

    auto jocInfo = std::dynamic_pointer_cast<InfoPointJoc>(joc);

    while (raspuns == "y") {
      try{
        if (jocInfo)
          jocInfo->modExtins();
        else
          joc->porneste();
        scorTotal += joc->getScor();
      } catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\nJocul s-a oprit din cauza unei erori.\n\n";
      }
      std::cout << "Vrei sa mai joci o data " << joc->getNume() << "? [y/n] \n";
      raspuns = ValidareInput<std::string>::citesteValoare({"y", "n"}, "Optiune invalida. Incearca din nou.\n");
    }
  }
  std::cout << " ============================= \n";
  std::cout << "Scorul total acumulat: " << scorTotal << "\n";
  Joc::afiseazaDurataTotala();
  Joc::afiseazaNumarTotalJocuri();
  CountryleJoc::afiseazaNumarCountryle();
  GuessCapitalJoc::afiseazaNumarGuessCapital();
  GuessCountryJoc::afiseazaNumarGuessCountry();
  ShortestPathJoc::afiseazaNumarShortestPath();
  InfoPointJoc::afiseazaNumarInfoPoint();
}

ManagerJoc::~ManagerJoc() = default;
