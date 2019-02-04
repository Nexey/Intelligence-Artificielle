#pragma once
#include "./Experts/Création/Graphe/Arêtes/CreationArete.h"
class AreteHorizontaleCOR :
	public CreationArete {
public:
	AreteHorizontaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteHorizontaleCOR();

	Arete<FormeEcran, FormeEcran> * construit(Sommet<FormeEcran> * s1, Sommet<FormeEcran> * s2);
};

