#pragma once
#include "./Experts/Cr�ation/Graphe/Sommets/Types de sommets/Sommet avec cr�ature/CreatureSommetCOR.h"
class PacmanSommetCOR :
	public CreatureSommetCOR {
public:
	PacmanSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Creature * initialiserCreature(Sommet<FormeEcran> * sommet, const Vecteur2D & coords);

	virtual ~PacmanSommetCOR();
};

