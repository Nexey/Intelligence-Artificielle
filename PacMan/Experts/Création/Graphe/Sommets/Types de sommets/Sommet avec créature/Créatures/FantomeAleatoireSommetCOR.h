#pragma once
#include "FantomeSommetCOR.h"
class FantomeAleatoireSommetCOR :
	public FantomeSommetCOR {
public:
	FantomeAleatoireSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Creature * initialiserCreature(Sommet<FormeEcran> * sommet, const Vecteur2D & coords);

	virtual ~FantomeAleatoireSommetCOR();
};

