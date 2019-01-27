#include "FenetreEcran.h"
#include "../Formes/Creature.h"
#include "../../Exceptions/Erreur.h"

const Vecteur2D
FenetreEcran::VECTEUR2D_BAS_GAUCHE(-1, -1),
FenetreEcran::VECTEUR2D_BAS(0, -1),
FenetreEcran::VECTEUR2D_BAS_DROITE(1, -1),
FenetreEcran::VECTEUR2D_GAUCHE(-1, 0),
FenetreEcran::VECTEUR2D_DROITE(1, 0),
FenetreEcran::VECTEUR2D_HAUT_GAUCHE(-1, 1),
FenetreEcran::VECTEUR2D_HAUT(0, 1),
FenetreEcran::VECTEUR2D_HAUT_DROITE(1, 1),
FenetreEcran::VECTEUR2D_STOP(0, 0);

FenetreEcran::FenetreEcran(const std::string & n, const unsigned & l, const unsigned & h, const Vecteur2D & coinBG, const Vecteur2D & coinHD, const unsigned & r) :
	sf::RenderWindow(sf::VideoMode(l, h), n),
	nom(n),
	largeur(l),
	hauteur(h),
	ratio(r),
	direction(VECTEUR2D_STOP) {
	Vecteur2D coinBGEcran(0, h), coinHDEcran(l, 0);
	transfoAffine = TransfoAffine2D::passageMondeEcran(coinBG, coinHD, coinBGEcran, coinHDEcran);
}

const TransfoAffine2D & FenetreEcran::getTransfoAffine() const {
	return transfoAffine;
}

void FenetreEcran::redimensionner() {
	sf::IntRect viewPort = this->getViewport(this->getView());
	viewPort.height = viewPort.height / this->getSize().y;
	viewPort.width = viewPort.width / this->getSize().x;
	std::cout << viewPort.width << ", " << viewPort.height << std::endl;
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

void FenetreEcran::ajouterForme(Creature & c) {
	this->listeCreature.push_back(c);
}

const FenetreEcran * FenetreEcran::operator+(Creature & c) {
	this->ajouterForme(c);
	return this;
}

bool FenetreEcran::effectuer(fctTraitement traitement) {
	try {
		std::vector<Creature>::iterator it = this->listeCreature.begin();
		for (it; it < this->listeCreature.end(); it++)
			(this->*traitement)(*it);
	}
	catch (Erreur e) {
#ifdef _DEBUG
		std::cerr << e.message << std::endl;
#endif
		return false;
	}
	return true;
}

sf::Vector2f FenetreEcran::calculPos(const Vecteur2D & posEcran) {
	return TransfoVecteur2DToVector2f(transfoAffine.applique(posEcran));
}

FenetreEcran::~FenetreEcran() {}