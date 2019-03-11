#include "PacmanSommetCOR.h"
#include "Experts\Création\Graphe\Sommets\Types de sommets\SommetCOR.h"
#include "Ecran\Formes\PacMan.h"

PacmanSommetCOR::PacmanSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : CreationSommetCOR(fenetre, suivant) {
	formes.push_back('P');
}

Sommet<FormeEcran>* PacmanSommetCOR::construit(const char & forme, const Vecteur2D & coords) {
	CreationSommetCOR * chaineSommetCOR = new SommetCOR(fenetre);
	Sommet<FormeEcran> * sommet = chaineSommetCOR->construit('3', coords);

	// Ajout du PacMan dans la liste de la fenêtre
	Creature * pacman = new PacMan(new FormeEcran(&this->fenetre->planche->pacman, this->fenetre, coords), sommet, this->fenetre->choixNiveau);

	fenetre->listeCreatureParNiveaux[fenetre->choixNiveau].push_back(pacman);

	delete chaineSommetCOR;
	return sommet;
}

PacmanSommetCOR::~PacmanSommetCOR() {}
