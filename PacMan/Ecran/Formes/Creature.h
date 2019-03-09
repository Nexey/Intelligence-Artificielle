#pragma once
#include "./Graphe/Graphe.h"
#include "./Ecran/Formes/FormeEcran.h"

class Creature {
protected:
	// alpha : si alpha == 0, alors la cr�ature peut bouger. Autrement, Elle est en mouvement.
	// alpha varie de 0 � 1
	// alpha augmente en lui ajoutant velocity
	float alpha,
		// La velocit� est ajout� aux coordonn�es de la figure, ce qui permet un d�placement fluide
		velocite;


	Liste<Sommet<FormeEcran> * > * voisins;
	Iterateur<Sommet<FormeEcran> * > * iterateurVoisins;

	FenetreEcran * fenetre;
	Graphe<FormeEcran, FormeEcran> * niveau;
public:
	Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran> * positionSommet, Graphe<FormeEcran, FormeEcran> * niveau);
	virtual ~Creature();

	// Pour le moment, g�re une forme sfml, mais plus tard ce sera des sprites
	sf::Shape * formeSFML;

	Vecteur2D directionCreature;

	Sommet<FormeEcran> * sommetActuel;
	Sommet<FormeEcran> * prochainSommet;

	// D�place la cr�ature jusqu'au prochain point
	// Actuellement, le d�placement ne peut pas �tre annul�
	bool deplacer();

	// Si alpha est 0, alors on peut la bouger
	// Il faut faire attention � lui mettre � jour sa direction si on veut la faire bouger apr�s cet appel
	const bool estImmobile() const;

	void miseAJourPositionEcran(const Vecteur2D& nouvPos);
};