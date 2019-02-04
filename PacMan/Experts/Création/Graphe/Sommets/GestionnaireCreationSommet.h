#pragma once
#include "./Graphe/Sommet.h"
#include "./Ecran/Formes/FormeEcran.h"

class GestionnaireCreationSommet {
public:
	// Prend un caract�re en entr�e, retourne le sommet associ�
	virtual Sommet<FormeEcran> * gerer(const char & forme, const Vecteur2D & coords) = 0;
};