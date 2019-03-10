#pragma once
#include "./Experts/Cr�ation/Graphe/Sommets/CreationSommetCOR.h"
class PacmanSommetCOR :
	public CreationSommetCOR {
public:
	PacmanSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	Sommet<FormeEcran> * construit(const char & forme, const Vecteur2D & coords);

	virtual ~PacmanSommetCOR();
};

