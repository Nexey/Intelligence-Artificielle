#include "FantomeSommetCOR.h"
#include "Experts\Création\Graphe\Sommets\Types de sommets\SommetCOR.h"
#include "Ecran\Formes\FantomeFlair.h"
#include "FantomeFlairSommetCOR.h"

FantomeFlairSommetCOR::FantomeFlairSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant)
	: FantomeSommetCOR(fenetre, suivant) {
	// F comme Flair
	this->formes.push_back('F');
}

FantomeFlairSommetCOR::~FantomeFlairSommetCOR() {}

Creature * FantomeFlairSommetCOR::initialiserCreature(Sommet<FormeEcran>* sommet, const Vecteur2D & coords) {
	return new FantomeFlair(new FormeEcran(&this->fenetre->planche->fantomeV, this->fenetre, coords), sommet, this->fenetre->choixNiveau);
}
