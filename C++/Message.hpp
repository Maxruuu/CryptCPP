#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include "Cle.hpp"
#include "IChiffrable.hpp"

/*===========================
    Message
=============================*/

class Message : public IChiffrable {
protected:
    std::string clair;

private:
    Cle* cle;

public:
    Message(const std::string& texte);
    void setCle(Cle* nouvelleCle);
    const Cle* getCle() const;
    std::string chiffrer() const override = 0;
    std::string dechiffrer() const override = 0;

};

/*===========================
    Cesar
=============================*/

class MCesar : public Message {
public:
    MCesar(const std::string& texte);

    std::string chiffrer() const override;
    std::string dechiffrer() const override;
};

/*===========================
    XOR
=============================*/

class MXOR : public Message {
public:
    MXOR(const std::string& texte);
    
    std::string chiffrer() const override;
    std::string dechiffrer() const override;
};

/*===========================
    Vigenere
=============================*/

class MVigenere : public Message {
public:
    MVigenere(const std::string& texte);
    
    std::string chiffrer() const override;
    std::string dechiffrer() const override;
};

#endif