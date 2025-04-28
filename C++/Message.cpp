#include "Message.hpp"
#include <iostream>

/*===========================
    Message
=============================*/

Message::Message(const std::string& texte) : clair(texte), cle(nullptr) {}

void Message::setCle(Cle* nouvelleCle) {
    cle = nouvelleCle;
}

const Cle* Message::getCle() const {
    return this->cle;
}

/*===========================
    Cesar
=============================*/

MCesar::MCesar(const std::string& texte) : Message(texte) {}

std::string MCesar::chiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        int decalage = stoi(this->getCle()->getValeur());

        for (char c : this->clair) {
            if (std::isalpha(c)) {
                char base = std::islower(c) ? 'a' : 'A'; // Pour garder les majuscules en majuscule et vice versa
                resultat += (c - base + decalage) % 26 + base;

            } else {
                resultat += c;
            }
        }
    }
    else {
        std::cerr << "Impossible de chiffrer (Cesar) : Clé non définie." << std::endl;
    }

    return resultat;
}

std::string MCesar::dechiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        int decalage = stoi(this->getCle()->getValeur());

        for (char c : this->clair) {
            if (std::isalpha(c)) {
                char base = std::islower(c) ? 'a' : 'A'; 
                resultat += (c - base - decalage + 26) % 26 + base;
            } else {
                resultat += c;
            }
        }
    }
    else {
        std::cerr << "Impossible de déchiffrer (Cesar) : Clé non définie." << std::endl;
    }

    return resultat;
}

/*===========================
    XOR
=============================*/

MXOR::MXOR(const std::string& texte) : Message(texte) {}

std::string MXOR::chiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        std::string key = this->getCle()->getValeur();

        for (size_t i = 0; i < this->clair.size(); ++i) {
            resultat += this->clair[i] ^ key[i % key.size()];
        }
    }
    else {
        std::cerr << "Impossible de chiffrer (XOR) : Clé non définie." << std::endl;
    }

    return resultat;
}

std::string MXOR::dechiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        std::string key = this->getCle()->getValeur();

        for (size_t i = 0; i < this->clair.size(); ++i) {
            resultat += this->clair[i] ^ key[i % key.size()];
        }
    }
    else {
        std::cerr << "Impossible de déchiffrer (XOR) : Clé non définie." << std::endl;
    }

    return resultat;
}

/*===========================
    Vigenere
=============================*/

MVigenere::MVigenere(const std::string& texte) : Message(texte) {}

std::string MVigenere::chiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        std::string key = this->getCle()->getValeur();

        for (size_t i = 0; i < this->clair.size(); ++i) {
            if (std::isalpha(this->clair[i])) {
                char base = std::islower(this->clair[i]) ? 'a' : 'A';
                char keyChar = std::tolower(key[i % key.size()]) - 'a';
                resultat += (this->clair[i] - base + keyChar) % 26 + base;
            } else {
                resultat += this->clair[i];
            }
        }
    }
    else {
        std::cerr << "Impossible de chiffrer (Vigenere) : Clé non définie." << std::endl;
    }

    return resultat;
}

std::string MVigenere::dechiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        std::string key = this->getCle()->getValeur();

        for (size_t i = 0; i < this->clair.size(); ++i) {
            if (std::isalpha(this->clair[i])) {
                char base = std::islower(this->clair[i]) ? 'a' : 'A';
                char keyChar = std::tolower(key[i % key.size()]) - 'a';
                resultat += (this->clair[i] - base - keyChar + 26) % 26 + base;
            } else {
                resultat += this->clair[i];
            }
        }
    }
    else {
        std::cerr << "Impossible de déchiffrer (Vigenere) : Clé non définie." << std::endl;
    }

    return resultat;
}