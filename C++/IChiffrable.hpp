#ifndef ICHIFFRABLE_HPP
#define ICHIFFRABLE_HPP

#include <string>

class IChiffrable {
public:
    virtual std::string chiffrer() const = 0;
    virtual std::string dechiffrer() const = 0;
};

#endif