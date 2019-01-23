#pragma once
#include "EvenementCOR.h"
class ToucheCOR :
	public EvenementCOR {
protected:
	sf::Keyboard::Key touchePressee;
	std::map<int, std::string> touches;
	virtual void initMap() = 0;
public:
	ToucheCOR(FenetreEcran * fenetre);
	ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	~ToucheCOR();
	virtual const bool appliquer();
};