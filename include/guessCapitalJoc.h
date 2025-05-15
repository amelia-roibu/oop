#ifndef GUESSCAPITALJOC_H
#define GUESSCAPITALJOC_H

#include "jocViteza.h"

class GuessCapitalJoc : public JocViteza {
public:
  GuessCapitalJoc();
  std::pair<std::string, std::string> genereazaIntrebareRaspuns() override;
  void formateazaIntrebare(const std::string& prompt) const override;
  bool verificaRaspuns(const std::string& input, const std::string& corect) const override;
  std::string getNume() const override;
  ~GuessCapitalJoc() override;
};

#endif //GUESSCAPITALJOC_H
