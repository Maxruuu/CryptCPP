#ifndef CLE_HPP
#define CLE_HPP

#include <variant>
#include <string>

class Cle {
private:
    std::string valeur;

public:
    Cle(const std::string& valeur);
    const std::string getValeur() const;

};

#endif