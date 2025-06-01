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
  static int nrShortestPathJucate;

  bool apartineDeDrum(const std::string& taraNoua) const;
  bool esteVecinaCuDrum(const std::string& taraNoua) const;

public:
  ShortestPathJoc();
  ShortestPathJoc(const ShortestPathJoc &other);
  ShortestPathJoc & operator=(const ShortestPathJoc &other);

  void porneste() override;
  void renunta() override;
  int getScor() override;
  std::string getNume() const override;
  void afisareDateRaspuns() override;

  static void cresteContorShortestPath();
  static void afiseazaNumarShortestPath();

  ~ShortestPathJoc() override;
};

#endif //SHORTESTPATHJOC_H