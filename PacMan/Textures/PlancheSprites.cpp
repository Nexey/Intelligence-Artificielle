#include "PlancheSprites.h"
#include "./Exceptions/Erreur.h"

PlancheSprites::~PlancheSprites() {}

PlancheSprites::PlancheSprites(const std::string & chemin) {
	planche = new sf::Texture();
	if (!planche->loadFromFile(chemin)) throw Erreur("Probleme lors du chargement de la texture.");
	this->chargerTextures();
}

PlancheSprites::PlancheSprites(sf::Texture * planche) : planche(planche) {
	this->chargerTextures();
}

bool PlancheSprites::chargerTextures() {
	unsigned largeur, hauteur;
	sf::Vector2u tailleTexture = planche->getSize();
	largeur = tailleTexture.x;
	hauteur = tailleTexture.y;

	if (largeur != hauteur)			throw Erreur("SpriteSheet invalide.");
	if (largeur & (largeur - 1))	throw Erreur("SpriteSheet invalide.");
	if (largeur < 16)				
		throw Erreur("SpriteSheet invalide.");

	// On divise 4 fois par deux la largeur
	taille = largeur >> 4;

	// On divise la taille en deux
	demiTaille = taille >> 1;

	chargerAretes();
	chargerSommet();
	return true;
}

bool PlancheSprites::chargerSommet() {
	sommet.setTexture(*planche);
	sommet.setTextureRect(sf::IntRect(12 * taille, 0, taille, taille));
	sommet.setOrigin((float)demiTaille, (float)demiTaille);
	sommet.setScale(0.2f, 0.2f);
	return true;
}

bool PlancheSprites::chargerAretes() {
	areteH.setTexture(*planche);
	areteH.setTextureRect(sf::IntRect(12 * taille, 1 * taille, taille, taille));
	areteH.setOrigin((float)demiTaille, (float)demiTaille);
	areteH.setScale(0.2f, 0.2f);

	areteV.setTexture(*planche);
	areteV.setTextureRect(sf::IntRect(12 * taille, 3 * taille, taille, taille));
	areteV.setOrigin((float)demiTaille, (float)demiTaille);
	areteV.setScale(0.2f, 0.2f);
	return false;
}

bool PlancheSprites::chargerCreatures() {
	return false;
}
