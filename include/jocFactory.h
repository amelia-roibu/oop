#ifndef JOCFACTORY_H
#define JOCFACTORY_H

#include <memory>
#include "joc.h"

class JocFactory {
public:
    static std::shared_ptr<Joc> creeazaJoc(int optiune);
};

#endif //JOCFACTORY_H
