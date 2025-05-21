main: main.o Application.o Fichier.o FichierCle.o Cle.o Message.o Window.o
	g++ main.o Application.o Fichier.o FichierCle.o Cle.o Message.o Window.o -lssl -lcrypto -o main

main.o: main.cpp Application.hpp
	g++ -c main.cpp

Application.o: Application.cpp Application.hpp
	g++ -c Application.cpp

Fichier.o: Fichier.cpp Fichier.hpp
	g++ -c Fichier.cpp

FichierCle.o: FichierCle.cpp FichierCle.hpp Fichier.hpp
	g++ -c FichierCle.cpp

Cle.o: Cle.cpp Cle.hpp
	g++ -c Cle.cpp

Message.o: Message.cpp Message.hpp
	g++ -c Message.cpp

Window.o: Window.cpp Window.hpp
	g++ -c Window.cpp

clean:
	rm -f *.o
