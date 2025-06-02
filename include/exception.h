#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class ExceptieJoc : public std::exception {
protected:
    std::string mesaj;
public:
    explicit ExceptieJoc(std::string msg) : mesaj(std::move(msg)) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class ExceptieFisier : public ExceptieJoc {
public:
    explicit ExceptieFisier (const std::string& fisier)
        : ExceptieJoc("a aparut o eroare in deschiderea fisierului " + fisier) {}
};

class ExceptieParsareJson : public ExceptieJoc {
public:
    explicit ExceptieParsareJson(const std::string& detalii)
        : ExceptieJoc("a aparut o eroare in timpul parsarii din JSON: " + detalii) {}
};

class ExceptieDirectieInvalida : public ExceptieJoc {
public:
    explicit ExceptieDirectieInvalida(const std::string& directie)
        : ExceptieJoc("Directie invalida: " + directie) {}
};


class ExceptieTaraInexistenta : public ExceptieJoc {
public:
    explicit ExceptieTaraInexistenta(const std::string& tara)
        : ExceptieJoc("Tara inexistenta: " + tara + "\n") {}
};

class ExceptieJocInvalid : public ExceptieJoc {
public:
    explicit ExceptieJocInvalid(const std::string& detalii)
        : ExceptieJoc("Joc invalid: " + detalii) {}
};

class ExceptieTimeoutUtilizator : public ExceptieJoc {
public:
    ExceptieTimeoutUtilizator()
        : ExceptieJoc("Timpul a expirat!") {}
};

class ExceptieRenuntare : public ExceptieJoc {
public:
    ExceptieRenuntare() : ExceptieJoc("Utilizatorul a renuntat") {}
};

#endif