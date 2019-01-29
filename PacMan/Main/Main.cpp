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
	const unsigned ratio = 6u;

	Vecteur2D
		CoinBasGauche(0, 0),
		CoinHautDroit(31, 31);

	FenetreEcran fenetre("PacMan", 32*ratio*2, 32*ratio*2, CoinBasGauche, CoinHautDroit, ratio);

	Graphe<FormeEcran, FormeEcran> graphe;

	GestionnaireChargement<FormeEcran> * expertChargement;
	expertChargement = new ChargeurLabyrintheCOR<FormeEcran>(&fenetre);

	std::vector<FormeEcran> test = *expertChargement->charger("./Labyrinthe.txt");

	std::vector<FormeEcran>::iterator it = test.begin();
	for (it; it < test.end(); it++)
		graphe.creeSommet(*it);

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
		graphe.dessineTousSommets<FenetreEcran>(fenetre);

		fenetre.effectuer(&FenetreEcran::deplacer);
		fenetre.effectuer(&FenetreEcran::dessine);
		fenetre.display();
	}
#ifdef _DEBUG
	//system("pause");
#endif
	return 0;
}