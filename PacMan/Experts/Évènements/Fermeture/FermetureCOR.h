#pragma once
#include "../EvenementCOR.h"
class FermetureCOR :
	public EvenementCOR {
public:
	FermetureCOR(FenetreEcran * fenetre);
	FermetureCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~FermetureCOR();

	// Ferme la fen�tre
	const bool appliquer();
};