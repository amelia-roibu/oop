#ifndef JOC_H
#define JOC_H

#include <string>
#include <chrono>

class Joc {
protected:
  std::chrono::steady_clock::time_point start_time;
  std::chrono::steady_clock::time_point end_time; // astea 3 pt calcularea statisticilor
  static std::chrono::seconds durata_totala;
  static int numar_total_jocuri; // si asta tot pt statistici
  bool jocInDesfasurare;
  int scorLocal;
  std::string continent;

  static std::string selectareContinent();
public:
  Joc();
  Joc(const Joc &other);
  Joc& operator=(const Joc &other);

  virtual void afisareDateRaspuns() = 0; // fiecare joc are alt format de a afisa informatii dupa ce este dat un raspuns ca input
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
