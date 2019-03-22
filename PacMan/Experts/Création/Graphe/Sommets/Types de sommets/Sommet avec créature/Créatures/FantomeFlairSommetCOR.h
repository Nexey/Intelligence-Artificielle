#pragma once
#include "./Experts/Cr�ation/Graphe/Sommets/Types de sommets/Sommet avec cr�ature/Cr�atures/FantomeSommetCOR.h"
class FantomeFlairSommetCOR :
	public FantomeSommetCOR {
public:
	FantomeFlairSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Creature * initialiserCreature(Sommet<FormeEcran> * sommet, const Vecteur2D & coords);

	virtual ~FantomeFlairSommetCOR();
};