#include "PacMan.h"

PacMan::PacMan(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	Creature(formeSFML, fenetre, positionSommet, choixNiveau) {}

PacMan::~PacMan() {}

const Vecteur2D PacMan::selectionDirection() {
	return this->fenetre->direction;
}