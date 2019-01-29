#pragma once
#include "GestionnaireCreation.h"

class CreationCOR :
	public GestionnaireCreation {
	GestionnaireCreation * suivant;
protected:
	std::vector<char> formes;
	FenetreEcran * fenetre;
public:
	CreationCOR(FenetreEcran * fenetre, GestionnaireCreation * suivant = NULL);

	virtual FormeEcran * construit(const char & forme, const Vecteur2D & coords) = 0;

	bool peutGerer(const char & forme);
	FormeEcran * gerer(const char & forme, const Vecteur2D & coords);

	virtual ~CreationCOR();
};