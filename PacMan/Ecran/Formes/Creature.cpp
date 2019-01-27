#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran)
	: FormeEcran(formeSFML, fenetre, positionEcran), alpha(0.f), velocite(0.05f) {}

void Creature::deplacer() {
	Vecteur2D nouvPos;
	alpha += velocite;
	// Si alpha vaut 1.f ou plus, alors la cr�ature a fini son d�placement
	// On peut donc lui mettre alpha � 0 et lui mettre sa nouvelle position en dure
	// Elle s'arr�te de bouger
	if (alpha >= 1.f) {
		alpha = 0.f;
		nouvPos = this->nouvellePositionEcran;
		this->positionEcran = nouvPos;

		// Pour tester, je remets la direction � (0, 0) sinon la cr�ature se baladerait ind�finiment
		this->fenetre->direction = Vecteur2D(0, 0);

		/*
#ifdef _DEBUG
		std::cout << "Nouvelle position : " << this->getPositionEcran() << std::endl;
		std::cout << "Origine : " << this->formeSFML->getOrigin().x << ", " << this->formeSFML->getOrigin().y << std::endl;
#endif
*/
	}
	// La cr�ature est en mouvement
	else
		// Il faut maintenant mettre � jour la nouvelle position
		// La formule est la suivante
		// position actuelle + direction * alpha
		// La direction est du style (0, 1) ou (-1, -1), le fait de la multiplier par alpha ne va
		// donc mettre � jour que les coordonn�es de la direction souhait�e (si c'est 0 la multiplication a lieu mais �a reste 0)
		// On obtient donc une direction g�n�rale que l'on peut additionner � notre position actuelle
		// Vecteur2D pr�voit l'addition et la multiplication entre deux Vecteur2D ainsi qu'avec des doubles (ici alpha est un float donc petite conversion de donn�es)
		nouvPos = Vecteur2D(this->positionEcran + this->directionCreature * alpha);
	// On met � jour la position � l'�cran
	this->setPos(nouvPos);
}

const bool Creature::peutBouger() const {
	return alpha == 0;
}

Creature::~Creature() {}
