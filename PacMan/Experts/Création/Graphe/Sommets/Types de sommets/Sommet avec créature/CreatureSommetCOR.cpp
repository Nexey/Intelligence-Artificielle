#include "CreatureSommetCOR.h"

CreatureSommetCOR::CreatureSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : SommetCOR(fenetre, suivant) {}

CreatureSommetCOR::~CreatureSommetCOR() {}

Sommet<FormeEcran>* CreatureSommetCOR::construit(const char & forme, const Vecteur2D & coords) {
	Sommet<FormeEcran> * tmp = SommetCOR::construit(forme, coords);
	this->fenetre->ajouterForme(initialiserCreature(tmp, coords));
	return tmp;
}