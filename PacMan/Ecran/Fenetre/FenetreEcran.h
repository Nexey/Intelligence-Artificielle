#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <functional>
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
	// La transformation affine se charge de transformer des coordonnées écran en coordonnées réelles
	TransfoAffine2D transfoAffine;

	// Les différentes informations de la fenêtre
	unsigned ratio, largeur, hauteur;
	std::string nom;

	// Les coins relatifs de la fenêtre
	Vecteur2D coinBasGauche, coinHautDroit;

	// Interdiction des constructeurs
	FenetreEcran() = delete;
	FenetreEcran(const FenetreEcran&) = delete;

	// La fenêtre se charge des créatures à dessiner
	std::vector<Creature> listeCreature;
public:
	// Liste des directions possibles
	// Ce sont des Vecteur2D, ce qui permet de les additionner directement à une forme écran quelconque possédant
	// des Vecteur2D comme coordonnées
	static const Vecteur2D
		VECTEUR2D_BAS_GAUCHE,
		VECTEUR2D_BAS,
		VECTEUR2D_BAS_DROITE,
		VECTEUR2D_GAUCHE,
		VECTEUR2D_DROITE,
		VECTEUR2D_HAUT_GAUCHE,
		VECTEUR2D_HAUT,
		VECTEUR2D_HAUT_DROITE,
		VECTEUR2D_STOP;

	// La direction, elle est mise à jour dans l'expert qui récupère les touches tapées par l'utilisateur
	// Elle peut être changée par n'importe quelle autre classe
	Vecteur2D direction;

	// Le constructeur initialise aussi direction à (0, 0)
	FenetreEcran(const std::string & nom, const unsigned & largeur, const unsigned & hauteur, const Vecteur2D & coinBasGauche, const Vecteur2D & coinHautDroit, const unsigned & ratio);

	const TransfoAffine2D & getTransfoAffine() const;

	// Redimension quand l'évènement resize est lancé
	// Il faudrait essayer de garder le ratio et d'éviter que la fenêtre soit trop étendue d'un côté ou un autre
	void redimensionner();

	/// Getters
	const unsigned & getRatio() const;
	const unsigned & getLargeur() const;
	const unsigned & getHauteur() const;
	const std::string & getNom() const;
	const Vecteur2D & getCoinBasGauche() const;
	const Vecteur2D & getCoinHautDroit() const;

	// Les deux méthodes d'ajout de créature à la collection
	// Pas de clonage, les créatures à l'heure actuelle sont là juste pour tester
	void ajouterForme(Creature & c);
	const FenetreEcran * operator+(Creature & c);

	// Type pointeur de fonction qui prend en paramètre une référence sur une créature
	typedef void(FenetreEcran::*fctTraitement)(Creature &);

	// Appel sur la méthode de déplacement d'une créature en tenant compte des paramètres à initialiser
	void deplacerCreature(Creature & c);

	// Appel sur la méthode de dessin d'une créature, elle se charge de tout faire
	void dessinerCreature(Creature & c);

	// Cette fonction parcourt la liste de toutes les créatures
	// Le paramètre fctTraitement est un pointeur sur une fonction
	// Cela permet de factoriser beaucoup de code
	void traitementCreatures(fctTraitement);

	// Applique la transformation affine sur un Vecteur2D, càd transforme des coordonnées écrans en coordonnées réelles
	sf::Vector2f calculPos(const Vecteur2D& screenPos);
	virtual ~FenetreEcran();
};