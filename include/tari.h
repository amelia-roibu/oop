#ifndef TARI_H
#define TARI_H

#include <string>
#include <vector>
#include <map>

class Tari{
  std::string nume;
  std::string capitala;
  std::string continent;
  std::string emisfera;
  double suprafata;
  double latitudine;
  double longitudine;
  std::map<std::string, std::vector<std::string>> veciniCardinal;
  // cheia poate fi doar "nord", "sud", "est", "vest"

public:
  Tari();
  Tari(const std::string& nume,
       const std::string& capitala,
       const std::string& continent,
       const std::string& emisfera,
       double suprafata,
       double latitudine,
       double longitudine,
       const std::map<std::string, std::vector<std::string>>& veciniCardinali);
  Tari(const Tari& other);
  Tari& operator= (const Tari& other);
  ~Tari();

  std::string getNume() const;
  std::string getCapitala() const;
  std::string getContinent() const;
  std::string getEmisfera() const;
  double getSuprafata() const;
  std::vector<std::string> getVeciniPeDirectie(const std::string& directie = "") const;
    // daca directia nu e data ca parametru, returneaza toti vecinii

  bool esteVecinCu(const std::string& numeTara) const;
  std::string directieFataDe(const Tari& alta) const;
  // util pt Countryle, unde se folosesc coordonatele pt a afla directia de la o tara la alta tara

  friend std::istream& operator>>(std::istream& in, Tari& tara);
  friend std::ostream& operator<<(std::ostream& out, const Tari& tara);
  bool operator== (const Tari& other) const;
  bool operator!= (const Tari& other) const;
  friend bool operator<(const Tari &lhs, const Tari &rhs); // aveam de gand sa l folosesc intr-un joc de tip Biggest vs Smallest, dar nu am mai apucat :(
};

#endif //TARI_H
