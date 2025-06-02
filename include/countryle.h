#ifndef COUNTRYLE_H
#define COUNTRYLE_H

#include <string>
#include "joc.h"
#include "tari.h"

class CountryleJoc : public Joc {
  Tari taraTinta, taraInput;
  int nrIncercari;

  static int nrCountryleJucate;
public:
  CountryleJoc();
  CountryleJoc(const CountryleJoc& other);
  CountryleJoc& operator=(const CountryleJoc& other);

  void afisareDateRaspuns() override;
  void porneste() override;
  void renunta() override;
  int getScor() override;
  std::string getNume() const override;

  void afisareFinala() const;
  void bonusVecin(const std::string& tara);

  static void cresteContorCountryle();
  static void afiseazaNumarCountryle();

  ~CountryleJoc() override;
};

#endif //COUNTRYLE_H
