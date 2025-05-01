#ifndef FICHIER_HPP
#define FICHIER_HPP

#include <string>
#include <fstream>

class Fichier {
private:
    std::string nom;
    std::fstream fichier;

public:
    Fichier(const std::string& nomFichier);
    ~Fichier(); // Definition du destructeur pour fermer proprement le fichier

    void ecrire(const std::string& texte);
    std::string lire();
    void effacerContenu();
    void fermer();
    static bool fichierExiste(const std::string& cheminComplet);
};

#endif
