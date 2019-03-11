#include "Fantome.h"

Fantome::Fantome(FormeEcran * infos, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	Creature(infos, positionSommet, choixNiveau) {
	directions[0] = FenetreEcran::VECTEUR2D_BAS;
	directions[1] = FenetreEcran::VECTEUR2D_GAUCHE;
	directions[2] = FenetreEcran::VECTEUR2D_HAUT;
	directions[3] = FenetreEcran::VECTEUR2D_DROITE;
}

Fantome::~Fantome() {}

Fantome::operator std::string() const {
	return "fantome";
}