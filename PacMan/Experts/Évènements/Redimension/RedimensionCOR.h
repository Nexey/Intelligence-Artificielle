#pragma once
#include "../../EvenementCOR.h"
class RedimensionCOR :
	public EvenementCOR {
public:
	RedimensionCOR(FenetreEcran * fenetre);
	RedimensionCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	~RedimensionCOR();

	const bool appliquer();
};