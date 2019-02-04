#pragma once
#include "./Experts/Création/Graphe/Arêtes/CreationArete.h"
class AreteVerticaleCOR :
	public CreationArete {
public:
	AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteVerticaleCOR();

	Arete<FormeEcran, FormeEcran> * construit(Sommet<FormeEcran> * s1, Sommet<FormeEcran> * s2);
};

