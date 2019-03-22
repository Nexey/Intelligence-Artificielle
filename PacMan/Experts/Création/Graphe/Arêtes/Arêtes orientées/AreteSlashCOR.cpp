#include "AreteSlashCOR.h"

AreteSlashCOR::AreteSlashCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(1, 1), suivant) {
	this->textureArete = &this->fenetre->planche->areteSlash;
}
AreteSlashCOR::~AreteSlashCOR() {}