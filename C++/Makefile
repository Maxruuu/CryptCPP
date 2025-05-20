CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lssl -lcrypto

# Cibles principales
main: main.o Fichier.o FichierCle.o Cle.o Message.o Application.o
	$(CXX) main.o Fichier.o Application.o FichierCle.o Cle.o Message.o -o main $(LDFLAGS)

# Compilation des fichiers sources
main.o: main.cpp FichierCle.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Application.o: Application.cpp Application.hpp Message.hpp
	$(CXX) $(CXXFLAGS) -c Application.cpp

Message.o: Message.cpp Message.hpp
	$(CXX) $(CXXFLAGS) -c Message.cpp

Cle.o: Cle.cpp Cle.hpp
	$(CXX) $(CXXFLAGS) -c Cle.cpp

FichierCle.o: FichierCle.cpp FichierCle.hpp Fichier.hpp
	$(CXX) $(CXXFLAGS) -c FichierCle.cpp

Fichier.o: Fichier.cpp Fichier.hpp
	$(CXX) $(CXXFLAGS) -c Fichier.cpp

# Nettoyage des fichiers objets
clean:
	rm -f *.o main