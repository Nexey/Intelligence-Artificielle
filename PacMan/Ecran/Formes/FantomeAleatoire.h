#pragma once
#include "Fantome.h"
class FantomeAleatoire :
	public Fantome {
	int directionAleatoire;
public:
	FantomeAleatoire(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~FantomeAleatoire();

	virtual const Vecteur2D selectionDirection();
};

