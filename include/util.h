#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include "tari.h"

inline Tari citesteTaraDinConsola() {
    std::string linie;
    std::getline(std::cin, linie);

    if (linie == "renunt")
        throw std::runtime_error("Utilizatorul a renuntat.");

    if (linie == "pas")
        throw std::logic_error("Utilizatorul a trecut peste intrebare.");

    std::istringstream stream(linie);
    Tari tara;
    stream >> tara;
    return tara;
}

std::vector<Tari> gasesteDrumBFS(const std::string& start, const std::string& final);

template <typename T>
T alegeRandom(const std::vector<T>& v) {
    if (v.empty())
        throw std::out_of_range("Vectorul este gol.");

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, static_cast<int>(v.size() - 1));

    return v[distrib(gen)];
}

// template <typename T>
// std::vector<T> alegeRandomMultiple(const std::vector<T>& v, std::size_t n) {
//     if (v.empty())
//         throw std::out_of_range("Vectorul este gol.");
//
//     std::vector<T> copie = v;
//
//     static std::random_device rd; // genereaza un generator de entropie din surse externe, un fel de seed aleator, mai bun decat rand()
//     static std::mt19937 gen(rd());
//     /* mt19937 e un motor de generare de numere pseudo-aleatoare; numele vine de la „Mersenne Twister”
//     primește seed de la rd() — deci va genera o secvență diferită de fiecare dată când rulezi programul. */
//
//     std::shuffle(copie.begin(), copie.end(), gen);
//
//     if (n > copie.size()) n = copie.size();
//     return std::vector<T>(copie.begin(), copie.begin() + n);
// }