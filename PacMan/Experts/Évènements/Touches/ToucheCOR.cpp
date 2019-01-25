#include "ToucheCOR.h"

ToucheCOR::ToucheCOR(FenetreEcran * fenetre) : EvenementCOR(fenetre, sf::Event::KeyPressed) {}

ToucheCOR::ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : EvenementCOR(fenetre, sf::Event::KeyPressed, suivant) {}

ToucheCOR::~ToucheCOR() {
	codeTouchesEnStr.clear();
}