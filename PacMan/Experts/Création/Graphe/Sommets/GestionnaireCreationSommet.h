#pragma once
#include "./Graphe/Sommet.h"
#include "./Ecran/Formes/FormeEcran.h"

class GestionnaireCreationSommet {
public:
	// Prend un caractère en entrée, retourne le sommet associé
	virtual Sommet<FormeEcran> * gerer(const char & forme, const Vecteur2D & coords) = 0;
};