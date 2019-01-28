#pragma once
#include "FormeEcran.h"
class Creature :
	public FormeEcran {
	Creature() = delete;
protected:
	// alpha : si alpha == 0, alors la créature peut bouger. Autrement, Elle est en mouvement.
	// alpha varie de 0 à 1
	// alpha augmente en lui ajoutant velocity
	float alpha,
		// La velocité est ajouté aux coordonnées de la figure, ce qui permet un déplacement fluide
		velocite;
public:
	Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran = Vecteur2D(0, 0));

	// La direction à suivre
	// Attention : Il faut la mettre à jour au moment où on commence le déplacement
	// C'est à dire lui donner la valeur de la dernière direction rentrée
	Vecteur2D directionCreature;

	// La nouvelle position à l'écran
	// Attention à l'initialiser au moment où on commence le déplacement
	Vecteur2D nouvellePositionEcran;
	
	// Déplace la créature jusqu'au prochain point
	// Actuellement, le déplacement ne peut pas être annulé
	bool deplacer();

	// Si alpha est 0, alors on peut la bouger
	// Il faut faire attention à lui mettre à jour sa direction si on veut la faire bouger après cet appel
	const bool estImmobile() const;
	
	virtual ~Creature();
};

