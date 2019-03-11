#pragma once
#include "./Ecran/Formes/Creature.h"
class PacMan :
	public Creature {
public:
	PacMan(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~PacMan();

	const Vecteur2D selectionDirection();
};

