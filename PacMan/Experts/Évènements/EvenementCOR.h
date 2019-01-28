#pragma once
#include "GestionnaireEvenement.h"
class EvenementCOR :
	public GestionnaireEvenement {
	GestionnaireEvenement * suivant;
	sf::Event evenement;
	sf::Event::EventType typeEvenement;
protected:
	// Un évènement garde un pointeur sur la fenêtre pour y apporter des modifications
	FenetreEcran * fenetre;
public:
	EvenementCOR(FenetreEcran * fenetre, const sf::Event::EventType & evenementType);
	EvenementCOR(FenetreEcran * fenetre, const sf::Event::EventType & evenementType, GestionnaireEvenement * suivant);

	// Traitement de l'évènement, renvoie false si le type d'évènement était correct mais que l'évènement en question
	// n'était pas traitable. Par exemple un expert peut s'occuper des touches directionnelles et un autre de la touche
	// échappe, ce sont les deux mêmes types d'évènement mais ils ne peuvent pas s'occuper de toutes les touches à la fois
	virtual const bool appliquer() = 0;

	// Renvoie l'évènement pour le consulter
	const sf::Event & getEvenement() const;

	// Un expert peut gérer un évènement si le type d'évènement correspond à celui avec lequel il a été construit
	const bool peutGerer(const sf::Event::EventType & evenementType) const;

	// Cette méthode s'occupe de récupérer un évènement, le stocker et y appliquer un traitement
	const bool gerer(const sf::Event & evenementType);

	virtual ~EvenementCOR();
};