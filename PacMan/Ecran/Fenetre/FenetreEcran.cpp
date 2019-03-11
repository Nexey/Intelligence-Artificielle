#include "FenetreEcran.h"
#include "Ecran/Formes/Creature.h"
#include "Graphe\Graphe.h"
#include "Exceptions/Erreur.h"
#include "./Experts/Chargement/Labyrinthe/ChargeurLabyrintheCOR.h"
#include <experimental\filesystem>

namespace fs = std::experimental::filesystem;

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
	sf::RenderWindow(sf::VideoMode(l, h), n, sf::Style::Titlebar),
	nom(n),
	largeur(l),
	hauteur(h),
	ratio(r),
	direction(VECTEUR2D_STOP),
	choixNiveau(0) {
	planche = new PlancheSprites("./Textures/Textures2.png", ratio);
	niveaux = new std::vector<Graphe<FormeEcran, FormeEcran>*>();
	Vecteur2D coinBGEcran(0, h), coinHDEcran(l, 0);
	transfoAffine = TransfoAffine2D::passageMondeEcran(coinBG, coinHD, coinBGEcran, coinHDEcran);


	// Initialisation des niveaux

	GestionnaireChargement<Graphe<FormeEcran, FormeEcran>> * expertChargementLabyrinthe;
	expertChargementLabyrinthe = new ChargeurLabyrintheCOR<Graphe<FormeEcran, FormeEcran>>(this);

	// Chargement de tous les niveaux
	Graphe<FormeEcran, FormeEcran> * niveau;
	for (fs::recursive_directory_iterator i("./Niveaux"), end; i != end; ++i)
		if (!is_directory(i->path())) {
			niveau = expertChargementLabyrinthe->charger(i->path().string());
			if (niveau != NULL) {
				niveaux->push_back(niveau);
				choixNiveau++;
			}
		}

}

const TransfoAffine2D & FenetreEcran::getTransfoAffine() const {
	return transfoAffine;
}

void FenetreEcran::redimensionner(const sf::Event & evenement) {
	sf::Vector2f sizef = static_cast<sf::Vector2f>(sf::Vector2u(evenement.size.width, evenement.size.height));
	sf::View GUIView(sf::Vector2f(sizef.x / 2, sizef.y / 2), sf::Vector2f(sizef.x, sizef.y));
	this->setView(GUIView);
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

void FenetreEcran::ajouterForme(Creature * c) {
	this->listeCreatureParNiveaux[choixNiveau].push_back(c);
}

const FenetreEcran * FenetreEcran::operator+(Creature * c) {
	this->ajouterForme(c);
	return this;
}

bool FenetreEcran::effectuer(fctTraitement traitement) {
	try {
		if (this->listeCreatureParNiveaux.count(choixNiveau) != 0) {
			std::vector<Creature *>::iterator it = this->listeCreatureParNiveaux.at(choixNiveau).begin();
			for (it; it < this->listeCreatureParNiveaux.at(choixNiveau).end(); it++)
				(this->*traitement)(*it);
		}
	}
	catch (Erreur e) {
#ifdef _DEBUG
		std::cerr << e.message << std::endl;
#endif
		return false;
	}
	return true;
}

//void FenetreEcran::onResize() {}

sf::Vector2f FenetreEcran::calculPos(const Vecteur2D & posEcran) {
	return TransfoVecteur2DToVector2f(transfoAffine.applique(posEcran));
}

FenetreEcran::~FenetreEcran() {}