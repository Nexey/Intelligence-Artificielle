#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <functional>
#include "./Maths/TransfoAffine2D.h"
#include "Graphe\Graphe.h"
class Creature;
class FormeEcran;

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
public:
	std::vector<Graphe<FormeEcran, FormeEcran>*> * niveaux;

	int choixNiveau;

	std::map<int, std::vector<Creature*>> listeCreatureParNiveaux;

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
		VECTEUR2D_HAUT_DROITE,
		VECTEUR2D_STOP;

	// La direction, elle est mise � jour dans l'expert qui r�cup�re les touches tap�es par l'utilisateur
	// Elle peut �tre chang�e par n'importe quelle autre classe
	Vecteur2D direction;

	// Le constructeur initialise aussi direction � (0, 0)
	FenetreEcran(const std::string & nom, const unsigned & largeur, const unsigned & hauteur, const Vecteur2D & coinBasGauche, const Vecteur2D & coinHautDroit, const unsigned & ratio);

	const TransfoAffine2D & getTransfoAffine() const;

	// Redimension quand l'�v�nement resize est lanc�
	// Il faudrait essayer de garder le ratio et d'�viter que la fen�tre soit trop �tendue d'un c�t� ou un autre
	void redimensionner(const sf::Event & evenement);

	/// Getters
	const unsigned & getRatio() const;
	const unsigned & getLargeur() const;
	const unsigned & getHauteur() const;
	const std::string & getNom() const;
	const Vecteur2D & getCoinBasGauche() const;
	const Vecteur2D & getCoinHautDroit() const;

	// Les deux m�thodes d'ajout de cr�ature � la collection
	// Pas de clonage, les cr�atures � l'heure actuelle sont l� juste pour tester
	void ajouterForme(Creature * c);
	const FenetreEcran * operator+(Creature * c);

	// Type pointeur de fonction qui prend en param�tre une r�f�rence sur une cr�ature
	typedef bool(FenetreEcran::*fctTraitement)(Creature *);

	// Appel sur la m�thode de d�placement d'une cr�ature en tenant compte des param�tres � initialiser
	template<class T>
	bool deplacer(T * c);

	// Appel sur la m�thode de dessin d'une cr�ature, elle se charge de tout faire
	template<class T>
	bool dessiner(T * forme);

	// Cette fonction parcourt la liste de toutes les cr�atures
	// Le param�tre fctTraitement est un pointeur sur une fonction
	// Cela permet de factoriser beaucoup de code
	bool effectuer(fctTraitement);

//	void onResize();

	// Applique la transformation affine sur un Vecteur2D, c�d transforme des coordonn�es �crans en coordonn�es r�elles
	sf::Vector2f calculPos(const Vecteur2D& screenPos);
	virtual ~FenetreEcran();
};

template<class T>
inline bool FenetreEcran::deplacer(T * c) {
	return c->deplacer();
}

template<class T>
inline bool FenetreEcran::dessiner(T * forme) {
	return forme->dessiner();
}