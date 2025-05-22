#include "../include/tari.h"
#include "../include/tariGlobal.h"
#include "../include/util.h"

// constructori

Tari::Tari() : nume(""), capitala(""), continent(""), emisfera(""), suprafata(0.0), latitudine(0.0), longitudine(0.0), veciniCardinal{} {}

Tari::Tari(const std::string& nume,
           const std::string& capitala,
           const std::string& continent,
           const std::string& emisfera,
           double suprafata,
           double latitudine,
           double longitudine,
           const std::map<std::string, std::vector<std::string>>& veciniCardinal) : nume(nume), capitala(capitala), continent(continent), emisfera(emisfera), suprafata(suprafata), latitudine(latitudine), longitudine(longitudine), veciniCardinal(veciniCardinal) {}

Tari::Tari(const Tari& other) : nume(other.nume), capitala(other.capitala), continent(other.continent), emisfera(other.emisfera), suprafata(other.suprafata), latitudine(other.latitudine), longitudine(other.longitudine), veciniCardinal(other.veciniCardinal) {}

Tari& Tari::operator=(const Tari& other) {
    if (this != &other) {
        nume = other.nume;
        capitala = other.capitala;
        continent = other.continent;
        emisfera = other.emisfera;
        suprafata = other.suprafata;
        latitudine = other.latitudine;
        longitudine = other.longitudine;
        veciniCardinal = other.veciniCardinal;
    }
    return *this;
}

Tari::~Tari() = default;

// getters

std::string Tari::getNume() const {
  return this->nume;
}

std::string Tari::getCapitala() const {
    return this->capitala;
}
std::string Tari::getContinent() const {
    return this->continent;
}
std::string Tari::getEmisfera() const {
    return this->emisfera;
}
double Tari::getSuprafata() const {
    return this->suprafata;
}

std::vector<std::string> Tari::getVeciniPeDirectie(const std::string& directie) const {

  // try and catch directie invalida

  if (!directie.empty()){
    auto it = veciniCardinal.find(directie);
    if (it != veciniCardinal.end())
        return it->second;
    throw std::invalid_argument("Directie invalida");
  }

  std::vector<std::string> totiVecinii;
  for (const auto& [dir, vecini] : veciniCardinal)
    totiVecinii.insert(totiVecinii.end(), vecini.begin(), vecini.end());
  return totiVecinii;
}

// alte metode

bool Tari::esteVecinCu(const std::string& numeTara) const{
    for (const auto& [dir, vecini] : veciniCardinal)
      for (const auto& vecin : vecini)
        if (toLower(vecin) == toLower(numeTara))
          return true;
    return false;
}

std::string Tari::directieFataDe(const Tari& other) const {
    double diffLatitudine = other.latitudine - this->latitudine;
    double diffLongitudine = other.longitudine - this->longitudine;
    const double marja = 0.7;

    std::string directieVerticala = "";
    std::string directieOrizontala = "";

    if (diffLatitudine > marja) directieVerticala = "Nord";
    if (diffLatitudine < -marja) directieVerticala = "Sud";

    if (diffLongitudine > marja) directieOrizontala = "Est";
    if (diffLongitudine < -marja) directieOrizontala = "Vest";

    if (!directieVerticala.empty() && !directieOrizontala.empty())
        return directieVerticala + "-" + directieOrizontala;
    if (directieVerticala.empty() && !directieOrizontala.empty())
        return directieOrizontala;
    return directieVerticala;
}

// operatori

std::istream& operator>>(std::istream& in, Tari& tara) {
    std::string nume;
    std::getline(in, nume);

    const TariGlobal& bazaDate = TariGlobal::getInstance();
    if (!bazaDate.existaTara(nume))
        throw std::invalid_argument("Tara introdusa nu exista.");

    tara = TariGlobal::getInstance().getTara(nume);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Tari& tara) {
    out << "Capitala: " << tara.capitala << "\n";
    out << "Continent: " << tara.continent << "\n";
    out << "Emisfera: " << tara.emisfera << "\n";
    out << "Suprafata: " << tara.suprafata << "\n";

    std::vector<std::string> directii = {"Nord", "Sud", "Est", "Vest"};
    bool areVecini = false;

    out << "Vecini: \n";
    for (const auto& directie : directii) {
        auto vecini = tara.getVeciniPeDirectie(directie);
        if (!vecini.empty()) {
            areVecini = true;
            out << "  " << directie << ": ";
            for (std::size_t i = 0; i < vecini.size(); ++i)
                out << vecini[i] << "; ";
            out << "\n";
        }
    }
    if (!areVecini)
        out << "  Este o tara insulara (nu are vecini).\n";
    return out;
}

bool Tari::operator== (const Tari& other) const {
  return toLower(this->nume) == toLower(other.nume);
}

bool Tari::operator!= (const Tari& other) const {
    return !(*this == other);
  }