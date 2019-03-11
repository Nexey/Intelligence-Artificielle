#pragma once
#include "./Ecran/Formes/FormeEcran.h"

class Creature {
protected:
	// alpha : si alpha == 0, alors la créature peut bouger. Autrement, Elle est en mouvement.
	// alpha varie de 0 à 1
	// alpha augmente en lui ajoutant velocity
	float alpha,
		// La velocité est ajouté aux coordonnées de la figure, ce qui permet un déplacement fluide
		velocite;

	Liste<Sommet<FormeEcran> * > * listeVoisins;
	Iterateur<Sommet<FormeEcran> * > * iterateurVoisins;

	int choixNiveau;

	FormeEcran * infos;

	void miseAJourVoisins();

	Vecteur2D directionCreature;

	virtual const Vecteur2D selectionDirection() = 0;
public:
	Creature(FormeEcran * infos, Sommet<FormeEcran> * positionSommet, int choixNiveau);
	virtual ~Creature();

	Sommet<FormeEcran> * sommetActuel;
	Sommet<FormeEcran> * prochainSommet;

	// Déplace la créature jusqu'au prochain point
	// Actuellement, le déplacement ne peut pas être annulé
	virtual bool deplacer();

	// Si alpha est 0, alors on peut la bouger
	// Il faut faire attention à lui mettre à jour sa direction si on veut la faire bouger après cet appel
	const bool estImmobile() const;

	const Vecteur2D getPositionEcran() const;

	bool dessiner();

	virtual operator std::string() const;
};