#include "AreteHorizontaleCOR.h"

AreteHorizontaleCOR::AreteHorizontaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(1, 0), suivant) {}

AreteHorizontaleCOR::~AreteHorizontaleCOR() {}

Arete<FormeEcran, FormeEcran>* AreteHorizontaleCOR::construit(Sommet<FormeEcran>* s1, Sommet<FormeEcran>* s2) {
	return new Arete<FormeEcran, FormeEcran>(FormeEcran(&this->fenetre->planche->areteH, this->fenetre, (s1->valeur.getPositionEcran() + s2->valeur.getPositionEcran()) * 0.5), s1, s2);
}
