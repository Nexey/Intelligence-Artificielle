#include "AreteAntiSlashCOR.h"

AreteAntiSlashCOR::AreteAntiSlashCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(1, -1), suivant) { 
	this->textureArete = &this->fenetre->planche->areteAntiSlash;
}

AreteAntiSlashCOR::~AreteAntiSlashCOR() {
}