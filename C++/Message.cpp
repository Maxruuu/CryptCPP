#include "Message.hpp"
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>

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

/*===========================
    AES
=============================*/

MAES::MAES(const std::string& texte) : Message(texte) {}

std::string MAES::chiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        std::string key = this->getCle()->getValeur();
        unsigned char iv[16]; // Initialisation vector
        RAND_bytes(iv, sizeof(iv)); // Génère un IV aléatoire

        unsigned char ciphertext[this->clair.size() + 16];
        int len = 0, ciphertext_len = 0;

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) {
            std::cerr << "Erreur : Impossible d'initialiser le contexte AES." << std::endl;
            return "";
        }

        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), iv) != 1) {
            std::cerr << "Erreur : Impossible d'initialiser le chiffrement AES." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }

        if (EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)this->clair.c_str(), this->clair.size()) != 1) {
            std::cerr << "Erreur : Impossible de chiffrer les données." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }
        ciphertext_len = len;

        if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
            std::cerr << "Erreur : Impossible de finaliser le chiffrement." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }
        ciphertext_len += len;

        EVP_CIPHER_CTX_free(ctx);

        // Ajoute l'IV au début du résultat pour le stockage
        resultat = std::string((char*)iv, sizeof(iv)) + std::string((char*)ciphertext, ciphertext_len);
    } else {
        std::cerr << "Impossible de chiffrer (AES) : Clé non définie." << std::endl;
    }

    return resultat;
}

std::string MAES::dechiffrer() const {
    std::string resultat;

    if (this->getCle()) {
        std::string key = this->getCle()->getValeur();

        if (this->clair.size() < 16) {
            std::cerr << "Erreur : Données chiffrées invalides." << std::endl;
            return "";
        }

        unsigned char iv[16];
        std::memcpy(iv, this->clair.c_str(), 16); // Récupère l'IV depuis le début des données chiffrées

        unsigned char plaintext[this->clair.size()];
        int len = 0, plaintext_len = 0;

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) {
            std::cerr << "Erreur : Impossible d'initialiser le contexte AES." << std::endl;
            return "";
        }

        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), iv) != 1) {
            std::cerr << "Erreur : Impossible d'initialiser le déchiffrement AES." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }

        if (EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)this->clair.c_str() + 16, this->clair.size() - 16) != 1) {
            std::cerr << "Erreur : Impossible de déchiffrer les données." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }
        plaintext_len = len;

        if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1) {
            std::cerr << "Erreur : Impossible de finaliser le déchiffrement." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }
        plaintext_len += len;

        EVP_CIPHER_CTX_free(ctx);

        resultat = std::string((char*)plaintext, plaintext_len);
    } else {
        std::cerr << "Impossible de déchiffrer (AES) : Clé non définie." << std::endl;
    }

    return resultat;
}