#include "PlancheSprites.h"
#include "./Exceptions/Erreur.h"

PlancheSprites::~PlancheSprites() {}

PlancheSprites::PlancheSprites(const std::string & chemin, const unsigned & ratio) : ratioFenetre(ratio) {
	planche = new sf::Texture();
	if (!planche->loadFromFile(chemin)) throw Erreur("Probleme lors du chargement de la texture.");
	this->initialiserTextures();
}

PlancheSprites::PlancheSprites(sf::Texture * planche, const unsigned & ratio) : planche(planche), ratioFenetre(ratio) {
	this->initialiserTextures();
}

bool PlancheSprites::initialiserTextures() {
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

	ratioSprite = ((float)ratioFenetre / (float)taille);

	// DEBUG
	// ratioSprite = 0.25f;

	chargerCreatures();
	chargerAretes();
	chargerSommet();
	return true;
}

bool PlancheSprites::chargerSommet() {
	chargerTexture(sommet, 12u, 0u);
	return true;
}

bool PlancheSprites::chargerAretes() {
	chargerTexture(areteH, 12u, 1u);
	chargerTexture(areteV, 12u, 3u);
	chargerTexture(areteSlash, 12u, 4u);
	chargerTexture(areteAntiSlash, 12u, 2u);
	return true;
}

bool PlancheSprites::chargerCreatures() {
	chargerTexture(pacman, 0u, 1u);
	chargerTexture(fantomeB, 6u, 5u);
	chargerTexture(fantomeJ, 6u, 1u);
	chargerTexture(fantomeR, 6u, 9u);
	chargerTexture(fantomeV, 6u, 13u);
	return true;
}

bool PlancheSprites::chargerTexture(sf::Sprite & texture, const unsigned & colonne, const unsigned & ligne) {
	texture.setTexture(*planche);
	texture.setTextureRect(sf::IntRect(colonne * taille, ligne * taille, taille, taille));
	texture.setOrigin((float)demiTaille, (float)demiTaille);
	texture.setScale(ratioSprite, ratioSprite);
	return true;
}