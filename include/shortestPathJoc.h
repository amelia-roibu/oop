#ifndef SHORTESTPATHJOC_H
#define SHORTESTPATHJOC_H

#include <vector>
#include <string>
#include "joc.h"
#include "tari.h"

class ShortestPathJoc : public Joc {
  Tari taraStart, taraFinal;
  std::vector<Tari> drumOptim;
  std::vector<Tari> drumJucator;
  std::string continent;
  int scorLocal;

  std::vector<Tari> gasesteDrumBFS(const std::string& start, const std::string& final) const;
  bool apartineDeDrum(const std::string& taraNoua) const;
  bool esteVecinaCuDrum(const std::string& taraNoua) const;


public:
  ShortestPathJoc();
  void porneste() override;
  int getScor() override;
  std::string getNume() const override;
  void afisareDateRaspuns() override;
  ~ShortestPathJoc() override;
};

#endif //SHORTESTPATHJOC_H