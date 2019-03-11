#pragma once
#include "Creature.h"
class Fantome :
	public Creature {
protected:
	std::map<int, Vecteur2D> directions;
public:
	Fantome(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~Fantome();

	operator std::string() const;
};

