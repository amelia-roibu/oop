#include "../include/jocFactory.h"
#include "../include/exception.h"
#include "../include/guessCapitalJoc.h"
#include "../include/guessCountryJoc.h"
#include "../include/countryle.h"
#include "../include/shortestPathJoc.h"
#include "../include/infoPointJoc.h"

std::shared_ptr<Joc> JocFactory::creeazaJoc(int optiune) {
    switch (optiune) {
        case 1: return std::make_shared<CountryleJoc>();
        case 2: return std::make_shared<GuessCapitalJoc>();
        case 3: return std::make_shared<GuessCountryJoc>();
        case 4: return std::make_shared<ShortestPathJoc>();
        case 5: return std::make_shared<InfoPointJoc>();
        default: throw ExceptieJocInvalid("Nu exista un joc cu acest index.");
    }
}