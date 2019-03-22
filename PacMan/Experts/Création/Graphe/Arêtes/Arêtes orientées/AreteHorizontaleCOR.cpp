#include "AreteHorizontaleCOR.h"

AreteHorizontaleCOR::AreteHorizontaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(1, 0), suivant) {
	this->textureArete = &this->fenetre->planche->areteH;
}

AreteHorizontaleCOR::~AreteHorizontaleCOR() {}