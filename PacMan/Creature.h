#pragma once
#include "./Graphe/Graphe.h"
#include "./Ecran/Formes/FormeEcran.h"

class Creature {
protected:
	// alpha : si alpha == 0, alors la créature peut bouger. Autrement, Elle est en mouvement.
	// alpha varie de 0 à 1
	// alpha augmente en lui ajoutant velocity
	float alpha,
		// La velocité est ajouté aux coordonnées de la figure, ce qui permet un déplacement fluide
		velocite;


	Liste<Sommet<FormeEcran> * > * voisins;
	Iterateur<Sommet<FormeEcran> * > * iterateurVoisins;

	FenetreEcran * fenetre;
	Graphe<FormeEcran, FormeEcran> * niveau;
public:
	Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran> * positionSommet, Graphe<FormeEcran, FormeEcran> * niveau);
	virtual ~Creature();

	// Pour le moment, gère une forme sfml, mais plus tard ce sera des sprites
	sf::Shape * formeSFML;

	Vecteur2D directionCreature;

	Sommet<FormeEcran> * sommetActuel;
	Sommet<FormeEcran> * prochainSommet;

	// Déplace la créature jusqu'au prochain point
	// Actuellement, le déplacement ne peut pas être annulé
	bool deplacer();

	// Si alpha est 0, alors on peut la bouger
	// Il faut faire attention à lui mettre à jour sa direction si on veut la faire bouger après cet appel
	const bool estImmobile() const;

	void miseAJourPositionEcran(const Vecteur2D& nouvPos);
};