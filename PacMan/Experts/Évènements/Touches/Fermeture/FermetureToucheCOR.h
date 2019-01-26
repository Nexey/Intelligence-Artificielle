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

	// Quand la touche �chappe est appuy�e, la fen�tre est ferm�e
	// Semblable au premier expert, mais pas tout � fait pareil
	const bool appliquer();
};