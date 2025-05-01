#include "Application.hpp"
#include "Fichier.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <vector>

namespace fs = std::filesystem;

std::string Application::demander(const std::string& message) const {
    std::string reponse;
    std::cout << message;
    std::getline(std::cin, reponse);
    return reponse;
}

void Application::demarrer() {
    const std::vector<std::string> types = {"cesar", "xor", "vigenere"};

    const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "Erreur : impossible d'accéder au répertoire personnel (HOME)." << std::endl;
        return;
    }

    std::string dossierCles = std::string(home) + "/MesCles/";
    fs::create_directories(dossierCles); // crée ~/MesCles/ s’il n’existe pas

    std::cout << "=== Initialisation des clés ===" << std::endl;
    for (const std::string& type : types) {
        std::string nomFichier = type + ".cle";
        std::string cheminComplet = dossierCles + nomFichier;

        if (Fichier::fichierExiste(cheminComplet)) {
            std::string reponse = demander("Clé " + type + " trouvée. La charger ? (y/n) ");
            if (reponse == "y" || reponse == "Y") {
                try {
                    FichierCle fichierCle(cheminComplet);
                    cles[type] = *fichierCle.getCle();
                    std::cout << "Clé " << type << " chargée : " << cles[type].getValeur() << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erreur lors du chargement de la clé " << type << " : " << e.what() << std::endl;
                }
            }
        } else {
            std::string reponse = demander("Clé " + type + " non trouvée. Voulez-vous la créer ? (y/n) ");
            if (reponse == "y" || reponse == "Y") {
                std::string valeurCle = demander("Entrez la valeur pour la clé " + type + " : ");
                Cle nouvelleCle(valeurCle);
                cles[type] = nouvelleCle;

                std::ofstream fichier(cheminComplet);
                if (fichier.is_open()) {
                    fichier << valeurCle;
                    fichier.close();
                    std::cout << "Clé " << type << " enregistrée dans : " << cheminComplet << std::endl;
                } else {
                    std::cerr << "Erreur : impossible d’écrire la clé dans " << cheminComplet << std::endl;
                }
            }
        }
    }

    std::cout << "\n=== Menu principal ===" << std::endl;
    std::string action = demander("Voulez-vous chiffrer ou dechiffrer ? ");
    std::string cible = demander("Sur une phrase ou un fichier ? ");
    std::string algo = demander("Quel algorithme ? (cesar/xor/vigenere) ");

    if (cles.find(algo) == cles.end()) {
        std::cerr << "Clé " << algo << " non chargée. Abandon." << std::endl;
        return;
    }

    std::string texte;
    if (cible == "phrase") {
        texte = demander("Entrez la phrase : ");
    } else if (cible == "fichier") {
        std::string chemin = demander("Chemin du fichier : ");
        Fichier f(chemin);
        texte = f.lire();
    } else {
        std::cerr << "Option invalide." << std::endl;
        return;
    }

    Message* message = nullptr;
    if (algo == "cesar") message = new MCesar(texte);
    else if (algo == "xor") message = new MXOR(texte);
    else if (algo == "vigenere") message = new MVigenere(texte);

    if (message) {
        message->setCle(&cles[algo]);

        if (action == "chiffrer") {
            std::cout << "Texte chiffré :\n" << message->chiffrer() << std::endl;
        } else if (action == "dechiffrer") {
            std::cout << "Texte déchiffré :\n" << message->dechiffrer() << std::endl;
        } else {
            std::cerr << "Action invalide." << std::endl;
        }

        delete message;
    }
}