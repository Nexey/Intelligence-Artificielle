#include "DeplacementToucheCOR.h"

DeplacementToucheCOR::DeplacementToucheCOR(FenetreEcran * fenetre) : ToucheCOR(fenetre) {
	initMap();
}

DeplacementToucheCOR::DeplacementToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : ToucheCOR(fenetre, suivant) {
	initMap();
}

DeplacementToucheCOR::~DeplacementToucheCOR() {}

void DeplacementToucheCOR::initMap() {
	this->touches = {
		{ 76, "Bas Gauche" },
		{ 77, "Bas" },
		{ 78, "Bas Droite" },
		{ 79, "Gauche" },
		{ 81, "Droite" },
		{ 82, "Haut Gauche" },
		{ 83, "Haut" },
		{ 84, "Haut Droite" },
		// Ici c'est quand le pavé numérique est éteint
		{ 63, "Bas Gauche" },
		{ 74, "Bas" },
		{ 62, "Bas Droite" },
		{ 71, "Gauche" },
		{ 72, "Droite" },
		{ 64, "Haut Gauche" },
		{ 73, "Haut" },
		{ 61, "Haut Droite" }
	};
}

const bool DeplacementToucheCOR::appliquer() {
	if (ToucheCOR::appliquer()) {
		std::cout << "Touche " << touches[touchePressee] << " entrée..." << std::endl;
		return true;
	}
	return false;
}