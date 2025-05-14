#ifndef TARIGLOBAL_H
#define TARIGLOBAL_H

#pragma once

#include <map>
#include <string>
#include <vector>
#include "../include/tari.h"

class TariGlobal {
    std::map<std::string, Tari> tari;
    static TariGlobal* instanta;

// constructor
    TariGlobal();

public:
// getters
    static TariGlobal& getInstance();
    const Tari& getTara(const std::string& nume) const;
    std::vector<Tari> getTariDinContinent(const std::string& continent) const;
    std::vector<Tari> getTariRandom(int nr, const std::string& continent = "") const;
    bool existaTara(const std::string& nume) const;
};

#endif //TARIGLOBAL_H