#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <functional>
#include "../../Maths/TransfoAffine2D.h"
class Creature;

// Translate des coordonn�es doubles en coordonn�es float
inline const sf::Vector2f TransfoVecteur2DToVector2f(const Vecteur2D & v) {
	float x, y;
	v.arrondit(x, y);
	return sf::Vector2f(x, y);
}

class FenetreEcran :
	public sf::RenderWindow {
	// La transformation affine se charge de transformer des coordonn�es �cran en coordonn�es r�elles
	TransfoAffine2D transfoAffine;

	// Les diff�rentes informations de la fen�tre
	unsigned ratio, largeur, hauteur;
	std::string nom;

	// Les coins relatifs de la fen�tre
	Vecteur2D coinBasGauche, coinHautDroit;

	// Interdiction des constructeurs
	FenetreEcran() = delete;
	FenetreEcran(const FenetreEcran&) = delete;

	// La fen�tre se charge des cr�atures � dessiner
	std::vector<Creature> listeCreature;
public:
	// Liste des directions possibles
	// Ce sont des Vecteur2D, ce qui permet de les additionner directement � une forme �cran quelconque poss�dant
	// des Vecteur2D comme coordonn�es
	static const Vecteur2D
		VECTEUR2D_BAS_GAUCHE,
		VECTEUR2D_BAS,
		VECTEUR2D_BAS_DROITE,
		VECTEUR2D_GAUCHE,
		VECTEUR2D_DROITE,
		VECTEUR2D_HAUT_GAUCHE,
		VECTEUR2D_HAUT,
		VECTEUR2D_HAUT_DROITE;

	// La direction, elle est mise � jour dans l'expert qui r�cup�re les touches tap�es par l'utilisateur
	// Elle peut �tre chang�e par n'importe quelle autre classe
	Vecteur2D direction;

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

	typedef void(FenetreEcran::*fctTraitement)(Creature &);

	void deplacerCreature(Creature & c);
	void dessinerCreature(Creature & c);
	void traitementCreatures(fctTraitement);
	//void traitementCreatures(std::function<void(Creature&)> traitement);

	sf::Vector2f calculPos(const Vecteur2D& screenPos);
	virtual ~FenetreEcran();
};