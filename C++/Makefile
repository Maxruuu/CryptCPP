main: main.o Fichier.o FichierCle.o Cle.o Message.o Application.o
	g++ main.o Fichier.o Application.o FichierCle.o Cle.o Message.o -o main

main.o: main.cpp FichierCle.hpp
	g++ -c main.cpp

Application.o: Application.cpp Application.hpp Message.hpp
	g++ -c Application.cpp

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