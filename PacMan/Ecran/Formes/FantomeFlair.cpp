#include "FantomeFlair.h"

FantomeFlair::FantomeFlair(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	FantomeAleatoire(infos, positionSommet, choixNiveau), pacman(nullptr) {}

FantomeFlair::~FantomeFlair() {}

const Vecteur2D FantomeFlair::selectionDirection() {
	// On regarde si les coordonn�es en x ou y du pacman correspondent, et si c'est le cas, on v�rifie
	// si on peut tracer une route jusqu'� lui
	if (pacman == nullptr) {
		// On va rechercher le pacman dans la liste des cr�atures
		std::vector<Creature*>::iterator it = this->infos->getFenetre()->listeCreatureParNiveaux.at(choixNiveau).begin();
		for (it; it < this->infos->getFenetre()->listeCreatureParNiveaux.at(choixNiveau).end(); it++)
			if ((std::string)(**it) == "pacman")
				this->pacman = *it;
	}

	std::cout << this->directionCreature << std::endl;
	Vecteur2D directionAPrendre;

	Vecteur2D coordSommetFantome(this->getPositionEcran());
	Vecteur2D coordSommetPacman(pacman->getPositionEcran());

	directionAPrendre = coordSommetFantome - coordSommetPacman;
	if ((directionAPrendre.x != directionAPrendre.y) && ((directionAPrendre.x == 0) || (directionAPrendre.y == 0))) {
		// On a potentiellement une vue sur le pacman, il faut donc d�duire la direction
		// TODO : grosse redondance de code ici

		if (directionAPrendre.x == 0) {
			// Le fantome est en dessous, il doit monter
			if (coordSommetFantome.y < coordSommetPacman.y)
				directionAPrendre.y = 1;
			else
				// Il doit descendre
				directionAPrendre.y = -1;
		}
		else {
			// Le fantome est � gauche
			if (coordSommetFantome.x < coordSommetPacman.x)
				directionAPrendre.x = 1;
			else
				directionAPrendre.x = -1;
		}
		this->listeVoisins = this->infos->getFenetre()->niveaux->at(choixNiveau)->voisins(this->sommetActuel);
		// On a maintenant une direction g�n�rale, on va d�piler les voisins en allant toujours dans la direction trouv�e
		Liste<Sommet<FormeEcran>*> voisinsTmp = *this->listeVoisins;
		Iterateur<Sommet<FormeEcran>*> iterateurVoisinsTmp = voisinsTmp.getIterateur();
		Sommet<FormeEcran> * tmp = nullptr;
		bool pacmanTrouve = false, voisinTrouve;
		Vecteur2D curseur = coordSommetFantome;

		while (!pacmanTrouve && iterateurVoisinsTmp.aSuivant()) {
			voisinTrouve = false;

			while (!voisinTrouve && iterateurVoisinsTmp.aSuivant()) {

				tmp = *iterateurVoisinsTmp.suivant();
				if (curseur + directionAPrendre == tmp->valeur.getPositionEcran()) {
					voisinTrouve = true;
					curseur = tmp->valeur.getPositionEcran();
				}

			}


			if (tmp->valeur.getPositionEcran() == coordSommetPacman)
				pacmanTrouve = true;
			else {
				voisinsTmp = *this->infos->getFenetre()->niveaux->at(choixNiveau)->voisins(tmp);
				iterateurVoisinsTmp = voisinsTmp.getIterateur();
			}
		}
		if (pacmanTrouve) return directionAPrendre;
	}
	std::cout << "direction random" << std::endl;
	return FantomeAleatoire::selectionDirection();
}
