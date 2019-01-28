#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran)
	: FormeEcran(formeSFML, fenetre, positionEcran), alpha(0.f), velocite(0.05f) {}

bool Creature::deplacer() {
	// DEBUG : Sert � arr�ter le pacman
	if (this->directionCreature == FenetreEcran::VECTEUR2D_STOP)
		return false;
	Vecteur2D nouvPos;
	alpha += velocite;
	// Si alpha vaut 1.f ou plus, alors la cr�ature a fini son d�placement
	// On peut donc lui mettre alpha � 0 et lui mettre sa nouvelle position en dure
	// Elle s'arr�te de bouger
	if (alpha >= 1.f) {
		alpha = 0.f;
		nouvPos = this->nouvellePositionEcran;
		this->positionEcran = nouvPos;
	}
	// La cr�ature est en mouvement
	else {
		// Si la direction a chang�, alors si la direction de la cr�ature + la direction de la fen�tre = (0, 0) donc il faut faire un demi-tour
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

		// Il faut maintenant mettre � jour la nouvelle position
		// La formule est la suivante
		// position actuelle + direction * alpha
		// La direction est du style (0, 1) ou (-1, -1), le fait de la multiplier par alpha ne va
		// donc mettre � jour que les coordonn�es de la direction souhait�e (si c'est 0 la multiplication a lieu mais �a reste 0)
		// On obtient donc une direction g�n�rale que l'on peut additionner � notre position actuelle
		// Vecteur2D pr�voit l'addition et la multiplication entre deux Vecteur2D ainsi qu'avec des doubles (ici alpha est un float donc petite conversion de donn�es)
		nouvPos = Vecteur2D(this->positionEcran + this->directionCreature * alpha);
	}
	// On met � jour la position � l'�cran
	this->miseAJourPositionEcran(nouvPos);
	return true;
}

const bool Creature::estImmobile() const {
	return alpha == 0.f;
}

Creature::~Creature() {}