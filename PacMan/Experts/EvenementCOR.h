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

	// Traitement de l'�v�nement, renvoie false si le type d'�v�nement �tait correct mais que l'�v�nement en question
	// n'�tait pas traitable. Par exemple un expert peut s'occuper des touches directionnelles et un autre de la touche
	// �chappe, ce sont les deux m�mes types d'�v�nement mais ils ne peuvent pas s'occuper de toutes les touches � la fois
	virtual const bool appliquer() = 0;

	// Renvoie l'�v�nement pour le consulter
	const sf::Event & getEvenement() const;

	// Un expert peut g�rer un �v�nement si le type d'�v�nement correspond � celui avec lequel il a �t� construit
	const bool peutGerer(const sf::Event::EventType & evenementType) const;

	// Cette m�thode s'occupe de r�cup�rer un �v�nement, le stocker et y appliquer un traitement
	const bool gerer(const sf::Event & evenementType);

	virtual ~EvenementCOR();
};