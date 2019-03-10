#include "FantomeSommetCOR.h"
#include "Experts\Création\Graphe\Sommets\Types de sommets\SommetCOR.h"
#include "Ecran\Formes\Fantome.h"

FantomeSommetCOR::FantomeSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : CreationSommetCOR(fenetre, suivant) {
	formes.push_back('F');
}

Sommet<FormeEcran>* FantomeSommetCOR::construit(const char & forme, const Vecteur2D & coords) {
	CreationSommetCOR * chaineSommetCOR = new SommetCOR(fenetre);
	Sommet<FormeEcran> * sommet = chaineSommetCOR->construit('3', coords);

	// Ajout du PacMan dans la liste de la fenêtre
	Creature * fantome = new Fantome(new sf::RectangleShape(sf::Vector2f((float)fenetre->getRatio(), (float)fenetre->getRatio())), fenetre, sommet, fenetre->choixNiveau);
	fantome->formeSFML->setFillColor(sf::Color::Yellow);
	fantome->formeSFML->setOutlineColor(sf::Color::White);
	fantome->formeSFML->setOutlineThickness(2.f);

	fenetre->listeCreatureParNiveaux[fenetre->choixNiveau].push_back(fantome);

	delete chaineSommetCOR;
	return sommet;
}

FantomeSommetCOR::~FantomeSommetCOR() {}
