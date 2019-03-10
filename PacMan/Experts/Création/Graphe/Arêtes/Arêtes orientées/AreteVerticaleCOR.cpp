#include "AreteVerticaleCOR.h"

AreteVerticaleCOR::AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(0, 1), suivant) {}

AreteVerticaleCOR::~AreteVerticaleCOR() {}

Arete<FormeEcran, FormeEcran>* AreteVerticaleCOR::construit(Sommet<FormeEcran>* s1, Sommet<FormeEcran>* s2) {
	return new Arete<FormeEcran, FormeEcran>(FormeEcran(&this->fenetre->planche->areteV, this->fenetre, (s1->valeur.getPositionEcran() + s2->valeur.getPositionEcran()) * 0.5), s1, s2);
}
