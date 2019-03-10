#pragma once
#include "Creature.h"
class Fantome :
	public Creature {
	int directionAleatoire;
public:
	Fantome(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~Fantome();

	const Vecteur2D selectionDirection();

	//bool deplacer();

	std::map<int, Vecteur2D> directions;
};

