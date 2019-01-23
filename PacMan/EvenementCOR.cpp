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
		this->evenement = evenement;
		return appliquer();
	}
	if (suivant != NULL)
		return suivant->gerer(evenement);
	return false;
}