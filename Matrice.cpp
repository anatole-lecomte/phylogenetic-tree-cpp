#include <fstream>
#include <sstream>
#include "Matrice.h"

/* Nous définissons toutes les fonctions déclarées dans le fichier
 * "Matrice.h". Les explications de ce que font ces fonctions sont
 * développées dans ce même fichier. */
 
Ligne* Matrice::getAncetre() const
{
	return matrice[matrice.size() - 1];
}

int Matrice::getTaille_matrice() const
{
	return matrice.size();
}

Ligne* Matrice::getLigne_specifique(int indice) const
{
	/* On vérifie que l'indice est valable avant de rentrer dans la liste. */
	if ((indice >= 0) && (indice < matrice.size())){
		return matrice[indice];
	 }
	 else{
		cout << "L'indice rentré dans la fonction getLigneI n'est pas valable" << endl;
		return NULL;
	 }
}

void Matrice::lecture_matrice(const char* file)
{
	{
	ifstream fichier(file);
	string line;
	
	if (!fichier.is_open()){
        cerr << "Erreur : Impossible d'ouvrir le fichier " << file << endl;
        return; 
		/* Permet de sortir de la fonction en cas d'erreur lors de 
        *l'ouverture du fichier */
    }
    while(getline(fichier, line))
    {	
		if (line.empty()) { 
			/* Teste si la ligne est vide.
			*Si oui, on passe directement à l'itération suivante du while */
            continue;
        }
		/*Les variables valeur_min et indice_min servent à stocker le minimum de chaque ligne 
		 * et son indice pour ensuite les mettre dans les attributs de la ligne*/
        int i = 0;
        double valeur_min = 999999.9;
        int indice_min=-1;
		stringstream flux(line);
		string nom_espece;
		flux>>nom_espece;
		Ligne* laligne = new Ligne(nom_espece);
		
		double valeur;
		
		while(flux >> valeur){
			laligne->ajouter_valeur(valeur);
			/*On regarde si valeur est un nouveau minimum, si oui, on change 
			*valeur_min et indice_min*/
			if((valeur != 0)&&(valeur < valeur_min)){
				valeur_min=valeur;
				indice_min=i;
			}
			i++;
		}
		/*Si on aucun minimum n'a été trouvé dans la ligne considérée, on donne une valeur très élevée à valeur_min*/
		if(indice_min == -1){
			valeur_min = 999999.9;
		}
		laligne->setIndice_valeur_minimale(indice_min);
		laligne->setValeur_minimale(valeur_min);
		matrice.push_back(laligne);
		/*On rajoute la ligne nouvellement créée à la matrice.*/
	}
	fichier.close();
}
}
int Matrice::trouver_ligne_minimale() const
{
	/* On initie les minimum à des valeurs très élevées, pour être sûr
	 * que les futurs valeurs seront inférieures. */
	double minimum = 999999.9;
	double valeur_min_ligne = 999999.9;
	int indice_ligne_minimale = -1;
	
	for (int i = 0; i < matrice.size() ; ++i){
		valeur_min_ligne = matrice[i]->getValeur_minimale();
		if (valeur_min_ligne < minimum) {
                minimum = valeur_min_ligne;
                indice_ligne_minimale = i;
        }
	}
	return indice_ligne_minimale;
}

vector<int> Matrice::trouver_animaux_minimum(int ligne_minimale) const
{
	/* Le premier animal recherché est tout simplement l'animal possédant le minimum.
	 * Le deuxième animal formant ce minimum se trouve tout simplement à la position
	 * (indice) du minimum dans la Ligne possédant ce minimum. */
	int indice_animal_colonne = matrice[ligne_minimale]->getIndice_valeur_minimale();
	
	/* Dans le vector avec les animaux minimums, on fait attention à mettre
	 * "indice_animal_colonne" en premier et "ligne_minimale". Cela permet de s'assurer
	 * que la première valeur du vector soit inférieure à la seconde.
	 * Cette propriété du vector avec les animaux minimum sera utile pour plus tard.
	 * En effet, savoir quel animal a une liste "valeurs" la plus petite permettra de
	 * diminuer le nombre de cas à considérer plus tard dans certaines fonctions. */
	vector<int> vec = {indice_animal_colonne, ligne_minimale};
	return vec;
}

