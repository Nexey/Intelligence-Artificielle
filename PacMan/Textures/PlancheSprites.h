#pragma once
#include "SFML\Graphics.hpp"
#include <string>

// Cette classe va contenir tous les sprites existants
// Elle découpe la planche de textures passée en paramètres

// La positions des textures doivent être positionnée
// exactement comme dans la SpriteSheet de base.
// La taille totale peut cependant être modifiée,
// tout en restant une puissance de 2.

class PlancheSprites {
	PlancheSprites() = delete;
	PlancheSprites(const PlancheSprites&) = delete;

	unsigned ratioFenetre;
	unsigned taille;
	unsigned demiTaille;

	float ratioSprite;

	sf::Texture* planche;

public:
	PlancheSprites(const std::string &chemin, const unsigned &);
	PlancheSprites(sf::Texture * planche, const unsigned &);

	bool initialiserTextures();
	bool chargerSommet();
	bool chargerAretes();
	bool chargerCreatures();

	bool chargerTexture(sf::Sprite & texture, const unsigned & colonne, const unsigned & ligne);

	sf::Sprite sommet,
		areteH,
		areteV,
		pacman,
		fantomeJ,
		fantomeB,
		fantomeR,
		fantomeV;

	virtual ~PlancheSprites();
};

