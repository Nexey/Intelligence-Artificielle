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
		{ sf::Keyboard::Numpad1, FenetreEcran::VECTEUR2D_BAS_GAUCHE },
		{ sf::Keyboard::Numpad2, FenetreEcran::VECTEUR2D_BAS },
		{ sf::Keyboard::Numpad3, FenetreEcran::VECTEUR2D_BAS_DROITE },
		{ sf::Keyboard::Numpad4, FenetreEcran::VECTEUR2D_GAUCHE },
		{ sf::Keyboard::Numpad6, FenetreEcran::VECTEUR2D_DROITE },
		{ sf::Keyboard::Numpad7, FenetreEcran::VECTEUR2D_HAUT_GAUCHE },
		{ sf::Keyboard::Numpad8, FenetreEcran::VECTEUR2D_HAUT },
		{ sf::Keyboard::Numpad9, FenetreEcran::VECTEUR2D_HAUT_DROITE }//,
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
		{ sf::Keyboard::Numpad1, BAS_GAUCHE_STR },
		{ sf::Keyboard::Numpad2, BAS_STR },
		{ sf::Keyboard::Numpad3, BAS_DROITE_STR },
		{ sf::Keyboard::Numpad4, GAUCHE_STR },
		{ sf::Keyboard::Numpad6, DROITE_STR },
		{ sf::Keyboard::Numpad7, HAUT_GAUCHE_STR },
		{ sf::Keyboard::Numpad8, HAUT_STR },
		{ sf::Keyboard::Numpad9, HAUT_DROITE_STR }
	};
}

const bool DeplacementToucheCOR::appliquer() {
	if (ToucheCOR::appliquer()) {
		this->fenetre->direction = codeToucheEnDirection[touchePressee];
		/*
#ifdef _DEBUG
		std::cout << "Touche " << codeTouchesEnStr[touchePressee] << " entrée..." << std::endl;
		std::cout << this->fenetre->direction << std::endl;
#endif
*/
		return true;
	}
	return false;
}