all: projetprelim projet	
	
projetprelim: Matrice.o Ligne.o projetprelim.o
	g++ -o projetprelim Matrice.o Ligne.o projetprelim.o
	
projet: Matrice.o Ligne.o projet.o
	g++ -o projet Matrice.o Ligne.o projet.o

Matrice.o: Matrice.cpp Matrice.h Ligne.h
	g++ -c Matrice.cpp

Ligne.o: Ligne.cpp Ligne.h
	g++ -c Ligne.cpp
	
projetprelim.o: projetprelim.cpp Matrice.h Ligne.h
	g++ -c projetprelim.cpp
	
projet.o: projet.cpp Matrice.h Ligne.h
	g++ -c projet.cpp
	
clean:
	rm *.o