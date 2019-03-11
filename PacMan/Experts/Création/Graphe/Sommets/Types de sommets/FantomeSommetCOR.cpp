#include "FantomeSommetCOR.h"
#include "Experts\Cr�ation\Graphe\Sommets\Types de sommets\SommetCOR.h"
#include "Ecran\Formes\Fantome.h"

FantomeSommetCOR::FantomeSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : CreationSommetCOR(fenetre, suivant) {
	formes.push_back('F');
}

Sommet<FormeEcran>* FantomeSommetCOR::construit(const char & forme, const Vecteur2D & coords) {
	CreationSommetCOR * chaineSommetCOR = new SommetCOR(fenetre);
	Sommet<FormeEcran> * sommet = chaineSommetCOR->construit('3', coords);

	// Ajout du PacMan dans la liste de la fen�tre
	Creature * fantome = new Fantome(new FormeEcran(&this->fenetre->planche->fantomeJ, this->fenetre, coords), sommet, this->fenetre->choixNiveau);

	fenetre->listeCreatureParNiveaux[fenetre->choixNiveau].push_back(fantome);

	delete chaineSommetCOR;
	return sommet;
}

FantomeSommetCOR::~FantomeSommetCOR() {}
