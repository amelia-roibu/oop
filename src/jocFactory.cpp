#include "../include/jocFactory.h"
#include "../include/guessCapitalJoc.h"
#include "../include/guessCountryJoc.h"
#include "../include/countryle.h"
#include "../include/shortestPathJoc.h"

Joc* JocFactory::creeazaJoc(int optiune) {
    switch (optiune) {
        case 1: return new CountryleJoc();
        case 2: return new GuessCapitalJoc();
        case 3: return new GuessCountryJoc();
        case 4: return new ShortestPathJoc();
        default: return nullptr;
    }
}