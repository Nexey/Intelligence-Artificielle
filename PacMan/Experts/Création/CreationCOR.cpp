#include "CreationCOR.h"

CreationCOR::CreationCOR(FenetreEcran * fenetre, GestionnaireCreation * suivant) : fenetre(fenetre), suivant(suivant) {}

bool CreationCOR::peutGerer(const char & forme) {
	return (std::find(formes.begin(), formes.end(), forme) != formes.end());
}

FormeEcran * CreationCOR::gerer(const char & forme, const Vecteur2D & coords) {
	if (peutGerer(forme))
		return construit(forme, coords);

	if (suivant != NULL)
		return suivant->gerer(forme, coords);
	
	return nullptr;
}

CreationCOR::~CreationCOR() {}