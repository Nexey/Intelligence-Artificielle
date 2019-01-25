#pragma once
#include "../Fenetre/FenetreEcran.h"

class FormeEcran {
	FormeEcran() = delete;
protected:
	FenetreEcran * fenetre;
	Vecteur2D positionEcran;
public:
	sf::Shape * formeSFML;
	FormeEcran(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran = Vecteur2D(0, 0));
	FormeEcran(const FormeEcran &);

	void setPos(const Vecteur2D& nouvPos);
	const bool dessine();

	FenetreEcran * getFenetre() const;
	const Vecteur2D getPositionEcran() const;

	virtual ~FormeEcran();
};