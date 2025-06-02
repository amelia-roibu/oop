#ifndef VALIDAREINPUT_H
#define VALIDAREINPUT_H

#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <limits>
#include "util.h"

template <typename T>
class ValidareInput {
public:
  static T citesteValoare(T valoareMinima, T valoareMaxima, const std::string& mesajEroare = "Input invalid! Incearca din nou.\n") {
    T valoare;
    while (true) {
      std::cin >> valoare;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << mesajEroare; // daca crapa citirea
        continue;
      }

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignora caracterul \0
      if (valoareMinima > valoare || valoareMaxima < valoare) {
        std::cout << mesajEroare << " Valoarea trebuie sa fie intre " << valoareMinima << " si " << valoareMaxima << "!\n";
        continue;
      }
      return valoare;
    }
  }
};

template <> // specializarea template ului
class ValidareInput<std::string> {
public:
  static std::string citesteValoare(const std::vector<std::string>& optiuniValide, const std::string& mesajEroare = "Input invalid! Incearca din nou.\n") {
    std::string input;
    while (true) {
      std::getline(std::cin, input);
      input = toLower(input);

      input.erase(0, input.find_first_not_of(" \t\r\n")); // sterge caracterele inutile de la inceput
      input.erase(input.find_last_not_of(" \t\r\n") + 1); // si de la final

      if (std::ranges::find(optiuniValide.begin(), optiuniValide.end(), input) != optiuniValide.end())
        return input;
      std::cout << mesajEroare;
    }
  }
};
#endif