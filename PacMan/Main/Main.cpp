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

	const unsigned ratio = 8u;
	Vecteur2D CoinBasGauche(0, 0), CoinHautDroit(31, 31);
	FenetreEcran fenetre("PacMan", 32*ratio*2, 32*ratio*2, CoinBasGauche, CoinHautDroit, ratio);

	// Experts d'évènements
	GestionnaireEvenement * experts =
		new DeplacementToucheCOR(&fenetre,
			new FermetureToucheCOR(&fenetre,
				new RedimensionCOR(&fenetre,
					new FermetureCOR(&fenetre)
				)
			)
		);

	fenetre.choixNiveau = 0;
	fenetre.niveaux->at(fenetre.choixNiveau)->dessine<FenetreEcran>(fenetre);

	sf::Texture niveauImg;
	niveauImg.create(fenetre.getLargeur(), fenetre.getHauteur());
	niveauImg.update(fenetre);

	//	Sauvegarde l'image générée sur le disque :
	//	std::string chemin = "C:\\Users\\geels\\Documents\\GitHub\\C++\\Intelligence Artificielle\\Niveau.png";
	//	niveauImg.copyToImage().saveToFile(chemin);

	sf::Sprite niveauSpr(niveauImg);
	fenetre.clear();

	while (fenetre.isOpen()) {
		sf::Event event;
		while (fenetre.pollEvent(event)) {
			experts->gerer(event);
		}

		fenetre.clear();
		fenetre.draw(niveauSpr);

		fenetre.effectuer(&FenetreEcran::deplacer);
		fenetre.effectuer(&FenetreEcran::dessiner);

		fenetre.display();
	}
	return 0;
}