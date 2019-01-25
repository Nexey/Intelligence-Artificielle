#pragma once
#include "FormeEcran.h"
class Creature :
	public FormeEcran {
	Creature() = delete;
public:
	Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran = Vecteur2D(0, 0));
	virtual ~Creature();
};

