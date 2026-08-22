#include <fstream>
#include "Matrice.h"

// Fonction principale
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <fichier_matrice.txt>" << endl;
        return 1;
    }
	
    // Lecture du fichier et création de la matrice
    Matrice* matrice = new Matrice;
    matrice->lecture_matrice(argv[1]);
	
	/* On effectue une seule fois l'étape permettant de trouver un ancetre
	 * et de supprimer les anciens animaux.*/
	matrice->etape();
   
   /* On écrit dans le terminal le nom de l'ancetre final. */
    cout << matrice->getAncetre()->getEspece() << endl;
    
    /* On écrit l'ancetre final dans le fichier de sortie,
     *  si un fichier de sortie est fourni.*/
    if(argc>2){ofstream fichierout(argv[2]);
    fichierout << matrice->getAncetre()->getEspece() << endl;
    fichierout.close();
	}
    
    return 0;
}
