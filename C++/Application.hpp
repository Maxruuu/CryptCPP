#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <map>
#include "Cle.hpp"
#include "FichierCle.hpp"
#include "Message.hpp"

class Application {
private:
    std::map<std::string, Cle> cles;

    bool fichierExiste(const std::string& nomFichier) const;
    std::string demander(const std::string& message) const;

public:
    void demarrer();
};

#endif // APPLICATION_HPP
