#pragma once
#include "../Fenetre/FenetreEcran.h"

class FormeEcran {
	FormeEcran() = delete;
protected:
	// Une forme garde un pointeur sur la fen�tre, � voir si �a reste utile ou non
	FenetreEcran * fenetre;
public:
	// Pour le moment, g�re une forme sfml, mais plus tard ce sera des sprites
	sf::Shape * formeSFML;
	FormeEcran(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran = Vecteur2D(0, 0));
	FormeEcran(const FormeEcran &);

	// La position �cran, par transformation affine
	Vecteur2D positionEcran;

	// Applique la transformation affine sur les coordonn�es de la forme SFML
	void miseAJourPositionEcran(const Vecteur2D& nouvPos);

	// Appelle le dessin sur la forme
	const bool dessine();

	/// Getters
	FenetreEcran * getFenetre() const;
	const Vecteur2D getPositionEcran() const;

	operator std::string() const;

	virtual ~FormeEcran();

	friend std::ostream & operator<<(std::ostream&, const FormeEcran&);
};