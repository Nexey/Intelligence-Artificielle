#include "ToucheCOR.h"

void ToucheCOR::initMap() {
	touches = {
		{ 76, "Bas Gauche" },
		{ 77, "Bas" },
		{ 78, "Bas Droite" },
		{ 79, "Gauche" },
		{ 81, "Droite" },
		{ 82, "Haut Gauche" },
		{ 83, "Haut" },
		{ 84, "Haut Droite" },
	};
}

ToucheCOR::ToucheCOR(FenetreEcran * fenetre) : EvenementCOR(fenetre, sf::Event::KeyPressed) {
	initMap();
}

ToucheCOR::ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : EvenementCOR(fenetre, sf::Event::KeyPressed, suivant) {
	initMap();
}

ToucheCOR::~ToucheCOR() {
	touches.clear();
}

const bool ToucheCOR::appliquer() {
	sf::Keyboard::Key touchePressee = getEvenement().key.code;

	// find est plus efficace que count, mais les deux sont valides
	if (touches.find(touchePressee) == touches.end()) return false;
	//if (touches.count(touchePressee) == 0) return false;

	std::cout << "Touche " << touches[touchePressee] << " entrée..." << std::endl;
	return true;
}
