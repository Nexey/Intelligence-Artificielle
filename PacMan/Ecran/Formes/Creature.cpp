#include "Creature.h"

Creature::Creature(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	infos(infos),
	sommetActuel(positionSommet),
	choixNiveau(choixNiveau),
	prochainSommet(positionSommet),
	directionCreature(FenetreEcran::VECTEUR2D_STOP),
	alpha(0.f),
	velocite(0.05f) {}

Creature::~Creature() {}

void Creature::miseAJourVoisins() {
	listeVoisins = infos->getFenetre()->niveaux->at(this->choixNiveau)->voisins(this->sommetActuel);
}

bool Creature::deplacer() {
	// La créature a atteint sa destination, on lui met à jour ses voisins
	if (alpha >= 1.f) {
		alpha = 0.f;
		sommetActuel = prochainSommet;
		infos->miseAJourPositionEcran(sommetActuel->valeur.getPositionEcran());

		// Mise à jour des voisins
		miseAJourVoisins();
	}
	else {
		Vecteur2D directionChoisie = this->selectionDirection();
		if (this->estImmobile()) {
			// Mise à jour des voisins
			miseAJourVoisins();

			// On initialise les voisins du sommet actuel, puis on initialise la direction du PacMan
			iterateurVoisins = &listeVoisins->getIterateur();
			Sommet<FormeEcran> * tmp = nullptr;

			// Quelques variables temporaires pour alléger l'appel aux fonctions
			Vecteur2D
				coordSommetActuel = sommetActuel->valeur.getPositionEcran(),
				nouvelleCoordDirectionUtilisateur = coordSommetActuel + directionChoisie,
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
					this->directionCreature = directionChoisie;
					prochainSommet = tmp;
					// J'ai récupéré le prochain sommet
				}
			}
			iterateurVoisins->debut();
			// Si les nouvelles coordonnées engendrées par la direction de la créature restent valides, alors j'y vais
			// On ne rentre dans cette boucle que si le prochain sommet n'a pas été choisi
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
		if (this->directionCreature + directionChoisie == FenetreEcran::VECTEUR2D_STOP) {
			// J'inverse l'alpha
			alpha = 1.f - alpha;

			// Je lui inverse sa position actuelle et sa position de destination
			Sommet<FormeEcran> * temp = this->prochainSommet;
			this->prochainSommet = this->sommetActuel;
			this->sommetActuel = temp;

			// Je lui inverse sa destination
			this->directionCreature = directionChoisie;

			// Je mets à jour ses voisins
			miseAJourVoisins();
		}

		if (prochainSommet != sommetActuel) {
			// On augmente son alpha et on met à jour la position du sprite
			alpha += velocite;
			infos->miseAJourPositionEcran(sommetActuel->valeur.getPositionEcran() + directionCreature * alpha);
			return true;
		}
	}
	return false;
}

const bool Creature::estImmobile() const {
	return alpha == 0.f;
}

bool Creature::dessiner() {
	return infos->dessiner();
}
