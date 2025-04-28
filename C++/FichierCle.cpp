#include "FichierCle.hpp"


FichierCle::FichierCle(const std::string& nomFichierCle) : Fichier(nomFichierCle), cle(this->lire()) {}

const Cle* FichierCle::getCle() const {
    return &this->cle;
}
