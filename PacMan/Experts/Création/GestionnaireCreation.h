#pragma once
#include "../../Ecran/Formes/FormeEcran.h"

class GestionnaireCreation {
public:
	// Prend un caractère en entrée, retourne la forme écran associée
	// Il faut réaliser une copie des coordonnées
	virtual FormeEcran * gerer(const char & forme, const Vecteur2D & coords) = 0;
};