#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran>* positionSommet, Graphe<FormeEcran, FormeEcran> * niveau) :
	formeSFML(formeSFML),
	fenetre(fenetre),
	sommetActuel(positionSommet),
	niveau(niveau),
	prochainSommet(positionSommet),
	directionCreature(FenetreEcran::VECTEUR2D_STOP),
	alpha(0.f),
	velocite(0.05f) {
	this->formeSFML->setOrigin(this->formeSFML->getGlobalBounds().width / 2.f, this->formeSFML->getGlobalBounds().height / 2.f);
	this->miseAJourPositionEcran(positionSommet->valeur.getPositionEcran());
	voisins = niveau->voisins(positionSommet);
}

Creature::~Creature() {}

bool Creature::deplacer() {
	// La créature a atteint sa destination, on lui met à jour ses voisins
	if (alpha >= 1.f) {
		alpha = 0.f;
		sommetActuel = prochainSommet;
		miseAJourPositionEcran(sommetActuel->valeur.getPositionEcran());

		voisins = niveau->voisins(sommetActuel);


		// DEBUG
		/*
		iterateurVoisins = &voisins->getIterateur();
		while (iterateurVoisins->aSuivant()) {
			std::cout << **iterateurVoisins->suivant() << std::endl;
		}

		std::cout << std::endl << std::endl << std::endl;
		*/
	}
	else {
		if (this->estImmobile()) {
			// On initialise les voisins du sommet actuel, puis on initialise la direction du PacMan
			iterateurVoisins = &voisins->getIterateur();
			Sommet<FormeEcran> * tmp = nullptr;

			// Quelques variables temporaires pour alléger l'appel aux fonctions
			Vecteur2D
				coordSommetActuel = sommetActuel->valeur.getPositionEcran(),
				nouvelleCoordDirectionUtilisateur = coordSommetActuel + this->fenetre->direction,
				nouvelleCoordCreature = coordSommetActuel + this->directionCreature,
				coordSommetVoisin;

			// Je récupère les voisins et vérifie s'il y en a un avec les coordonnées telles que : direction + pos = voisin.pos
			// Je boucle tant qu'il y a des voisins et tant que le prochainSommet n'est pas mis à jour
			while (iterateurVoisins->aSuivant() && prochainSommet == sommetActuel) {
				tmp = *iterateurVoisins->suivant();
				coordSommetVoisin = tmp->valeur.getPositionEcran();

				// Je regarde si les nouvelles coordonnées engendrées par un changement de direction de l'utilisateur font tomber sur
				// les coordonnées d'un des voisins
				if (nouvelleCoordDirectionUtilisateur == coordSommetVoisin) {
					this->directionCreature = this->fenetre->direction;
					prochainSommet = tmp;
					// J'ai récupéré le prochain sommet
				}
			}
			iterateurVoisins->debut();
			// Si les nouvelles coordonnées engendrées par la direction de la créature restent valides, alors j'y vais
			while (iterateurVoisins->aSuivant() && prochainSommet == sommetActuel) {
				// On entre dans cette boucle que si les coordonnées de l'utilisateur sont invalides
				tmp = *iterateurVoisins->suivant();
				coordSommetVoisin = tmp->valeur.getPositionEcran();

				if (nouvelleCoordCreature == coordSommetVoisin)
					prochainSommet = tmp;
			}
		}
		// On est en mouvement
		
		// Si la direction a changé, et si la direction de la créature + la direction de la fenêtre = (0, 0) alors il faut faire un demi-tour
		if (this->directionCreature + this->fenetre->direction == FenetreEcran::VECTEUR2D_STOP) {
			// J'inverse l'alpha
			alpha = 1.f - alpha;

			// Je lui inverse sa position actuelle et sa position de destination
			Sommet<FormeEcran> * temp = this->prochainSommet;
			this->prochainSommet = this->sommetActuel;
			this->sommetActuel = temp;

			// Je lui inverse sa destination
			this->directionCreature = this->fenetre->direction;

			// Je mets à jour ses voisins
			this->voisins = niveau->voisins(sommetActuel);
		}

		if (prochainSommet != sommetActuel) {
			// On augmente son alpha et on met à jour la position du sprite
			alpha += velocite;
			miseAJourPositionEcran(sommetActuel->valeur.getPositionEcran() + directionCreature * alpha);
			return true;
		}
	}
	return false;
}

const bool Creature::estImmobile() const {
	return alpha == 0.f;
}

void Creature::miseAJourPositionEcran(const Vecteur2D & nouvPos) {
	this->formeSFML->setPosition(fenetre->calculPos(nouvPos));
}
