#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../Maths/TransfoAffine2D.h"

// Translate des coordonnées doubles en coordonnées float
inline const sf::Vector2f TransfoVecteur2DToVector2f(const Vecteur2D & v) {
	float x, y;
	v.arrondit(x, y);
	return sf::Vector2f(x, y);
}

class FenetreEcran :
	public sf::RenderWindow {
	TransfoAffine2D transfoAffine;
	unsigned ratio, largeur, hauteur;
	std::string nom;
	Vecteur2D coinBasGauche, coinHautDroit;
	FenetreEcran() = delete;
	FenetreEcran(const FenetreEcran&) = delete;
public:
	static const int BAS_GAUCHE = 1;
	static const int BAS = 2;
	static const int BAS_DROITE = 3;
	static const int GAUCHE = 4;
	static const int DROITE = 5;
	static const int HAUT_GAUCHE = 6;
	static const int HAUT = 7;
	static const int HAUT_DROITE = 8;

	static int direction;

	FenetreEcran(const std::string & nom, const unsigned & largeur, const unsigned & hauteur, const Vecteur2D & coinBasGauche, const Vecteur2D & coinHautDroit, const unsigned & ratio);

	const TransfoAffine2D & getTransfoAffine() const;
	void redimensionner();

	const unsigned & getRatio() const;
	const unsigned & getLargeur() const;
	const unsigned & getHauteur() const;
	const std::string & getNom() const;
	const Vecteur2D & getCoinBasGauche() const;
	const Vecteur2D & getCoinHautDroit() const;

	sf::Vector2f calculPos(const Vecteur2D& screenPos);
	virtual ~FenetreEcran();
};