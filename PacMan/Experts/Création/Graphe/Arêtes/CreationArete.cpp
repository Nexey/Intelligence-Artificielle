#include "CreationArete.h"

CreationArete::CreationArete(FenetreEcran * fenetre, const Vecteur2D & direction, GestionnaireCreationAretes * suivant) : fenetre(fenetre), direction(direction), suivant(suivant) {}

CreationArete::~CreationArete() {}

bool CreationArete::peutGerer(const Vecteur2D & direction) {
	// La partie comment�e peut cr�er une ar�te de fin � deb alors que je veux cr�er seulement des ar�tes de deb � fin
	return this->direction == direction/* || this->direction == -direction*/;
}

Arete<FormeEcran, FormeEcran>* CreationArete::gerer(Sommet<FormeEcran>* s1, Sommet<FormeEcran>* s2) {
	if (peutGerer(s1->valeur.getPositionEcran() - s2->valeur.getPositionEcran()))
		return construit(s1, s2);

	if (suivant != NULL)
		return suivant->gerer(s1, s2);
	
	return nullptr;
}