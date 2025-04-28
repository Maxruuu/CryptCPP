#ifndef FICHIERCLE_HPP
#define FICHIERCLE_HPP

#include "Fichier.hpp"
#include "Cle.hpp"

class FichierCle : public Fichier {
private:
    Cle cle; // objet Cle

public:
    FichierCle(const std::string& nomFichier);
    const Cle* getCle() const;

};

#endif
