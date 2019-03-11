#include "Fantome.h"

Fantome::Fantome(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	Creature(infos, positionSommet, choixNiveau) {
	directions[0] = FenetreEcran::VECTEUR2D_BAS;
	directions[1] = FenetreEcran::VECTEUR2D_GAUCHE;
	directions[2] = FenetreEcran::VECTEUR2D_HAUT;
	directions[3] = FenetreEcran::VECTEUR2D_DROITE;
	srand((unsigned)time(NULL));
	directionAleatoire = (rand() % (directions.size()));
}

Fantome::~Fantome() {}

const Vecteur2D Fantome::selectionDirection() {
	// Une chance sur 32 de changer de trajectoire
	if (rand() % 32 < 1)
		directionAleatoire = (rand() % (directions.size()));
	return this->directions[directionAleatoire];
}