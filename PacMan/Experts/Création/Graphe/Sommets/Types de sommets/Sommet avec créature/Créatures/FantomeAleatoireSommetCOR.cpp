#include "FantomeAleatoireSommetCOR.h"
#include "Ecran\Formes\FantomeAleatoire.h"
#include "Ecran\Formes\FantomeFlair.h"

FantomeAleatoireSommetCOR::FantomeAleatoireSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant)
	: FantomeSommetCOR(fenetre, suivant) {
	// A comme Aléatoire
	this->formes.push_back('A');
}

Creature * FantomeAleatoireSommetCOR::initialiserCreature(Sommet<FormeEcran>* sommet, const Vecteur2D & coords) {
	return new FantomeAleatoire(new FormeEcran(&this->fenetre->planche->fantomeJ, this->fenetre, coords), sommet, this->fenetre->choixNiveau);
}

FantomeAleatoireSommetCOR::~FantomeAleatoireSommetCOR() {}