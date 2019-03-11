#pragma once
#include "Experts/Création/Graphe/Sommets/Types de sommets/SommetCOR.h"
#include "Ecran\Formes\Creature.h"
class CreatureSommetCOR :
	public SommetCOR {
	Creature * creature;
public:
	CreatureSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);
	virtual ~CreatureSommetCOR();

	virtual Creature * initialiserCreature(Sommet<FormeEcran> * sommet, const Vecteur2D & coords) = 0;

	virtual Sommet<FormeEcran> * construit(const char & forme, const Vecteur2D & coords);
};

