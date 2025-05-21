#include "Fichier.hpp"
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Fichier::Fichier(const std::string& nomFichier) : nom(nomFichier) {
    fichier.open(nom, std::ios::in | std::ios::out);
    if (!fichier.is_open()) std::cerr << "Attention ! Le fichier " << nomFichier << " n'existe pas." << std::endl;
}

Fichier::~Fichier() {
    this->fermer();
}

void Fichier::ecrire(const std::string& texte) {
    if (fichier.is_open()) {
        fichier.clear(); // Clear les flags fichier 'eof' par exemple
        fichier.seekg(0, std::ios::end); // Positionne en fin de fichier

        fichier << texte;
    }
}

std::string Fichier::lire() {
    std::string output, buff;

    if (fichier.is_open()) {
        fichier.clear();
        fichier.seekg(0, std::ios::beg); // Positionne au début de fichier

        while(std::getline(fichier, buff)) { // On met une ligne dans le buffer
            output += buff + "\n"; // On rajoute la ligne à notre string de sortie
        }
    }
    return output;
}

void Fichier::effacerContenu() {
    if (fichier.is_open()) {
        fichier.close();
    }

    fichier.open(nom, std::ios::out | std::ios::trunc);
    fichier.close();
    fichier.open(nom, std::ios::in | std::ios::out);
}

void Fichier::fermer() {
    if (fichier.is_open()) {
        fichier.close();
    }
}

bool Fichier::fichierExiste(const std::string& cheminComplet) {
    return fs::exists(cheminComplet);
}
