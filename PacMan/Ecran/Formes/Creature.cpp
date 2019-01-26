#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran)
	: FormeEcran(formeSFML, fenetre, positionEcran), alpha(0.f), velocite(0.05f) {}

void Creature::deplacer() {
	Vecteur2D nouvPos;
	alpha += velocite;
	// Si alpha vaut 1.f ou plus, alors la créature a fini son déplacement
	// On peut donc lui mettre alpha à 0 et lui mettre sa nouvelle position en dure
	// Elle s'arrête de bouger
	if (alpha >= 1.f) {
		alpha = 0.f;
		nouvPos = this->nouvellePositionEcran;
		this->positionEcran = nouvPos;

		// Pour tester, je remets la direction à (0, 0) sinon la créature se baladerait indéfiniment
		this->fenetre->direction = Vecteur2D(0, 0);

#ifdef _DEBUG
		std::cout << "Nouvelle position : " << this->getPositionEcran() << std::endl;
		std::cout << "Origine : " << this->formeSFML->getOrigin().x << ", " << this->formeSFML->getOrigin().y << std::endl;
#endif
	}
	// La créature est en mouvement
	else
		// Il faut maintenant mettre à jour la nouvelle position
		// La formule est la suivante
		// position actuelle + direction * alpha
		// La direction est du style (0, 1) ou (-1, -1), le fait de la multiplier par alpha ne va
		// donc mettre à jour que les coordonnées de la direction souhaitée (si c'est 0 la multiplication a lieu mais ça reste 0)
		// On obtient donc une direction générale que l'on peut additionner à notre position actuelle
		// Vecteur2D prévoit l'addition et la multiplication entre deux Vecteur2D et des double (ici alpha est un float donc petite conversion de données
		nouvPos = Vecteur2D(this->positionEcran + this->directionCreature * alpha);
	// On met à jour la position à l'écran
	this->formeSFML->setPosition(fenetre->calculPos(nouvPos));
}

const bool Creature::peutBouger() const {
	return alpha == 0;
}

Creature::~Creature() {}
