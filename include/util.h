#pragma once
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include "tari.h"

Tari citesteTaraDinConsola();

std::vector<Tari> gasesteDrumBFS(const std::string& start, const std::string& final);

std::string toLower(const std::string& text);

template <typename T>
T alegeRandom(const std::vector<T>& v) {
    if (v.empty())
        throw std::out_of_range("Vectorul este gol.");

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, static_cast<int>(v.size() - 1));

    return v[distrib(gen)];
}