#include "AreteVerticaleCOR.h"

AreteVerticaleCOR::AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(0, 1), suivant) {
	this->textureArete = &this->fenetre->planche->areteV;
}

AreteVerticaleCOR::~AreteVerticaleCOR() {}