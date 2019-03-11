#include "PacmanSommetCOR.h"
#include "Experts\Création\Graphe\Sommets\Types de sommets\SommetCOR.h"
#include "Ecran\Formes\PacMan.h"

PacmanSommetCOR::PacmanSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : CreatureSommetCOR(fenetre, suivant) {
	formes.push_back('P');
}

Creature * PacmanSommetCOR::initialiserCreature(Sommet<FormeEcran>* sommet, const Vecteur2D & coords) {
	return new PacMan(new FormeEcran(&this->fenetre->planche->pacman, this->fenetre, coords), sommet, this->fenetre->choixNiveau);
}

PacmanSommetCOR::~PacmanSommetCOR() {}
