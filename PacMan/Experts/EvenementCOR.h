#pragma once
#include "GestionnaireEvenement.h"
class EvenementCOR :
	public GestionnaireEvenement {
	GestionnaireEvenement * suivant;
	sf::Event evenement;
	sf::Event::EventType typeEvenement;
public:
	FenetreEcran * fenetre;
	EvenementCOR(FenetreEcran * fenetre, const sf::Event::EventType & evenementType);
	EvenementCOR(FenetreEcran * fenetre, const sf::Event::EventType & evenementType, GestionnaireEvenement * suivant);

	virtual const bool appliquer() = 0;

	const sf::Event & getEvenement() const;

	const bool peutGerer(const sf::Event::EventType & evenementType) const;
	const bool gerer(const sf::Event & evenementType);

	virtual ~EvenementCOR();
};