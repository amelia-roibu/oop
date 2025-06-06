#ifndef MANAGERJOC_H
#define MANAGERJOC_H

#include <memory>
#include "../include/tariGlobal.h"
#include "../include/joc.h"

class ManagerJoc {
  std::vector<std::shared_ptr<Joc>> jocuriDisponibile;
  TariGlobal& bazaDate;
  int scorTotal;
public:
  ManagerJoc();
  void porneste();
  void afiseazaMeniu() const;
  void alegeJoc();
  ~ManagerJoc();
};

#endif //MANAGERJOC_H
