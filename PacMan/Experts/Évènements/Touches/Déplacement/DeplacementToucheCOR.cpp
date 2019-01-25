#include "DeplacementToucheCOR.h"

const std::string
DeplacementToucheCOR::BAS_GAUCHE_STR = "Bas Gauche",
DeplacementToucheCOR::BAS_STR = "Bas",
DeplacementToucheCOR::BAS_DROITE_STR = "Bas Droite",
DeplacementToucheCOR::GAUCHE_STR = "Gauche",
DeplacementToucheCOR::DROITE_STR = "Droite",
DeplacementToucheCOR::HAUT_GAUCHE_STR = "Haut Gauche",
DeplacementToucheCOR::HAUT_STR = "Haut",
DeplacementToucheCOR::HAUT_DROITE_STR = "Haut Droite";

DeplacementToucheCOR::DeplacementToucheCOR(FenetreEcran * fenetre) : ToucheCOR(fenetre) {
	initMap();
}

DeplacementToucheCOR::DeplacementToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : ToucheCOR(fenetre, suivant) {
	initMap();
}

DeplacementToucheCOR::~DeplacementToucheCOR() {
	codeToucheEnDirection.clear();
}

void DeplacementToucheCOR::initMap() {

	this->codeToucheEnDirection = {
		{ sf::Keyboard::Numpad1, FenetreEcran::BAS_GAUCHE },
		{ sf::Keyboard::Numpad2, FenetreEcran::BAS },
		{ sf::Keyboard::Numpad3, FenetreEcran::BAS_DROITE },
		{ sf::Keyboard::Numpad4, FenetreEcran::GAUCHE },
		{ sf::Keyboard::Numpad6, FenetreEcran::DROITE },
		{ sf::Keyboard::Numpad7, FenetreEcran::HAUT_GAUCHE },
		{ sf::Keyboard::Numpad8, FenetreEcran::HAUT },
		{ sf::Keyboard::Numpad9, FenetreEcran::HAUT_DROITE }//,
		// Ici c'est quand le pavé numérique est éteint
		// Je ne pense pas les utiliser parce qu'elles entrent en conflit avec d'autres touches
		/*
		{ sf::Keyboard::End, FenetreEcran::BAS_GAUCHE },
		{ sf::Keyboard::Down, FenetreEcran::BAS },
		{ sf::Keyboard::PageDown, FenetreEcran::BAS_DROITE },
		{ sf::Keyboard::Left, FenetreEcran::GAUCHE },
		{ sf::Keyboard::Right, FenetreEcran::DROITE },
		{ sf::Keyboard::Home, FenetreEcran::HAUT_GAUCHE },
		{ sf::Keyboard::Up, FenetreEcran::HAUT },
		{ sf::Keyboard::PageUp, FenetreEcran::HAUT_DROITE }
		*/
	};

	this->codeTouchesEnStr = {
		{ FenetreEcran::BAS_GAUCHE, BAS_GAUCHE_STR },
		{ FenetreEcran::BAS, BAS_STR },
		{ FenetreEcran::BAS_DROITE, BAS_DROITE_STR },
		{ FenetreEcran::GAUCHE, GAUCHE_STR },
		{ FenetreEcran::DROITE, DROITE_STR },
		{ FenetreEcran::HAUT_GAUCHE, HAUT_GAUCHE_STR },
		{ FenetreEcran::HAUT, HAUT_STR },
		{ FenetreEcran::HAUT_DROITE, HAUT_DROITE_STR }
	};
}

const bool DeplacementToucheCOR::appliquer() {
	if (trouveEvenementDansMap(this->codeToucheEnDirection)) {
		this->fenetre->direction = codeToucheEnDirection[touchePressee];
		std::cout << "Touche " << codeTouchesEnStr[this->fenetre->direction] << " entrée..." << std::endl;
		return true;
	}
	return false;
}