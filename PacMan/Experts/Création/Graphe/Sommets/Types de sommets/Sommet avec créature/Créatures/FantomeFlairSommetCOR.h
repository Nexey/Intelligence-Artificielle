#pragma once
#include "./Experts/Création/Graphe/Sommets/Types de sommets/Sommet avec créature/Créatures/FantomeSommetCOR.h"
class FantomeFlairSommetCOR :
	public FantomeSommetCOR {
public:
	FantomeFlairSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Creature * initialiserCreature(Sommet<FormeEcran> * sommet, const Vecteur2D & coords);

	virtual ~FantomeFlairSommetCOR();
};