#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & posEcran)
	: FormeEcran(formeSFML, fenetre, posEcran), alpha(0.f), velocite(0.05f) {}

bool Creature::deplacer() {
	// DEBUG : Sert à arrêter le pacman
	if (this->directionCreature == FenetreEcran::VECTEUR2D_STOP)
		return false;
	Vecteur2D nouvPos;
	alpha += velocite;
	// Si alpha vaut 1.f ou plus, alors la créature a fini son déplacement
	// On peut donc lui mettre alpha à 0 et lui mettre sa nouvelle position en dure
	// Elle s'arrête de bouger
	if (alpha >= 1.f) {
		alpha = 0.f;
		nouvPos = this->nouvellePositionEcran;
		this->positionEcran = nouvPos;
	}
	// La créature est en mouvement
	else {
		// Si la direction a changé, alors si la direction de la créature + la direction de la fenêtre = (0, 0) donc il faut faire un demi-tour
		if (this->directionCreature + this->fenetre->direction == FenetreEcran::VECTEUR2D_STOP) {
			// J'inverse l'alpha
			alpha = 1.f - alpha;

			// Je lui inverse sa position actuelle et sa position de destination
			Vecteur2D temp = this->nouvellePositionEcran;
			this->nouvellePositionEcran = this->positionEcran;
			this->positionEcran = temp;

			// Je lui inverse sa destination
			this->directionCreature = this->fenetre->direction;
		}

		// Il faut maintenant mettre à jour la nouvelle position
		// La formule est la suivante
		// position actuelle + direction * alpha
		// La direction est du style (0, 1) ou (-1, -1), le fait de la multiplier par alpha ne va
		// donc mettre à jour que les coordonnées de la direction souhaitée (si c'est 0 la multiplication a lieu mais ça reste 0)
		// On obtient donc une direction générale que l'on peut additionner à notre position actuelle
		// Vecteur2D prévoit l'addition et la multiplication entre deux Vecteur2D ainsi qu'avec des doubles (ici alpha est un float donc petite conversion de données)
		nouvPos = Vecteur2D(this->positionEcran + this->directionCreature * alpha);
	}
	// On met à jour la position à l'écran
	this->miseAJourPositionEcran(nouvPos);
	return true;
}


const bool Creature::estImmobile() const {
	return alpha == 0.f;
}

Creature::~Creature() {}