#include "../include/util.h"
#include <queue>
#include <unordered_set>
#include <map>
#include <algorithm>
#include "tariGlobal.h"

std::vector<Tari> gasesteDrumBFS(const std::string& start, const std::string& final) {
    std::queue<std::string> coada;
    coada.push(start);
    std::string current;

    std::unordered_set<std::string> vizitate;
    vizitate.insert(start);

    std::map<std::string, std::string> parinte;
    parinte[start] = "";

    while (!coada.empty()) {
        current = coada.front();
        coada.pop();

        if (current == final)
            break;

        auto vecini = TariGlobal::getInstance().getTara(current).getVeciniPeDirectie();
        for (const auto& vecin : vecini)
            if (!vizitate.contains(vecin)) {
                coada.push(vecin);
                vizitate.insert(vecin);
                parinte[vecin] = current;
            }
    }

    if (!parinte.contains(final))
        return {};

    std::vector<Tari> drum;
    current = final;
    while (!current.empty()) {
        drum.push_back(TariGlobal::getInstance().getTara(current));
        current = parinte[current];
    }

    std::ranges::reverse(drum.begin(), drum.end());
    return drum;
}

std::string toLower(const std::string &text) {
    std::string rezultat = text;
    std::ranges::transform(rezultat.begin(), rezultat.end(), rezultat.begin(), [](unsigned char c) { return std::tolower(c); });
    return rezultat;
}
