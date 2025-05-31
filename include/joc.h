#ifndef JOC_H
#define JOC_H

#include <string>
#include <chrono>

class Joc {
protected:
  static std::string selectareContinent();

  std::chrono::steady_clock::time_point start_time;
  std::chrono::steady_clock::time_point end_time;
  static std::chrono::seconds durata_totala;

  static int numar_total_jocuri;
  bool jocInDesfasurare;
public:
  Joc();
  virtual void afisareDateRaspuns() = 0;
  virtual void porneste() = 0;
  virtual void renunta() = 0;
  virtual int getScor() = 0;
  virtual std::string getNume() const = 0;

  void startTime();
  virtual void stopTime();
  static void afiseazaDurataTotala();
  static void afiseazaNumarTotalJocuri();
  static void cresteContorJocuri();

  virtual ~Joc();
};

#endif //JOC_H
