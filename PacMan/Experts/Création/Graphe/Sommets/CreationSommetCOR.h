#pragma once
#include "./Experts/Création/Graphe/Sommets/GestionnaireCreationSommet.h"

class CreationSommetCOR :
	public GestionnaireCreationSommet {
	GestionnaireCreationSommet * suivant;
protected:
	std::vector<char> formes;
	FenetreEcran * fenetre;
public:
	CreationSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant = NULL);

	virtual Sommet<FormeEcran> * construit(const char & forme, const Vecteur2D & coords) = 0;
	
	bool peutGerer(const char & forme);
	Sommet<FormeEcran> * gerer(const char & forme, const Vecteur2D & coords);

	virtual ~CreationSommetCOR();
};