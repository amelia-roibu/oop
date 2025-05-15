#ifndef MANAGERJOC_H
#define MANAGERJOC_H

#include "../include/tariGlobal.h"
#include "../include/joc.h"

class ManagerJoc {
  // Utilizator utilizatorCurent;
  std::vector<Joc*> jocuriDisponibile;
  TariGlobal& bazaDate;
  int scorTotal;
public:
  ManagerJoc();
  void porneste();
  void afiseazaMeniu() const;
  void alegeJoc();
  int getScorTotal() const;
  ~ManagerJoc();
};

#endif //MANAGERJOC_H
