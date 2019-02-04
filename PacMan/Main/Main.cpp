#include <vector>
#include "../Ecran/Formes/Creature.h"
#include "../Experts/Évènements/Redimension/RedimensionCOR.h"
#include "../Experts/Évènements/Fermeture/FermetureCOR.h"
#include "../Experts/Évènements/Touches/Fermeture/FermetureToucheCOR.h"
#include "../Experts/Évènements/Touches/Déplacement/DeplacementToucheCOR.h"
#include "../Graphe/Graphe.h"
#include "../Graphe/Liste.h"
#include "../Experts/Chargement/Labyrinthe/ChargeurLabyrintheCOR.h"
#include <Windows.h> // Pour les accents dans la console sous Windows

int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows
	const unsigned ratio = 8u;

	Vecteur2D
		CoinBasGauche(0, 0),
		CoinHautDroit(31, 31);

	FenetreEcran fenetre("PacMan", 32*ratio*2, 32*ratio*2, CoinBasGauche, CoinHautDroit, ratio);

	Graphe<FormeEcran, FormeEcran> graphe;

	GestionnaireChargement<FormeEcran> * expertChargement;
	expertChargement = new ChargeurLabyrintheCOR<FormeEcran>(&fenetre);

	std::vector<FormeEcran> test = *expertChargement->charger("./Niveaux/1/Labyrinthe.txt");

	std::vector<FormeEcran>::const_iterator it = test.begin();
	for (it; it < test.end(); it++)
		graphe.creeSommet(*it);

	sf::Shape * rectangleSFML;


	Iterateur<Sommet<FormeEcran>> iterateurListeTemp = graphe.listeSommets.getIterateur();
	Iterateur<Sommet<FormeEcran>> iterateurSommetGraphe = graphe.listeSommets.getIterateur();

	Sommet<FormeEcran> * teteListeSommets;
	Sommet<FormeEcran> * teteListeTemp;

	while (iterateurSommetGraphe.aSuivant()) {
		teteListeSommets = iterateurSommetGraphe.suivant();
		while (iterateurListeTemp.aSuivant()) {
			teteListeTemp = iterateurListeTemp.suivant();
			if (teteListeTemp != teteListeSommets) {
				Vecteur2D
					posTeteListeSommets = teteListeSommets->valeur.getPositionEcran(),
					posTeteListeTemp = teteListeTemp->valeur.getPositionEcran();
				if (
					(posTeteListeSommets + FenetreEcran::VECTEUR2D_BAS		== posTeteListeTemp) ||
					(posTeteListeSommets + FenetreEcran::VECTEUR2D_DROITE	== posTeteListeTemp)
					) {
					rectangleSFML = new sf::RectangleShape(sf::Vector2f(8.f, 8.f));
					rectangleSFML->setFillColor(sf::Color::Green);
					graphe.creeArete(FormeEcran(rectangleSFML, &fenetre, (posTeteListeSommets + posTeteListeTemp) * 0.5), teteListeSommets, teteListeTemp);
				}
			}
		}
		iterateurListeTemp.debut();
	}

	Creature rectangle(new sf::RectangleShape(sf::Vector2f(ratio, ratio)), &fenetre, Vecteur2D(4, 4));
	rectangle.formeSFML->setFillColor(sf::Color::Red);
	rectangle.formeSFML->setOutlineColor(sf::Color::Green);
	rectangle.formeSFML->setOutlineThickness(2.f);
	fenetre.ajouterForme(rectangle);

	GestionnaireEvenement * experts =
		new DeplacementToucheCOR(&fenetre,
			new FermetureToucheCOR(&fenetre,
				new RedimensionCOR(&fenetre,
					new FermetureCOR(&fenetre))));

	while (fenetre.isOpen()) {
		sf::Event event;
		while (fenetre.pollEvent(event)) {
			experts->gerer(event);
		}

		fenetre.clear();
		graphe.dessine<FenetreEcran>(fenetre);

		fenetre.effectuer(&FenetreEcran::deplacer);
		fenetre.effectuer(&FenetreEcran::dessine);
		fenetre.display();
	}
#ifdef _DEBUG
	//system("pause");
#endif
	return 0;
}