#pragma once
#include "./Experts/Création/Graphe/Arêtes/CreationArete.h"
class AreteVerticaleCOR :
	public CreationArete {
public:
	AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteVerticaleCOR();
};

