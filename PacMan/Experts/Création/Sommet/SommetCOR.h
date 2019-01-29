#pragma once
#include "../CreationCOR.h"
class SommetCOR :
	public CreationCOR {
public:
	SommetCOR(FenetreEcran * fenetre, GestionnaireCreation * suivant = NULL);

	FormeEcran * construit(const char & forme, const Vecteur2D & coords);

	virtual ~SommetCOR();
};