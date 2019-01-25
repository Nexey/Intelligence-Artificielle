#include "FermetureToucheCOR.h"

FermetureToucheCOR::FermetureToucheCOR(FenetreEcran * fenetre) : ToucheCOR(fenetre) {
	initMap();
}

FermetureToucheCOR::FermetureToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : ToucheCOR(fenetre, suivant) {
	initMap();
}

FermetureToucheCOR::~FermetureToucheCOR() {}

void FermetureToucheCOR::initMap() {
	this->codeTouchesEnStr = {
		{ sf::Keyboard::Escape, "Echappe" }
	};
}

const bool FermetureToucheCOR::appliquer() {
	if (trouveEvenementDansMap(this->codeTouchesEnStr)) {
		std::cout << "Fermeture de la fenêtre de jeu..." << std::endl;
		this->fenetre->close();
		return true;
	}
	return false;
}