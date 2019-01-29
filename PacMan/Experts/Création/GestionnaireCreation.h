#pragma once
#include "../../Ecran/Formes/FormeEcran.h"

class GestionnaireCreation {
public:
	// Prend un caract�re en entr�e, retourne la forme �cran associ�e
	// Il faut r�aliser une copie des coordonn�es
	virtual FormeEcran * gerer(const char & forme, const Vecteur2D & coords) = 0;
};