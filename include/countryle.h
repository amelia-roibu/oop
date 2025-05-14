#ifndef COUNTRYLE_H
#define COUNTRYLE_H

#include <string>
#include "joc.h"
#include "tari.h"

class CountryleJoc : public Joc {
  Tari taraTinta;
  int scorLocal, nrIncercari;
  std::string continent;
public:
  CountryleJoc();
  void porneste() override;
  int getScor() override;
  std::string getNume() const override;
  void afisareDateRaspuns(const Tari& tara) override;
  void afisareFinala() const;
  void bonusVecin(const std::string& tara);
  ~CountryleJoc() override;
};

#endif //COUNTRYLE_H
