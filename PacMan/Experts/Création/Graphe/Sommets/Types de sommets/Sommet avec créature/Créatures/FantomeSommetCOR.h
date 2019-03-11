#pragma once
#include "./Experts/Création/Graphe/Sommets/Types de sommets/Sommet avec créature/CreatureSommetCOR.h"
class FantomeSommetCOR :
	public CreatureSommetCOR {
public:
	FantomeSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);
	virtual ~FantomeSommetCOR();
};