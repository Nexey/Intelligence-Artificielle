#include "FantomeFlair.h"

FantomeFlair::FantomeFlair(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	FantomeAleatoire(infos, positionSommet, choixNiveau), pacman(nullptr) {}

FantomeFlair::~FantomeFlair() {}

const Vecteur2D FantomeFlair::selectionDirection() {
	// On regarde si les coordonnées en x ou y du pacman correspondent, et si c'est le cas, on vérifie
	// si on peut tracer une route jusqu'à lui
	if (pacman == nullptr) {
		// On va rechercher le pacman dans la liste des créatures
		std::vector<Creature*>::iterator it = this->infos->getFenetre()->listeCreatureParNiveaux.at(choixNiveau).begin();
		for (it; it < this->infos->getFenetre()->listeCreatureParNiveaux.at(choixNiveau).end(); it++)
			if ((std::string)(**it) == "pacman")
				this->pacman = *it;
	}

	//std::cout << this->directionCreature << std::endl;
	Vecteur2D directionAPrendre;

	Vecteur2D coordSommetFantome(this->getPositionEcran());
	Vecteur2D coordSommetPacman(pacman->getPositionEcran());

	if (coordSommetFantome != coordSommetPacman)
		directionAPrendre = coordSommetPacman - coordSommetFantome;

	if (
		(directionAPrendre.x == directionAPrendre.y) // Le fantome est en diagonale
		|| (-directionAPrendre.x == directionAPrendre.y) // Le fantome est en diagonale
		|| (directionAPrendre.x == -directionAPrendre.y) // Le fantome est en diagonale
		|| (-directionAPrendre.x == -directionAPrendre.y) // Le fantome est en diagonale
		|| (directionAPrendre.x == 0) || (directionAPrendre.y == 0) // Le fantome est de côté
		) {
		// On a potentiellement une vue sur le pacman, il faut donc déduire la direction
		// TODO : grosse redondance de code ici

		if (directionAPrendre.x != 0) directionAPrendre.x /= std::abs(directionAPrendre.x);
		if (directionAPrendre.y != 0) directionAPrendre.y /= std::abs(directionAPrendre.y);


		/*
		if (directionAPrendre.x == 0) {
			// Le fantome est en dessous, il doit monter
			if (coordSommetFantome.y < coordSommetPacman.y)
				directionAPrendre.y = 1;
			else
				// Il doit descendre
				directionAPrendre.y = -1;
		}
		else {
			// Le fantome est à gauche
			if (coordSommetFantome.x < coordSommetPacman.x)
				directionAPrendre.x = 1;
			else
				directionAPrendre.x = -1;
		}
		*/
		this->listeVoisins = this->infos->getFenetre()->niveaux->at(choixNiveau)->voisins(this->sommetActuel);
		// On a maintenant une direction générale, on va dépiler les voisins en allant toujours dans la direction trouvée
		Liste<Sommet<FormeEcran>*> voisinsTmp = *this->listeVoisins;
		Iterateur<Sommet<FormeEcran>*> iterateurVoisinsTmp = *voisinsTmp.getIterateur();
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
				if (voisinTrouve) {
					voisinsTmp = *this->infos->getFenetre()->niveaux->at(choixNiveau)->voisins(tmp);
					iterateurVoisinsTmp = *voisinsTmp.getIterateur();
				}
			}
		}
		if (pacmanTrouve) return directionAPrendre;
	}
	//std::cout << "direction random" << std::endl;
	return FantomeAleatoire::selectionDirection();
}
