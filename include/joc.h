#ifndef JOC_H
#define JOC_H

#include <string>

class Joc {
protected:
  static std::string selectareContinent();
  virtual void afisareDateRaspuns() = 0;

public:
  virtual void porneste() = 0;
  virtual int getScor() = 0;
  virtual std::string getNume() const = 0;
  virtual ~Joc();
};

#endif //JOC_H
