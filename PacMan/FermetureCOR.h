#pragma once
#include "EvenementCOR.h"
class FermetureCOR :
	public EvenementCOR {
public:
	FermetureCOR(FenetreEcran * fenetre);
	FermetureCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	~FermetureCOR();

	const bool appliquer();
};