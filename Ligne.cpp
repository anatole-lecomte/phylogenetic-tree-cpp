#include "Ligne.h"

/* Nous définissons les fonctions déclarées dans le fichier
 * "Ligne.h". Les explications de ce que font ces fonctions
 * sont développées dans ce même fichier. */
 
string Ligne::getEspece() const
{
	return espece;
}

void Ligne::setEspece(string nouveau_nom)
{
	espece = nouveau_nom;
}

double Ligne::getValeur_minimale() const
{
	return valeur_minimale;
}

void Ligne::setValeur_minimale(double valeur)
{
	valeur_minimale = valeur;
}

int Ligne::getIndice_valeur_minimale() const
{
	return indice_valeur_minimale;
}

void Ligne::setIndice_valeur_minimale(int indice)
{
	indice_valeur_minimale = indice;
}

double Ligne::getValeur_specifique(int indice) const
{
	/* On vérifie que l'indice est valable avant de rentrer dans la liste. */
	if ((indice >= 0) && (indice < valeurs.size())){
		return valeurs[indice];
	}
	else {
		cout << "L'indice rentré dans la fonctin getValeur_specifique n'est pas valable" << endl;
		return -1;
	}
}

void Ligne::setValeur_specifique(int indice, double nouvelle_valeur)
{
	/* On vérifie que l'indice est valable avant de rentrer dans la liste. */
	 if ((indice >= 0) && (indice < valeurs.size())){
		valeurs[indice] = nouvelle_valeur;
	 }
	 else{
		cout << "L'indice rentré dans la fonction setValeur_specifique n'est pas valable" << endl;
	 }
}

void Ligne::supprimer_valeur_specifique(int indice)
{	
	/* On vérifie que l'indice est valable avant de rentrer dans la liste. */
	if ((indice >= 0) && (indice < valeurs.size())){
		valeurs.erase(valeurs.begin() + indice);
		
		/* Une fois que la valeur a été supprimée de la liste, on regarde si
		 * cette suppression a affecté notre minimum. */
		if (indice == indice_valeur_minimale){
			/* Si la valeur supprimée était précisément notre minimum,
			 * il faut en trouver un nouveau, d'où l'appel à la fonction
			 * maj_minimum. */
			maj_minimum();
			}
		else if (indice < indice_valeur_minimale){
			/* Si la valeur supprimée était avant la position de notre
			 * minimum, notre minimum sera déplacé d'une position dans la liste.
			 * On va donc mettre à jour sa positioin en changeant son indice.
			 * Pour cela, pas besoin de réappeler la fonction couteuse
			 * maj_minimum, qui augmenterait la complexité pour rien. */
			indice_valeur_minimale = indice_valeur_minimale - 1;
			}
	 }
	 else{
		cerr << "L'indice rentré dans la fonction supprimer_valeur_specifique n'est pas valable" << endl;
	 }
}

void Ligne::ajouter_valeur(double valeur_a_ajouter)
{
		valeurs.push_back(valeur_a_ajouter);
}

int Ligne::getTaille_ligne() const
{
	return valeurs.size();
}

void Ligne::maj_minimum()
{
	/* On initie un minimum, et on l'initie à une valeur très grande
	 * pour être sûr que les valeurs dans la liste "valeurs" seront
	 * inférieures. */
	double minimum = 999999.9;
	int indice_minimum = -1;
	
	/* On fait une boucle pour trouver notre valeur minimale et son
	 * indice. */
	for (int i = 0; i < valeurs.size(); ++i){
		if ((valeurs[i] != 0) && (valeurs[i] < minimum)) {
                minimum = valeurs[i];
                indice_minimum = i;
            }
		}
	/* On met à jour les attributs. */
	indice_valeur_minimale = indice_minimum;
	valeur_minimale = valeurs[indice_minimum];
	
	/* Si nous n'avons pas trouvé de minimum, on dit que la valeur
	 * minimale est très élevée. Ce cas correspond à une Ligne n'ayant
	 * plus de valeurs après qu'on ait supprimé certains éléments, c'est
	 * donc une Ligne avec uniquement la valeur 0.0. On ne veut jamais compter
	 * cette Ligne, donc on impose un minimum très élevée. */
	if (indice_valeur_minimale == -1){
		valeur_minimale = 999999.9;
		}
}
