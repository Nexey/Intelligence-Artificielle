#pragma once
#include "../ToucheCOR.h"
class DeplacementToucheCOR :
	public ToucheCOR {

	// Collection qui translate les codes des touches en direction
	std::map<int, Vecteur2D> codeToucheEnDirection;
protected:
	void initMap();
public:
	// Membres statics, initialisés pour éviter de la redondance
	static const std::string
		BAS_GAUCHE_STR,
		BAS_STR,
		BAS_DROITE_STR,
		GAUCHE_STR,
		DROITE_STR,
		HAUT_GAUCHE_STR,
		HAUT_STR,
		HAUT_DROITE_STR;

	DeplacementToucheCOR(FenetreEcran * fenetre);
	DeplacementToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);
	virtual ~DeplacementToucheCOR();

	// Change la direction stockée dans la fenêtre quand une touche est appuyée
	const bool appliquer();
};