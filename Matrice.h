#include "Ligne.h"

class Matrice 
{
private:
	/* Nous aurons un unique objet de la classe Matrice. Cet objet aura
	 * un attribut "matrice", qui est une liste (vector) de pointeurs
	 * vers des objets de la classe Ligne. Cette forme (vector de pointeurs
	 * vers des Lignes) est une manière de reformer la matrice donnée en entrée,
	 * de garder cette structure. */
    vector<Ligne*> matrice;
   
public:
	/* On définit le constructeur de la classe. */
	Matrice(): matrice(){}
	
	/* Nous déclarons certaines fonctions getter qui vont permettre
	 * de renvoyer certains éléments liés à notre attribut "matrice" sans
	 * pouvoir les changer (à l'aide du mot-clé "const") : */
	 
	/* La fonction getAncetre renvoie le dernier pointeur dans notre
	 * liste matrice. On appelle la ligne pointée "ancetre", car nous placerons
	 * toujours l'ancetre nouvellement créé à la fin de la liste "matrice". */
	Ligne* getAncetre() const;
	
	/* La fonction getTaille_matrice renvoie la taille de la liste "matrice",
	 * pour éviter de potentielles erreurs de segmentation. */
	int getTaille_matrice() const;
	
	/* La fonction suivante permet de renvoyer le pointeur se trouvant à la
	 * position "indice" dans la liste "matrice". */
	Ligne* getLigne_specifique(int indice) const;
	
	
	/* Pour entamer l'algorithme, il est d'abord indispensable de retranscrire
	 * la matrice donnée en entrée dans la structure choisie. La fonction
	 * suivante permet de créer les différents objets Ligne au fur et à
	 * mesure de la lecture du fichier donné en entrée, pour ensuite les 
	 * mettre dans le bon ordre dans la liste "matrice".
	 * Afin de diminuer la complexité globale, cette fonction va également initié
	 * les valeurs des attributs valeur_minimale et indice_valeur_minimale de 
	 * chaque objet Ligne. En effet, tant qu'à devoir lire toutes les valeurs
	 * de dissimilitude, autant déjà retenir quel est le minimum de chaque Ligne.*/
	void lecture_matrice(const char* file);
	/* Cette fonction a une complexité de l'ordre de O(n²),
	 * car elle doit parcourir tous les éléments de la matrice en entrée
	 * (avec n = nombre d'animaux). */
	
	
	/* Les prochaines fonctions sont listées dans l'ordre de leur utilisation
	 * dans le code. Ces utilisations suivent l'ordre des opérations nécessaires 
	 * pour effectuer 1 étape de l'algorithme:
	 * 1. trouver un minimum, 
	 * 2. créer un ancetre liant les 2 animaux ayant comme valeur de dissimilitude 
	 *    le minimum,
	 * 3. Calculer les nouvelles valeurs liant l'ancetre à tous les autres animaux,
	 * 4. Supprimer les animaux qui ont permis de former l'ancetre.
	 * */
	
	// 1.
	/* Cette fonction permet de renvoyer l'indice du pointeur de l'objet
	 * Ligne ayant le minimum global. Cet indice permet de situer le pointeur
	 * dans la liste "matrice". */
	int trouver_ligne_minimale() const;
	/* Cette fonction est en O(n), car elle doit parcourir toute la
	 * liste "matrice" afin de trouver le minimum global, qui se trouve parmi
	 * toutes les valeur_minimale de chaque Ligne. */
	
	// 2.
	/* Cette fonction renvoie les 2 indices des pointeurs des 2 animaux
	 * ayant comme valeur de dissimilitude le minimum global. Elle indique donc
	 * les 2 Lignes qui devront être supprimées à la fin de l'étape. */
	vector<int> trouver_animaux_minimum(int ligne_minimale) const;
	
	/* Cette fonction renvoie le pointeur d'un nouvel objet Ligne avec 
	 * le nom de l'ancetre formé des deux animaux minimum. */
	Ligne* creer_nouvel_ancetre(vector<int> animaux_minimum);
	
	// 3.
	/* Cette fonction calcule et renvoie la valeur de dissimilitude entre 
	 * l'ancètre nouvellement créé et l'animal (Ligne) se trouvant à la 
	 * position "indice" dans la liste "matrice". */
	double calcul_valeur(vector<int> animaux_minimum, int indice) const;
	
	// 4.
	/* Cette fonction supprime l'objet Ligne se trouvant à la position "indice"
	 * dans la liste "matrice". Elle retire également son pointeur de cette même
	 * liste. */
	void suppression_ligne_specifique(int indice);
	
	/* Les valeurs de dissimilitude des animaux à supprimer ne se trouvent
	 * pas uniquement dans leurs Lignes, elles sont également à leur position
	 * dans les autres Lignes. Cette fonction permet de supprimer ces valeurs. 
	 * Le nom de cette fonction vient du fait que les valeurs à supprimer forment
	 * les colonnes des animaux, si l'on regarde la structure de la matrice donnée
	 * en entrée.*/
	void suppression_colonnes(vector<int> animaux_minimum);
	/* Cette fonction est en grand O de n. En effet, on doit rentrer dans chaque Ligne
	 * pour supprimer les 2 valeurs.*/
	
	
	/* Cette fonction permet d'effectuer 1 étape de l'algorithme. Elle combine donc
	 * les fonctions expliquées précédemment. 
	 * Elle permet également d'initier les attributs valeur_minimale et
	 * indice_valeur_minimale de la Ligne de l'ancetre en même temps. En effet,
	 * comme on doit calculer toutes les valeurs à mettre dans l'ancètre, on est 
	 * obligé de parcourir toutes ces nouvelles valeurs, donc autant en profiter pour
	 * directement trouver le minimum de cette Ligne, pour ne pas devoir reparcourir
	 * la liste plus tard. */
	void etape();
	/* La complexité de cette fonction est variable, elle dépend de la situation dans
	 * laquelle elle est appelée. Sa complexité est développée dans le rapport. */
	
	
	/* Cette dernière fonction n'est pas utilisée dans le main afin de réaliser le projet. 
	 * Elle permet simplement de visualiser la matrice, dans le même format que la matrice
	 * donnée en entrée.*/
	void afficher_matrice() const;
};
