#pragma once
#include "./Experts/Cr�ation/Graphe/Sommets/Types de sommets/Sommet avec cr�ature/CreatureSommetCOR.h"
class FantomeSommetCOR :
	public CreatureSommetCOR {
public:
	FantomeSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);
	virtual ~FantomeSommetCOR();
};