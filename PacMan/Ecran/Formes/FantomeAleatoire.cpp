#include "FantomeAleatoire.h"

FantomeAleatoire::FantomeAleatoire(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) : 
	Fantome(infos, positionSommet, choixNiveau) {
	srand((unsigned)time(NULL));
	directionAleatoire = (rand() % (directions.size()));
}

FantomeAleatoire::~FantomeAleatoire() {}

const Vecteur2D FantomeAleatoire::selectionDirection() {
	// Une chance sur 32 de changer de trajectoire
	if (rand() % 32 < 1)
		directionAleatoire = (rand() % (directions.size()));
	return this->directions[directionAleatoire];
}