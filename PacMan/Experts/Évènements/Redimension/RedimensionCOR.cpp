#include "RedimensionCOR.h"

RedimensionCOR::RedimensionCOR(FenetreEcran * fenetre) : EvenementCOR(fenetre, sf::Event::Resized) {}

RedimensionCOR::RedimensionCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : EvenementCOR(fenetre, sf::Event::Resized, suivant) {}

RedimensionCOR::~RedimensionCOR() {}

const bool RedimensionCOR::appliquer() {
	this->fenetre->redimensionner(this->getEvenement());
	return true;
}