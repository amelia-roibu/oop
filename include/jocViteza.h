#ifndef JOCVITEZA_H
#define JOCVITEZA_H

#include <chrono>
#include <vector>
#include <string>
#include "joc.h"

class JocViteza : public Joc{
protected:
  int scorLocal, durataTimpSecunde;
  std::string continent;
  std::chrono::time_point<std::chrono::steady_clock> startTimp;
  std::vector<std::string> raspunsuriGhicite;
  std::vector<std::string> raspunsuriPierdute;


  void seteazaTimp();
  bool timpExpirat() const;

  virtual std::pair<std::string, std::string> genereazaIntrebareRaspuns() = 0;
  virtual void formateazaIntrebare(const std::string& prompt) const = 0;
  virtual bool verificaRaspuns(const std::string& input, const std::string& corect) const = 0;


public:
  JocViteza();
  void porneste() override;
  int getScor() override;void afisareDateRaspuns() override;
  ~JocViteza() override;
};

#endif //JOCVITEZA_H
