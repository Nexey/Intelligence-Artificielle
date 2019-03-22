#include "FormeEcran.h"
#include "../../Exceptions/Erreur.h"

FormeEcran::FormeEcran(sf::Sprite * texture, FenetreEcran * fenetre, const Vecteur2D & p) : texture(new sf::Sprite(*texture)), fenetre(fenetre), positionEcran(p) {
	this->miseAJourPositionTexture(positionEcran);
}

FormeEcran::FormeEcran(const FormeEcran & f) : texture(new sf::Sprite(*f.texture)), fenetre(f.fenetre), positionEcran(f.positionEcran) {}

void FormeEcran::miseAJourPositionEcran(const Vecteur2D & nouvPos) {
	this->positionEcran = nouvPos;
}

void FormeEcran::miseAJourPositionTexture(const Vecteur2D & nouvPos) {
	this->texture->setPosition(fenetre->calculPos(nouvPos));
}

const bool FormeEcran::dessiner() {
	try {
		fenetre->draw(*texture);
	}
	catch (Erreur e) {
#ifdef _DEBUG
		std::cerr << e.message << std::endl;
#endif
		return false;
	}
	return true;
}

FenetreEcran * FormeEcran::getFenetre() const {
	return fenetre;
}

const Vecteur2D FormeEcran::getPositionEcran() const {
	return positionEcran;
}

FormeEcran::operator std::string() const {
	std::stringstream ss;
	ss << "Position écran : " << positionEcran << std::endl;
	ss << "Position réelle : " << texture->getPosition().x << ", " << texture->getPosition().y << std::endl;
	return ss.str();
}

FormeEcran::~FormeEcran() {}

std::ostream & operator<<(std::ostream &o, const FormeEcran &f) {
	return o << (std::string)f;
}
