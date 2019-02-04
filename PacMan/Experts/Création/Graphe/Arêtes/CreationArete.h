#pragma once
#include "./Experts/Création/Graphe/Arêtes/GestionnaireCreationAretes.h"
class CreationArete :
	public GestionnaireCreationAretes {
	GestionnaireCreationAretes * suivant;
protected:
	Vecteur2D direction;
	FenetreEcran * fenetre;
public:
	CreationArete(FenetreEcran * fenetre, const Vecteur2D & direction, GestionnaireCreationAretes * suivant = NULL);
	virtual ~CreationArete();

	virtual Arete<FormeEcran, FormeEcran> * construit(Sommet<FormeEcran> * s1, Sommet<FormeEcran> * s2) = 0;

	bool peutGerer(const Vecteur2D & direction);

	Arete<FormeEcran, FormeEcran> * gerer(Sommet<FormeEcran> * s1, Sommet<FormeEcran> * s2);
};