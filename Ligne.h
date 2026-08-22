#ifndef LIGNE_H   
#define LIGNE_H   

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Ligne 
{
private:
	/* Chaque objet de la classe Ligne possède 4 attributs :
	1. le nom de l'espece formant cette ligne dans la matrice initiale (un string),
	2. un vector de double reprenant toutes les valeurs de dissimilitude entre cette espece
	   et les autres especes (ces valeurs sont dans un ordre précis, l'ordre de la matrice se 
	   trouvant dans le fichier en entrée),
	3. un nombre (double) qui est égal à la valeur du minimum dans cette ligne, donc pour cette
	   espece,
	4. un nombre (int) représentant l'indice de la position du minimum (valeur_minimale) dans
	   le vector valeurs. */
    string espece;
    vector<double> valeurs;
    double valeur_minimale;
    int indice_valeur_minimale;
   
public:
	/* On définit le constructeur de notre classe Ligne.*/
	Ligne(string nom_espece): espece(nom_espece), valeurs(){}
	
	/* On déclare les getters et setters des attributs :
	 * espece, valeur_minimale et indice_valeur_minimale.
	 * Le mot-clé "const" est utilisé pour les getters. */
	string getEspece() const;
	void setEspece(string nouveau_nom);
	
	double getValeur_minimale() const;
	void setValeur_minimale(double valeur);
	
	int getIndice_valeur_minimale() const;
	void setIndice_valeur_minimale(int indice);
	
	/* Dans notre code, nous n'avons jamais l'utilité d'avoir un getter
	 * et un setter pour l'attribut "valeurs". En effet, on ne doit jamais demander
	 * ou changer entièrement la liste. Cependant, il est parfois nécessaire d'effectuer
	 * quelques actions sur cette liste "valeurs" : */
	 
	 /* Nous commençons par déclarer les getter et setter permettant de connaître ou
	  * modifier la valeur se trouvant à l'indice "indice" dans notre liste. */
	double getValeur_specifique(int indice) const;
	void setValeur_specifique(int indice, double nouvelle_valeur);
	
	/* En plus de connaître où modifier une valeur déjà existante dans la liste,
	 * nous devons parfois supprimer une valeur se trouvant à une certaine position,
	 * et également rajouter une valeur (la valeur rajoutée se trouvera à la fin de la
	 * liste). */
	void supprimer_valeur_specifique(int indice);
	void ajouter_valeur(double valeur_a_ajouter);
	
	/* Pour éviter des erreurs de segmentation, on a parfois besoin de connaître
	 * la taille de cette liste "valeurs". Pour cela, on crée une fonction qui
	 * renvoie la taille de la ligne. */
	int getTaille_ligne() const;
	
	/* Lorsque la liste "valeurs" est modifiée, il peut arriver que les attributs
	 *  valeur_minimale et indice_valeur_minimale soient également affectés. Dans
	 * ces situations, il faut parfois retrouver un minimum et donc son indice également.
	 * Nous avons créé la fonction maj_minimum pour qu'elle mette à jour ces attributs.
	 * Les lettres "maj" correspondent à "mise à jour", car on ne crée pas de nouveaux
	 * attributs, on les met simplement à jour. */
	void maj_minimum();
	/* Il faut noter que cette fonction est la seule de la classe Ligne qui n'est pas
	 * en O(1). Comme il faut parcourir toutes les valeurs de la liste
	 * "valeurs", cette fonction tourne en O(n). */
};

#endif 
