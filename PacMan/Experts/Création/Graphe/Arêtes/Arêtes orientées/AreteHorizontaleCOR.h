#pragma once
#include "./Experts/Cr�ation/Graphe/Ar�tes/CreationArete.h"
class AreteHorizontaleCOR :
	public CreationArete {
public:
	AreteHorizontaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteHorizontaleCOR();
};

