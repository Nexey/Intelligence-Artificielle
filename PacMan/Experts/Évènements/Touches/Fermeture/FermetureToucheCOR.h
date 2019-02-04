#pragma once
#include "./Experts/Évènements/Touches/ToucheCOR.h"
class FermetureToucheCOR :
	public ToucheCOR {
protected:
	void initMap();
public:
	FermetureToucheCOR(FenetreEcran * fenetre);
	FermetureToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~FermetureToucheCOR();

	// Quand la touche échappe est appuyée, la fenêtre est fermée
	// Semblable au premier expert, mais pas tout à fait pareil
	const bool appliquer();
};