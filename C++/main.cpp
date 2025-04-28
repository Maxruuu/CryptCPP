#include <iostream>

#include "FichierCle.hpp"
#include "Message.hpp"

int main() {
    MCesar test("Docd no mrsppbowoxd Méckb.");
    Cle cle("10");

    test.setCle(&cle);

    std::cout << test.dechiffrer() << std::endl;
}