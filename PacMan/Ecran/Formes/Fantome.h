#pragma once
#include "Creature.h"
class Fantome :
	public Creature {
	int directionAleatoire;
public:
	Fantome(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~Fantome();

	bool deplacer();

	std::map<int, Vecteur2D> directions;
};

