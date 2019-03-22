#pragma once
#include "./Ecran/Fenetre/FenetreEcran.h"

class FormeEcran {
	FormeEcran() = delete;
protected:
	// Une forme garde un pointeur sur la fenêtre
	FenetreEcran * fenetre;
public:
	sf::Sprite * texture;
	FormeEcran(sf::Sprite * texture, FenetreEcran * fenetre, const Vecteur2D & positionEcran = Vecteur2D(0, 0));
	FormeEcran(const FormeEcran &);

	// La position écran, par transformation affine
	Vecteur2D positionEcran;

	// Applique la transformation affine sur les coordonnées de la forme SFML
	void miseAJourPositionEcran(const Vecteur2D& nouvPos);

	// Applique la transformation affine sur les coordonnées de la texture
	void miseAJourPositionTexture(const Vecteur2D& nouvPos);

	// Appelle le dessin sur la forme
	const bool dessiner();

	/// Getters
	FenetreEcran * getFenetre() const;
	const Vecteur2D getPositionEcran() const;

	virtual operator std::string() const;

	virtual ~FormeEcran();

	friend std::ostream & operator<<(std::ostream&, const FormeEcran&);
};