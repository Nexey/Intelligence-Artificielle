#pragma once
#include "./Experts/Création/Graphe/Sommets/CreationSommetCOR.h"
class SommetCOR :
	public CreationSommetCOR {
public:
	SommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	Sommet<FormeEcran> * construit(const char & forme, const Vecteur2D & coords);

	virtual ~SommetCOR();
};