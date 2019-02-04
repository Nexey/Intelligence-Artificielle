#pragma once
#include "./Graphe/Arete.h"
#include "./Graphe/Sommet.h"
#include "./Ecran/Formes/FormeEcran.h"

class GestionnaireCreationAretes {
public:
	virtual Arete<FormeEcran, FormeEcran> * gerer(Sommet<FormeEcran> * s1, Sommet<FormeEcran> * s2) = 0;
};