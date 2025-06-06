#ifndef JOCVITEZA_H
#define JOCVITEZA_H

#include <chrono>
#include <vector>
#include <string>
#include <unordered_set>
#include "joc.h"

class JocViteza : public Joc{
protected:
  int durataTimpSecunde;
  std::chrono::time_point<std::chrono::steady_clock> startTimp;
  std::vector<std::string> raspunsuriGhicite;
  std::vector<std::string> raspunsuriPierdute;
  std::unordered_set<std::string> obiecteFolosite;

  void seteazaTimp();
  bool timpExpirat() const;
  void afisareTimpRamas() const;
  void gestioneazaIntrebare();

  virtual void afisareInstructiuni() = 0;
  virtual std::pair<std::string, std::string> genereazaIntrebareRaspuns() = 0;
  virtual void formateazaIntrebare(const std::string& prompt) const = 0;
  virtual bool verificaRaspuns(const std::string& input, const std::string& corect) const = 0;

  void stopTime() override;

public:
  JocViteza();
  JocViteza(const JocViteza &other);
  JocViteza & operator=(const JocViteza &other);

  void porneste() override;
  void renunta() override;
  int getScor() override;void afisareDateRaspuns() override;
  ~JocViteza() override;
};

#endif //JOCVITEZA_H
