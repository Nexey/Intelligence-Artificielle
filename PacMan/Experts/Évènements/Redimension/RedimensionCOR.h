#pragma once
#include "../../EvenementCOR.h"
class RedimensionCOR :
	public EvenementCOR {
public:
	RedimensionCOR(FenetreEcran * fenetre);
	RedimensionCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~RedimensionCOR();

	// Fais en sorte que le ratio de la fen�tre reste inchang� (pas encore fonctionnel)
	const bool appliquer();
};