Ligne* Matrice::creer_nouvel_ancetre(vector<int> animaux_minimum)
{
	string nom_temporaire = "temporaire";
	Ligne* nouvel_ancetre = new Ligne(nom_temporaire);
	Ligne* animal1 = matrice[animaux_minimum[0]];
	Ligne* animal2 = matrice[animaux_minimum[1]];
	/* On crée le bon nom à donner à notre ancètre, respectant les critères donnés. */
	if (animal1->getEspece() < animal2->getEspece()){
		string vrai_nom = "A_" + animal1->getEspece() + "_" + animal2->getEspece();
		nouvel_ancetre->setEspece(vrai_nom);
		}
	else {
		string vrai_nom = "A_" + animal2->getEspece() + "_" + animal1->getEspece();
		nouvel_ancetre->setEspece(vrai_nom);
		}
	return nouvel_ancetre;
}

double Matrice::calcul_valeur(vector<int> animaux_minimum, int i) const
{
	int indice1 = animaux_minimum[0];
	int indice2 = animaux_minimum[1];
	Ligne* animal1 = matrice[indice1];
	Ligne* animal2 = matrice[indice2];
	double distance = -1;
	/* Pour pouvoir calculer la nouvelle valeur de dissimilitude entre l'ancetre
	 * et l'animal à la position i, on aimerait pouvoir simplement aller
	 * à la position i dans les listes "valeurs" des deux animaux, et effectuer
	 * le calcul.
	 * Cependant, ces deux listes "valeurs" n'ont pas la même taille, et peuvent
	 * même être de taille inférieure à la position i. Heureusement, il est quand même
	 * possible d'effectuer le calcul en profitant des propriétés de la matrice de
	 * dissimilitude. En effet, celle-ci étant symétrique, si l'on essaie de prendre
	 * une valeur dans une Ligne A, à une position i plus grande que la taille de cette
	 * liste, cela revient à prendre la valeur se trouvant dans la Ligne i à la position A.*/
	 
    if ( i < indice1){ 
		/* Cas 1 : les Lignes des 2 animaux sont suffisamment grandes
		que pour aller chercher la valeur i. */
		distance = (animal1->getValeur_specifique(i) + animal2->getValeur_specifique(i)) / 2.0;
		}
			
	else if ((i > indice1) && (i < indice2)){ 
		/* Cas 2 : la Ligne du premier animal est trop petite par rapport à la position i,
		 * mais la Ligne du second animal est suffisamment grande.
		 * On ne vérifie que le cas où le premier animal est l'animal limitant, car on sait
		 * que le premier animal aura toujours une Ligne plus petite que le second. En effet,
		 * on avait créé le vector animaux_minimum avec cette propriété. */
		distance = (matrice[i]->getValeur_specifique(indice1) + animal2->getValeur_specifique(i)) / 2.0;
		}
			
	else if ( i > indice2){ 
		/* Cas 3 : les deux Lignes sont trop petites devant i */
		distance = (matrice[i]->getValeur_specifique(indice1) + matrice[i]->getValeur_specifique(indice2)) / 2.0;
		}
	return distance;
}

void Matrice::suppression_ligne_specifique(int indice)
{
	/* On fait attention à bien supprimer l'objet Ligne, et pas juste supprimer
	 * son pointeur de la liste "matrice". */
	delete matrice[indice];
	matrice.erase(matrice.begin() + indice);
	
	/* On peut remarquer qu'on ne réoriente pas le pointeur de la Ligne vers
	 * le pointeur NULL, mais en réalité ce n'est pas nécessaire. Le pointeur
	 * vers cette Ligne n'est accessible que depuis la liste "matrice", donc si
	 * on le supprime de cette liste, on est sûr qu'on ne pourra plus jamais l'appeler,
	 * et on évite ainsi tout risque de pointeur fou. */
}

