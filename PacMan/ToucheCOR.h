#pragma once
#include "EvenementCOR.h"
class ToucheCOR :
	public EvenementCOR {
	std::map<int, std::string> touches;
	void initMap();
public:
	ToucheCOR(FenetreEcran * fenetre);
	ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	~ToucheCOR();

	const bool appliquer();
};

