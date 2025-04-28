#include "Cle.hpp"

Cle::Cle(const std::string& valeur) : valeur(valeur) {}

const std::string Cle::getValeur() const {
    return this->valeur;
}