void Matrice::suppression_colonnes(vector<int> animaux_minimum)
{	
	int indice1 = animaux_minimum[0];
	int indice2 = animaux_minimum[1];
	Ligne* animal = matrice[0];
	
    for (int i = 0; i < matrice.size(); ++i) {
		animal = matrice[i];
		if ( indice2 < animal->getTaille_ligne()){ 
			/* On vérifie qu'on n'essaie pas d'effacer
			un élément plus loin que la taille de notre Ligne. */
			matrice[i]->supprimer_valeur_specifique(indice2);
			}
        if ( indice1 < animal->getTaille_ligne()){
			matrice[i]->supprimer_valeur_specifique(indice1);
			}
    }
    /* Il est intéressant de voir qu'on supprime d'abord la valeur à la position
     * indice2. En effet, indice2 > indice1 (par construction du vector animaux_minimum), 
     * et donc on s'assure de supprimer une valeur plus loin dans la liste d'abord.
     * Si on avait voulu inverser, il aurait fallu tenir compte du déplacement de l'indice. */
}

void Matrice::etape()
{
	int ligne_minimale = trouver_ligne_minimale();
	vector<int> animaux_minimum = trouver_animaux_minimum(ligne_minimale);
	Ligne* ancetre = creer_nouvel_ancetre(animaux_minimum);
	/* On initie la valeur du minimum de l'ancètre à une valeur très élevée,
	 * pour être sûr que les valeurs futures seront inférieures.*/
	double valeur_minimale_ancetre = 999999.9;
	int indice_mini = -1;
	int j=-1;
	for (int i = 0; i < matrice.size() ; ++i){
		if ((i != animaux_minimum[0]) && (i != animaux_minimum[1])) {
			/* Cette condition permet d'écarter les valeurs valant 0 et la position
			 * où nous avons le minimum. */
			j++;
			double nouvelle_valeur = calcul_valeur(animaux_minimum, i);
			ancetre->ajouter_valeur(nouvelle_valeur);
			
			/* Maintenant que nous avons calculé une nouvelle valeur, on regarde
			 * si ça peut être le potentiel minimum de la Ligne ancetre. */
			if((nouvelle_valeur < valeur_minimale_ancetre) && (nouvelle_valeur != 0)){
				valeur_minimale_ancetre = nouvelle_valeur;
				indice_mini = j;
			}
			}
		}
	if(indice_mini == -1){
			valeur_minimale_ancetre = 999999.9;
		}
	/* On doit terminer la liste des valeurs avec la valeur
	 * 0.0. */
	ancetre->ajouter_valeur(0.0);
	
	suppression_ligne_specifique(animaux_minimum[1]);
	suppression_ligne_specifique(animaux_minimum[0]);
	/* Il est intéressant de remarquer qu'on supprime d'abord la ligne du 
	 * second animal. En effet, le second animal se trouve plus bas dans la matrice,
	 * et sa suppression n'impacte pas l'indice du premier animal. */
	
	suppression_colonnes(animaux_minimum);
	ancetre->setValeur_minimale(valeur_minimale_ancetre);
	ancetre->setIndice_valeur_minimale(indice_mini);	
	
	/* Après avoir effectué nos étapes, il reste à rajouter la Ligne de l'ancetre dans
	 * la liste "matrice". */
	matrice.push_back(ancetre);
}

/* Fonction juste pour le visuel. */
void Matrice::afficher_matrice() const
{
    for (int i = 0; i < getTaille_matrice(); ++i) {
		const Ligne* ligne = getLigne_specifique(i);
        cout << ligne->getEspece() << "\t";
        for (int i = 0 ; i < ligne->getTaille_ligne() ; ++i) {
			double valeur = ligne->getValeur_specifique(i);
            cout << valeur << "\t";
        }
        cout << endl;
    }
    cout << " " << endl;
}
