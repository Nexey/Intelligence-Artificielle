#include "PacMan.h"

PacMan::PacMan(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	Creature(infos, positionSommet, choixNiveau) {}

PacMan::~PacMan() {}

const Vecteur2D PacMan::selectionDirection() {
	return this->infos->getFenetre()->direction;
}