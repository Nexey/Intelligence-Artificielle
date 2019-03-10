#pragma once
#include "SFML\Graphics.hpp"
#include <string>

// Cette classe va contenir tous les sprites existants
// Elle d�coupe la planche de textures pass�e en param�tres

// La positions des textures doivent �tre positionn�e
// exactement comme dans la SpriteSheet de base.
// La taille totale peut cependant �tre modifi�e,
// tout en restant une puissance de 2.

class PlancheSprites {
	PlancheSprites() = delete;
	PlancheSprites(const PlancheSprites&) = delete;

	unsigned taille;
	unsigned demiTaille;

	sf::Texture* planche;

public:
	PlancheSprites(const std::string &chemin);
	PlancheSprites(sf::Texture * planche);

	bool chargerTextures();
	bool chargerSommet();
	bool chargerAretes();
	bool chargerCreatures();

	sf::Sprite sommet,
		areteH,
		areteV;
	virtual ~PlancheSprites();
};

