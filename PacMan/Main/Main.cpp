#include <vector>
#include "./Ecran/Formes/Creature.h"
#include "./Experts/Évènements/Redimension/RedimensionCOR.h"
#include "./Experts/Évènements/Fermeture/FermetureCOR.h"
#include "./Experts/Évènements/Touches/Fermeture/FermetureToucheCOR.h"
#include "./Experts/Évènements/Touches/Déplacement/DeplacementToucheCOR.h"
#include "./Graphe/Graphe.h"
#include "./Graphe/Liste.h"
#include "./Experts/Chargement/Labyrinthe/ChargeurLabyrintheCOR.h"
#include <Windows.h> // Pour les accents dans la console sous Windows
#include <experimental\filesystem>

namespace fs = std::experimental::filesystem;

int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows

	const unsigned ratio = 8u;
	Vecteur2D CoinBasGauche(0, 0), CoinHautDroit(31, 31);
	FenetreEcran fenetre("PacMan", 32*ratio*2, 32*ratio*2, CoinBasGauche, CoinHautDroit, ratio);

	GestionnaireChargement<Graphe<FormeEcran, FormeEcran>> * expertChargementLabyrinthe;
	expertChargementLabyrinthe = new ChargeurLabyrintheCOR<Graphe<FormeEcran, FormeEcran>>(&fenetre);

	std::vector<Graphe<FormeEcran, FormeEcran>*> niveaux;

	// Chargement de tous les niveaux
	Graphe<FormeEcran, FormeEcran> * niveau;
	for (fs::recursive_directory_iterator i("./Niveaux"), end; i != end; ++i)
		if (!is_directory(i->path())) {
			niveau = expertChargementLabyrinthe->charger(i->path().string());
			if (niveau != NULL)
				niveaux.push_back(niveau);
		}
	int choixNiveau = 0;

//	std::cout << *niveaux.at(0);

	//Creature rectangle(new sf::RectangleShape(sf::Vector2f(ratio, ratio)), &fenetre, Vecteur2D(5, 5));
	//rectangle.formeSFML->setFillColor(sf::Color::Red);
	//rectangle.formeSFML->setOutlineColor(sf::Color::Green);
	//rectangle.formeSFML->setOutlineThickness(2.f);
	//fenetre.ajouterForme(rectangle);


	Creature rectangle(new sf::RectangleShape(sf::Vector2f(ratio, ratio)), &fenetre, niveaux.at(choixNiveau)->listeSommets.tete->valeur, niveaux.at(0));
	rectangle.formeSFML->setFillColor(sf::Color::Red);
	rectangle.formeSFML->setOutlineColor(sf::Color::White);
	rectangle.formeSFML->setOutlineThickness(2.f);

	// Experts d'évènements
	GestionnaireEvenement * experts =
		new DeplacementToucheCOR(&fenetre,
			new FermetureToucheCOR(&fenetre,
				new RedimensionCOR(&fenetre,
					new FermetureCOR(&fenetre)
				)
			)
		);

	niveaux.at(choixNiveau)->dessine<FenetreEcran>(fenetre);

	sf::Texture niveauImg;
	niveauImg.create(fenetre.getLargeur(), fenetre.getHauteur());
	niveauImg.update(fenetre);

	//	Sauvegarde l'image générée sur le disque :
	//	std::string chemin = "C:\\Users\\geels\\Documents\\GitHub\\C++\\Intelligence Artificielle\\Niveau.png";
	//	niveauImg.copyToImage().saveToFile(chemin);


	//std::cout << *niveaux.at(0);
	/*
	Liste<Sommet<FormeEcran>> * voisins = niveaux.at(0)->voisins(rectangle.positionSommet);
	Iterateur<Sommet<FormeEcran>> it = voisins->getIterateur();

	while (it.aSuivant())
		std::cout << *it.suivant();*/

	sf::Sprite niveauSpr(niveauImg);
	fenetre.clear();

	while (fenetre.isOpen()) {
		sf::Event event;
		while (fenetre.pollEvent(event)) {
			experts->gerer(event);
		}

		fenetre.clear();
		fenetre.draw(niveauSpr);

		rectangle.deplacer();
		fenetre.draw(*rectangle.formeSFML);

		//fenetre.effectuer(&FenetreEcran::deplacer);
		//fenetre.effectuer(&FenetreEcran::dessine);
		fenetre.display();
	}
	return 0;
}