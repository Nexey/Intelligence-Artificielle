#pragma once
#include "../ToucheCOR.h"
class FermetureToucheCOR :
	public ToucheCOR {
protected:
	void initMap();
public:
	FermetureToucheCOR(FenetreEcran * fenetre);
	FermetureToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~FermetureToucheCOR();
	const bool appliquer();
};