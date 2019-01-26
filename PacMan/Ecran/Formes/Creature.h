#pragma once
#include "FormeEcran.h"
class Creature :
	public FormeEcran {
	Creature() = delete;
protected:
	// alpha : si alpha == 0, alors la cr�ature peut bouger. Autrement, Elle est en mouvement.
	// alpha varie de 0 � 1
	// alpha augmente en lui ajoutant velocity
	float alpha,
		// La velocit� est ajout� aux coordonn�es de la figure, ce qui permet un d�placement fluide
		velocite;
public:
	Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran = Vecteur2D(0, 0));

	// La direction � suivre
	// Attention : Il faut la mettre � jour au moment o� on commence le d�placement
	// C'est � dire lui donner la valeur de la derni�re direction rentr�e
	Vecteur2D directionCreature;

	// La nouvelle position � l'�cran
	// Attention � l'initialiser au moment o� on commence le d�placement
	Vecteur2D nouvellePositionEcran;
	
	// D�place la cr�ature jusqu'au prochain point
	// Actuellement, le d�placement ne peut pas �tre annul�
	void deplacer();

	// Si alpha est 0, alors on peut la bouger
	// Il faut faire attention � lui mettre � jour sa direction si on veut la faire bouger apr�s cet appel
	const bool peutBouger() const;
	
	virtual ~Creature();
};

