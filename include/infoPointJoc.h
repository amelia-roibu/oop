#ifndef INFOPOINTJOC_H
#define INFOPOINTJOC_H

#include "joc.h"
#include "tari.h"
#include <string>

class InfoPointJoc : public Joc {
    Tari taraInfo;
    int modJoc; // 0 = mod single, 1 = mod tur
    int scorLocal; // cate tari s au consultat
    std::string continent;
    static int nrInfoPointJucate;
    void modSingle();
public:
    InfoPointJoc();
    void porneste() override;
    void renunta() override;
    std::string getNume() const override;
    void afisareDateRaspuns() override;
    int getScor() override;
    void modExtins();

    static void cresteContorInfoPoint();
    static void afiseazaNumarInfoPoint();
    ~InfoPointJoc() override;
};

#endif
