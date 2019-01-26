#include "EvenementCOR.h"

EvenementCOR::EvenementCOR(FenetreEcran * fenetre, const sf::Event::EventType & typeEvenement) : fenetre(fenetre), typeEvenement(typeEvenement), suivant(NULL) {}

EvenementCOR::EvenementCOR(FenetreEcran * fenetre, const sf::Event::EventType & typeEvenement, GestionnaireEvenement * suivant) : fenetre(fenetre), typeEvenement(typeEvenement), suivant(suivant) {}

const sf::Event & EvenementCOR::getEvenement() const {
	return evenement;
}

const bool EvenementCOR::peutGerer(const sf::Event::EventType & typeEvenement) const {
	return typeEvenement == this->typeEvenement;
}

const bool EvenementCOR::gerer(const sf::Event & evenement) {
	if (peutGerer(evenement.type)) {
		// On stocke l'�v�nement pour pouvoir y r�cup�rer des informations dans les epxerts
		this->evenement = evenement;

		// Appliquer peut retourner faux, dans ce cas l� je souhaite sortir du premier if
		// Ce n'est donc pas une erreur que ce ne soit pas �crit "return appliquer();"
		// Bien qu'un expert puisse g�rer un certain type d'�v�nement, il se peut qu'il ne puisse
		// pas appliquer son traitement sur l'�v�nement l� en particulier, il faut donc le passer
		// � l'expert suivant
		if (appliquer()) return true;
	}
	if (suivant != NULL)
		return suivant->gerer(evenement);
	return false;
}

EvenementCOR::~EvenementCOR() {}