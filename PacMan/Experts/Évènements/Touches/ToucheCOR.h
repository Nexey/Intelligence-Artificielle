#pragma once
#include "../../EvenementCOR.h"
class ToucheCOR :
	public EvenementCOR {
protected:
	// Code de la touche press�e
	sf::Keyboard::Key touchePressee;

	// Collection qui g�re la conversion en code d'une touche en string
	std::map<sf::Keyboard::Key, std::string> codeTouchesEnStr;

	// Appel � l'initialisation de la collection
	// Doit �tre appel�e dans les constructeurs des classes d�riv�es
	virtual void initMap() = 0;

	// Fonction template qui s'occupe de v�rifier si la collection peut g�rer le code touche rentr�
	// Elle est template car je peux g�re une map de <int, string> et une autre de <int, int> ou une de <sf::KeyBoard::Key, Vecteur2D> ...
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