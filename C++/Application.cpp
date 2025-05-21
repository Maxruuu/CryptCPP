#include "Application.hpp"
#include "Window.hpp"
#include "Fichier.hpp"
#include "FichierCle.hpp"

#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

bool estEntier(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void Application::chargerOuCreerCles() {
    const std::vector<std::string> types = {"cesar", "xor", "vigenere", "aes"};
    const char* home = std::getenv("HOME");
    std::string dossierCles = std::string(home) + "/MesCles/";
    fs::create_directories(dossierCles);

    for (const auto& type : types) {
        std::string cheminComplet = dossierCles + type + ".cle";
        if (Fichier::fichierExiste(cheminComplet)) {
            WindowMenu menu("Clé trouvée pour " + type, {"La charger", "En entrer une nouvelle"});
            menu.show();
            if (menu.getChoice() == 3) continue;

            if (menu.getChoice() == 1) {
                FichierCle fichierCle(cheminComplet);
                cles[type] = *fichierCle.getCle();
            } else {
                WindowForm form("Nouvelle clé pour " + type, {"Valeur"});
                form.show();
                std::string val = form.getAnswer().at("Valeur");

                if (type == "cesar" && !estEntier(val)) {
                    WindowInfo err("Erreur", {"La clé César doit être un entier."});
                    err.show();
                    continue;
                }
                if (type == "aes" && val.size() != 32) {
                    WindowInfo err("Erreur", {"La clé AES doit contenir exactement 32 caractères."});
                    err.show();
                    continue;
                }

                cles[type] = Cle(val);
                std::ofstream fichier(cheminComplet);
                fichier << val;
            }
        } else {
            WindowForm form("Aucune clé trouvée pour " + type + ". Veuillez en entrer une.", {"Valeur"});
            form.show();
            std::string val = form.getAnswer().at("Valeur");

            if (type == "cesar" && !estEntier(val)) {
                WindowInfo err("Erreur", {"La clé César doit être un entier."});
                err.show();
                continue;
            }
            if (type == "aes" && val.size() != 32) {
                WindowInfo err("Erreur", {"La clé AES doit contenir exactement 32 caractères."});
                err.show();
                continue;
            }

            cles[type] = Cle(val);
            std::ofstream fichier(cheminComplet);
            fichier << val;
        }
    }
}

void Application::changerCles() {
    const std::vector<std::string> types = {"cesar", "xor", "vigenere", "aes"};
    const char* home = std::getenv("HOME");
    std::string dossierCles = std::string(home) + "/MesCles/";

    for (const auto& type : types) {
        WindowMenu modif("Modifier la clé pour " + type + " ?", {"Oui", "Non"});
        modif.show();
        if (modif.getChoice() == 3) return;

        if (modif.getChoice() == 1) {
            WindowForm form("Nouvelle clé pour " + type, {"Valeur"});
            form.show();
            std::string val = form.getAnswer().at("Valeur");

            if (type == "cesar" && !estEntier(val)) {
                WindowInfo err("Erreur", {"La clé César doit être un entier."});
                err.show();
                continue;
            }
            if (type == "aes" && val.size() != 32) {
                WindowInfo err("Erreur", {"La clé AES doit contenir exactement 32 caractères."});
                err.show();
                continue;
            }

            cles[type] = Cle(val);
            std::string cheminComplet = dossierCles + type + ".cle";
            std::ofstream fichier(cheminComplet);
            fichier << val;
        }
    }
}


void Application::traiterMessage() {
    const std::vector<std::string> types = {"cesar", "xor", "vigenere", "aes"};

    WindowMenu actionMenu("Action", {"Chiffrer", "Déchiffrer"});
    actionMenu.show();
    if (actionMenu.getChoice() == 3) return;
    bool chiffrer = actionMenu.getChoice() == 1;

    WindowMenu cibleMenu("Type de traitement", {"Phrase", "Fichier"});
    cibleMenu.show();
    if (cibleMenu.getChoice() == 3) return;
    bool surPhrase = cibleMenu.getChoice() == 1;

    WindowMenu algoMenu("Choix de l'algorithme", {"cesar", "xor", "vigenere", "aes"});
    algoMenu.show();
    if (algoMenu.getChoice() == 5) return;
    std::string algo = types[algoMenu.getChoice() - 1];

    if (cles.find(algo) == cles.end()) {
        WindowInfo erreur("Erreur", {"Clé non chargée pour l'algorithme choisi."});
        erreur.show();
        return;
    }

    std::string texte;
    if (surPhrase) {
        WindowForm saisie("Texte à traiter", {"Texte"});
        saisie.show();
        texte = saisie.getAnswer().at("Texte");
    } else {
        WindowForm fichierDemande("Fichier à lire", {"Chemin"});
        fichierDemande.show();
        std::string chemin = fichierDemande.getAnswer().at("Chemin");
        Fichier f(chemin);
        texte = f.lire();
    }

    std::unique_ptr<Message> message;
    if (algo == "cesar") message = std::make_unique<MCesar>(texte);
    else if (algo == "xor") message = std::make_unique<MXOR>(texte);
    else if (algo == "vigenere") message = std::make_unique<MVigenere>(texte);
    else if (algo == "aes") message = std::make_unique<MAES>(texte);

    message->setCle(&cles[algo]);
    std::string resultat = chiffrer ? message->chiffrer() : message->dechiffrer();

    WindowInfo resultatWindow("Résultat", {resultat});
    resultatWindow.show();
}

void Application::afficherCles() {
    std::vector<std::string> lignes;
    for (const auto& [nom, cle] : cles) {
        lignes.push_back(nom + " : " + cle.getValeur());
    }
    if (lignes.empty()) lignes.push_back("Aucune clé chargée.");
    WindowInfo infos("Clés chargées", lignes);
    infos.show();
}

void Application::demarrer() {
    const char* home = std::getenv("HOME");
    if (!home) {
        WindowInfo erreur("Erreur", {"Impossible d'accéder au répertoire personnel (HOME)."});
        erreur.show();
        return;
    }

    std::system("clear");

    WindowMenu chargement("Souhaitez-vous charger et/ou créer vos clés ?", {"Oui", "Non (toutes les clés seront vidées)"});
    chargement.show();
    if (chargement.getChoice() == 3) return;

    if (chargement.getChoice() == 1) {
        chargerOuCreerCles();
    }

    while (true) {
        WindowMenu menuPrincipal("Menu principal", {"Chiffrer / Déchiffrer", "Changer les clés", "Afficher les clés"});
        menuPrincipal.show();
        int choixPrincipal = menuPrincipal.getChoice();
    
        switch (choixPrincipal) {
            case 1:
                traiterMessage();
                break;
            case 2:
                changerCles();
                break;
            case 3:
                afficherCles();
                break;
            case 4:
                return;
        }
    }    
}
