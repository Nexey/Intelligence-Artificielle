#include <vector>
#include "./Ecran/Formes/PacMan.h"

#include "./Experts/Évènements/Redimension/RedimensionCOR.h"
#include "./Experts/Évènements/Fermeture/FermetureCOR.h"
#include "./Experts/Évènements/Touches/Fermeture/FermetureToucheCOR.h"
#include "./Experts/Évènements/Touches/Déplacement/DeplacementToucheCOR.h"
#include "./Graphe/Graphe.h"
#include "./Graphe/Liste.h"
#include <Windows.h> // Pour les accents dans la console sous Windows


int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows

	const unsigned ratio = 32u,
		longueur = 512,
		largeur = 512;
	Vecteur2D CoinBasGauche(0, 0), CoinHautDroit(ratio - 1, ratio - 1);
	FenetreEcran fenetre("PacMan", largeur, longueur, CoinBasGauche, CoinHautDroit, ratio);

	// Experts d'évènements
	GestionnaireEvenement * experts =
		new DeplacementToucheCOR(&fenetre,
			new FermetureToucheCOR(&fenetre,
				new RedimensionCOR(&fenetre,
					new FermetureCOR(&fenetre)
				)
			)
		);

	fenetre.choixNiveau = 3;
	fenetre.niveaux->at(fenetre.choixNiveau)->dessine<FenetreEcran>(fenetre);

	// std::cout << *fenetre.niveaux->at(fenetre.choixNiveau) << std::endl;

	sf::Texture niveauImg;
	niveauImg.create(fenetre.getLargeur(), fenetre.getHauteur());
	niveauImg.update(fenetre);

	//	Sauvegarde l'image générée sur le disque :
	//	std::string chemin = "C:\\Users\\geels\\Documents\\GitHub\\C++\\Intelligence Artificielle\\Niveau.png";
	//	niveauImg.copyToImage().saveToFile(chemin);

	sf::Sprite niveauSpr(niveauImg);
	fenetre.clear();

	sf::Clock horlogeDeplacement;
	sf::Time tempsDeplacement = sf::milliseconds(4);

	sf::Event event;
	while (fenetre.isOpen()) {
		while (fenetre.pollEvent(event))
			experts->gerer(event);

		fenetre.clear();
		fenetre.draw(niveauSpr);

		if (fenetre.direction != FenetreEcran::VECTEUR2D_STOP)
			if (horlogeDeplacement.getElapsedTime() >= tempsDeplacement) {
				horlogeDeplacement.restart();
				fenetre.effectuer(&FenetreEcran::deplacer);
			}
		fenetre.effectuer(&FenetreEcran::dessiner);

		fenetre.display();
	}
	return 0;
}