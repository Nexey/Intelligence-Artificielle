#pragma once
#include "./Experts/Création/Graphe/Sommets/Types de sommets/Sommet avec créature/CreatureSommetCOR.h"
class PacmanSommetCOR :
	public CreatureSommetCOR {
public:
	PacmanSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Creature * initialiserCreature(Sommet<FormeEcran> * sommet, const Vecteur2D & coords);

	virtual ~PacmanSommetCOR();
};

