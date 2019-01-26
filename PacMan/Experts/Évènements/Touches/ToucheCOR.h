#pragma once
#include "../../EvenementCOR.h"
class ToucheCOR :
	public EvenementCOR {
protected:
	// Code de la touche pressée
	sf::Keyboard::Key touchePressee;

	// Collection qui gère la conversion en code d'une touche en string
	std::map<sf::Keyboard::Key, std::string> codeTouchesEnStr;

	// Appel à l'initialisation de la collection
	// Doit être appelée dans les constructeurs des classes dérivées
	virtual void initMap() = 0;

	// Fonction template qui s'occupe de vérifier si la collection peut gérer le code touche rentré
	// Elle est template car je peux gère une map de <int, string> et une autre de <int, int> ou une de <sf::KeyBoard::Key, Vecteur2D> ...
	template<class S, class T>
	bool trouveEvenementDansMap(const std::map<S, T> & codeTouches);
public:
	ToucheCOR(FenetreEcran * fenetre);
	ToucheCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant);

	virtual const bool appliquer();
	virtual ~ToucheCOR();
};

template<class S, class T>
inline bool ToucheCOR::trouveEvenementDansMap(const std::map<S, T>& codeTouches) {
	touchePressee = getEvenement().key.code;
	return codeTouches.find(touchePressee) != codeTouches.end();
}