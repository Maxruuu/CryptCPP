main: main.o Fichier.o FichierCle.o Cle.o Message.o
	g++ main.o Fichier.o FichierCle.o Cle.o Message.o -o main

main.o: main.cpp FichierCle.hpp
	g++ -c main.cpp

Message.o : Message.cpp Message.hpp
	g++ -c Message.cpp

Cle.o: Cle.cpp Cle.hpp
	g++ -c Cle.cpp

FichierCle.o : FichierCle.cpp FichierCle.hpp Fichier.hpp
	g++ -c FichierCle.cpp

Fichier.o : Fichier.cpp Fichier.hpp
	g++ -c Fichier.cpp

clean:
	rm *.o