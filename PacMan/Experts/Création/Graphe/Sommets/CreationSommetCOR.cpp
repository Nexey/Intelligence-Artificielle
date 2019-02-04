#include "CreationSommetCOR.h"

CreationSommetCOR::CreationSommetCOR(FenetreEcran * fenetre, GestionnaireCreationSommet * suivant) : fenetre(fenetre), suivant(suivant) {}

bool CreationSommetCOR::peutGerer(const char & forme) {
	return (std::find(formes.begin(), formes.end(), forme) != formes.end());
}

Sommet<FormeEcran> * CreationSommetCOR::gerer(const char & forme, const Vecteur2D & coords) {
	if (peutGerer(forme))
		return construit(forme, coords);

	if (suivant != NULL)
		return suivant->gerer(forme, coords);
	
	return nullptr;
}

CreationSommetCOR::~CreationSommetCOR() {}