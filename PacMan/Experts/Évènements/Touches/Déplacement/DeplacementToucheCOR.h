#pragma once
#include "../ToucheCOR.h"
class DeplacementToucheCOR :
	public ToucheCOR {
protected:
	void initMap();
public:
	DeplacementToucheCOR(FenetreEcran * fenetre);
	DeplacementToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	~DeplacementToucheCOR();
	const bool appliquer();
};