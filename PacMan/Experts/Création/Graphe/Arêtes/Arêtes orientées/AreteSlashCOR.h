#pragma once
#include "./Experts/Cr�ation/Graphe/Ar�tes/CreationArete.h"
class AreteSlashCOR :
	public CreationArete {
public:
	AreteSlashCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteSlashCOR();
};

