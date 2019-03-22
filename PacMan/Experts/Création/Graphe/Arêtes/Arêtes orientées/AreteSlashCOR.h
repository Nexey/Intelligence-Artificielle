#pragma once
#include "./Experts/Création/Graphe/Arêtes/CreationArete.h"
class AreteSlashCOR :
	public CreationArete {
public:
	AreteSlashCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteSlashCOR();
};

