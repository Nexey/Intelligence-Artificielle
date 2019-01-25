#pragma once
#include "../../EvenementCOR.h"
class RedimensionCOR :
	public EvenementCOR {
public:
	RedimensionCOR(FenetreEcran * fenetre);
	RedimensionCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~RedimensionCOR();

	const bool appliquer();
};