#pragma once
#include "./Experts/Cr�ation/Graphe/Ar�tes/CreationArete.h"
class AreteVerticaleCOR :
	public CreationArete {
public:
	AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteVerticaleCOR();
};

