#pragma once
#include "./Experts/Création/Graphe/Sommets/CreationSommetCOR.h"
class FantomeSommetCOR :
	public CreationSommetCOR {
public:
	FantomeSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	Sommet<FormeEcran> * construit(const char & forme, const Vecteur2D & coords);

	virtual ~FantomeSommetCOR();
};

