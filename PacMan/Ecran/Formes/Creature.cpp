#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran)
	: FormeEcran(formeSFML, fenetre, positionEcran), alpha(0.f), velocite(0.05f) {}

void Creature::deplacer() {
	alpha += velocite;
	// Si alpha vaut 1.f ou plus, alors la créature a fini son déplacement
	// On peut donc lui mettre alpha à 0 et lui mettre sa nouvelle position en dure
	// Elle s'arrête de bouger
	if (alpha >= 1.f) {
		alpha = 0.f;
		this->positionEcran = this->nouvellePositionEcran;
		this->formeSFML->setPosition(fenetre->calculPos(this->positionEcran));

		this->fenetre->direction = Vecteur2D(0, 0);

#ifdef DEBUG
		std::cout << "Nouvelle position : " << this->getPositionEcran() << std::endl;
		std::cout << "Origine : " << this->formeSFML->getOrigin().x << ", " << this->formeSFML->getOrigin().y << std::endl;
#endif

	}
	// La créature est en mouvement
	else {
		// Il faut maintenant mettre à jour la position à l'écran
		this->formeSFML->setPosition(fenetre->calculPos(
			Vecteur2D(
				this->positionEcran.x + this->directionCreature.x * alpha,
				this->positionEcran.y + this->directionCreature.y * alpha
			)
		)
		);
	}
}

const bool Creature::peutBouger() const {
	return alpha == 0;
}

Creature::~Creature() {}
