#pragma once
#include "FantomeAleatoire.h"
class FantomeFlair :
	public FantomeAleatoire {
	Creature * pacman;
public:
	FantomeFlair(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~FantomeFlair();

	virtual const Vecteur2D selectionDirection();
};

