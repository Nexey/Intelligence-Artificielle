#pragma once
#include "./Experts/Cr�ation/Graphe/Ar�tes/CreationArete.h"
class AreteAntiSlashCOR :
	public CreationArete {
public:
	AreteAntiSlashCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant = NULL);
	virtual ~AreteAntiSlashCOR();
};

