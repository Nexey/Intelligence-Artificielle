#include "ToucheCOR.h"

ToucheCOR::ToucheCOR(FenetreEcran * fenetre) : EvenementCOR(fenetre, sf::Event::KeyPressed) {}

ToucheCOR::ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : EvenementCOR(fenetre, sf::Event::KeyPressed, suivant) {}

ToucheCOR::~ToucheCOR() {
	touches.clear();
}

const bool ToucheCOR::appliquer() {
	touchePressee = getEvenement().key.code;
	return touches.find(touchePressee) != touches.end();
	/*
	sf::Keyboard::Key touchePressee = getEvenement().key.code;
	// find est plus efficace que count, mais les deux sont valides
	if (touches.find(touchePressee) == touches.end()) {
		// DEBUG
		// std::cout << touchePressee << std::endl;
		return false;
	}
	//if (touches.count(touchePressee) == 0) return false;

	std::cout << "Touche " << touches[touchePressee] << " entrée..." << std::endl;
	return true;
	*/
}
