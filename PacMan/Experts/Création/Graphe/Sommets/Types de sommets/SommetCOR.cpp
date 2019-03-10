#include "SommetCOR.h"

SommetCOR::SommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : CreationSommetCOR(fenetre, suivant) {
	formes.push_back('1');
	formes.push_back('2');
	formes.push_back('3');
	formes.push_back('4');
	formes.push_back('5');
}

Sommet<FormeEcran> * SommetCOR::construit(const char & forme, const Vecteur2D & coords) {
	return new Sommet<FormeEcran>(FormeEcran(&this->fenetre->planche->sommet, fenetre, coords));
}

SommetCOR::~SommetCOR() {}