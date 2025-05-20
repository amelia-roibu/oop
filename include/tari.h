#ifndef TARI_H
#define TARI_H

#pragma once

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
  // constructori
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

  // getters
  std::string getNume() const;
  std::string getCapitala() const;
  std::string getContinent() const;
  std::string getEmisfera() const;
  double getSuprafata() const;
  // double getLatitudine() const;
  // double getLongitudine() const;
  std::vector<std::string> getVeciniPeDirectie(const std::string& directie = "") const;

  // alte metode
  bool esteVecinCu(const std::string& numeTara) const;
  std::string directieFataDe(const Tari& alta) const;


  // operatori
  friend std::istream& operator>>(std::istream& in, Tari& tara);
  friend std::ostream& operator<<(std::ostream& out, const Tari& tara);
  bool operator== (const Tari& other) const;
  bool operator!= (const Tari& other) const;
};

#endif //TARI_H
