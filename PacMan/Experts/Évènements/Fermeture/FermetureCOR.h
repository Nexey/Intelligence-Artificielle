#pragma once
#include "./Experts/Évènements/EvenementCOR.h"
class FermetureCOR :
	public EvenementCOR {
public:
	FermetureCOR(FenetreEcran * fenetre);
	FermetureCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~FermetureCOR();

	// Ferme la fenêtre
	const bool appliquer();
};