#pragma once
#include "./Experts/Création/Graphe/Arêtes/CreationArete.h"
class AreteAntiSlashCOR :
	public CreationArete {
public:
	AreteAntiSlashCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteAntiSlashCOR();
};

