#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include "Cle.hpp"
#include "IChiffrable.hpp"

/*===========================
    Message
=============================*/

class Message {
protected:
    std::string clair;

private:
    Cle* cle;

public:
    Message(const std::string& texte);
    void setCle(Cle* nouvelleCle);
    const Cle* getCle() const;

};

/*===========================
    Cesar
=============================*/

class MCesar : public Message, public IChiffrable {
public:
    MCesar(const std::string& texte);

    std::string chiffrer() const override;
    std::string dechiffrer() const override;
};

/*===========================
    XOR
=============================*/

class MXOR : public Message, public IChiffrable {
public:
    MXOR(const std::string& texte);
    
    std::string chiffrer() const override;
    std::string dechiffrer() const override;
};

/*===========================
    Vigenere
=============================*/

class MVigenere : public Message, public IChiffrable {
public:
    MVigenere(const std::string& texte);
    
    std::string chiffrer() const override;
    std::string dechiffrer() const override;
};

#endif