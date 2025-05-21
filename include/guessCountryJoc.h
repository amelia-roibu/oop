#ifndef GUESSCOUNTRYJOC_H
#define GUESSCOUNTRYJOC_H

#include "jocViteza.h"

class GuessCountryJoc : public JocViteza {
    static int nrGuessCountryJucate;
public:
    GuessCountryJoc();
    void porneste() override;
    std::pair<std::string, std::string> genereazaIntrebareRaspuns() override;
    void formateazaIntrebare(const std::string& prompt) const override;
    bool verificaRaspuns(const std::string& input, const std::string& corect) const override;
    std::string getNume() const override;
    static void afiseazaNumarGuessCountry();
    ~GuessCountryJoc() override;
};

#endif //GUESSCOUNTRYJOC_H
