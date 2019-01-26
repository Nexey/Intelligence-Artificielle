#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "../../Maths/TransfoAffine2D.h"
class Creature;

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

	std::vector<Creature> listeCreature;
public:
	/*
	static const int BAS_GAUCHE = 1;
	static const int BAS = 2;
	static const int BAS_DROITE = 3;
	static const int GAUCHE = 4;
	static const int DROITE = 5;
	static const int HAUT_GAUCHE = 6;
	static const int HAUT = 7;
	static const int HAUT_DROITE = 8;*/

	static const Vecteur2D
		VECTEUR2D_BAS_GAUCHE,
		VECTEUR2D_BAS,
		VECTEUR2D_BAS_DROITE,
		VECTEUR2D_GAUCHE,
		VECTEUR2D_DROITE,
		VECTEUR2D_HAUT_GAUCHE,
		VECTEUR2D_HAUT,
		VECTEUR2D_HAUT_DROITE;

	static Vecteur2D direction;

	FenetreEcran(const std::string & nom, const unsigned & largeur, const unsigned & hauteur, const Vecteur2D & coinBasGauche, const Vecteur2D & coinHautDroit, const unsigned & ratio);

	const TransfoAffine2D & getTransfoAffine() const;
	void redimensionner();

	const unsigned & getRatio() const;
	const unsigned & getLargeur() const;
	const unsigned & getHauteur() const;
	const std::string & getNom() const;
	const Vecteur2D & getCoinBasGauche() const;
	const Vecteur2D & getCoinHautDroit() const;

	void ajouterForme(Creature & c);
	const FenetreEcran * operator+(Creature & c);

	// Les deux fonctions suivantes sont trop semblables
	void deplacerCreatures();
	void dessinerCreatures();

	sf::Vector2f calculPos(const Vecteur2D& screenPos);
	virtual ~FenetreEcran();
};