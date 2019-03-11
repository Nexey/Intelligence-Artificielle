#pragma once
#include "./Experts/Cr�ation/Graphe/Sommets/CreationSommetCOR.h"
class SommetCOR :
	public CreationSommetCOR {
public:
	SommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Sommet<FormeEcran> * construit(const char & forme, const Vecteur2D & coords);

	virtual ~SommetCOR();
};