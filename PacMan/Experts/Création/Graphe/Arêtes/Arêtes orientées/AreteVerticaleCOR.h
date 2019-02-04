#pragma once
#include "./Experts/Cr�ation/Graphe/Ar�tes/CreationArete.h"
class AreteVerticaleCOR :
	public CreationArete {
public:
	AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteVerticaleCOR();

	Arete<FormeEcran, FormeEcran> * construit(Sommet<FormeEcran> * s1, Sommet<FormeEcran> * s2);
};

