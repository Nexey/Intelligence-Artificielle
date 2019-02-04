#pragma once
#include "./Experts/Évènements/EvenementCOR.h"
class RedimensionCOR :
	public EvenementCOR {
public:
	RedimensionCOR(FenetreEcran * fenetre);
	RedimensionCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~RedimensionCOR();

	// Fais en sorte que le ratio de la fenêtre reste inchangé (pas encore fonctionnel)
	const bool appliquer();
};