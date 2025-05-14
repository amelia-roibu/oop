#ifndef JOC_H
#define JOC_H

#include <string>
#include "tari.h"

class Joc {
public:
  virtual void porneste() = 0;
  virtual int getScor() = 0;
  virtual std::string getNume() const = 0;
  virtual void afisareDateRaspuns(const Tari& tara) = 0;
  virtual ~Joc();
};

#endif //JOC_H
