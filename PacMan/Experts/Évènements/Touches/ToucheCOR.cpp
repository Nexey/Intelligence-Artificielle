#include "ToucheCOR.h"

ToucheCOR::ToucheCOR(FenetreEcran * fenetre) : EvenementCOR(fenetre, sf::Event::KeyPressed) {}

ToucheCOR::ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : EvenementCOR(fenetre, sf::Event::KeyPressed, suivant) {}

const bool ToucheCOR::appliquer() {
	return trouveEvenementDansMap(this->codeTouchesEnStr);
}

ToucheCOR::~ToucheCOR() {
	codeTouchesEnStr.clear();
}