#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <map>
#include <string>
#include "Cle.hpp"
#include "Message.hpp"

class Application {
private:
    std::map<std::string, Cle> cles;

    void chargerOuCreerCles();
    void changerCles();
    void traiterMessage();
    void afficherCles();

public:
    void demarrer();
};

#endif