#pragma once
#include "./Ecran/Formes/Creature.h"
class PacMan :
	public Creature {
public:
	PacMan(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran>* positionSommet, int choixNiveau);
	virtual ~PacMan();

	bool deplacer();
};

