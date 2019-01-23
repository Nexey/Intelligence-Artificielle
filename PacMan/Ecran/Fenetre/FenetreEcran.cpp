#include "FenetreEcran.h"

FenetreEcran::FenetreEcran(const std::string & n, const unsigned & l, const unsigned & h, const Vecteur2D & coinBG, const Vecteur2D & coinHD, const unsigned & r) :
	sf::RenderWindow(sf::VideoMode(l, h), n),
	nom(n),
	largeur(l),
	hauteur(h),
	ratio(r) {
	Vecteur2D coinBGEcran(0, h), coinHDEcran(l, 0);
	transfoAffine = TransfoAffine2D::passageMondeEcran(coinBG, coinHD, coinBGEcran, coinHDEcran);
}
/*/
FenetreEcran::FenetreEcran(const FenetreEcran & f) :
	sf::RenderWindow(sf::VideoMode(f.getLargeur(), f.getHauteur()), f.getNom()),
	nom(f.getNom()),
	largeur(f.getLargeur()),
	hauteur(f.getHauteur()),
	ratio(f.getRatio()),
	transfoAffine(f.getTransfoAffine()) {}
	*/

const TransfoAffine2D & FenetreEcran::getTransfoAffine() const {
	return transfoAffine;
}

void FenetreEcran::redimensionner() {
	sf::IntRect viewPort = this->getViewport(this->getView());
	viewPort.height = viewPort.height / this->getSize().y;
	viewPort.width = viewPort.width / this->getSize().x;
}

const unsigned & FenetreEcran::getRatio() const {
	return ratio;
}

const unsigned & FenetreEcran::getLargeur() const {
	return largeur;
}

const unsigned & FenetreEcran::getHauteur() const {
	return hauteur;
}

const std::string & FenetreEcran::getNom() const {
	return nom;
}

const Vecteur2D & FenetreEcran::getCoinBasGauche() const {
	return coinBasGauche;
}

const Vecteur2D & FenetreEcran::getCoinHautDroit() const {
	return coinHautDroit;
}

sf::Vector2f FenetreEcran::calculPos(const Vecteur2D & posEcran) {
	return TransfoVecteur2DToVector2f(transfoAffine.applique(posEcran));
}