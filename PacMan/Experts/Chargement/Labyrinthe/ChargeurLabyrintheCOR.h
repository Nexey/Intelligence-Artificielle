#pragma once
#include "../ChargeurCOR.h"
#include "../../Création/Sommet/SommetCOR.h"
#include <fstream>
#include <algorithm>

template<class T>
class ChargeurLabyrintheCOR :
	public ChargeurCOR<T> {
public:
	ChargeurLabyrintheCOR(FenetreEcran * fenetre, GestionnaireChargement<T> * suivant = NULL) : ChargeurCOR<T>(fenetre, suivant) { this->extension = "txt"; }

	std::vector<T> * construit(const std::string & chemin);

	virtual ~ChargeurLabyrintheCOR() {}
};

template<class T>
inline std::vector<T>* ChargeurLabyrintheCOR<T>::construit(const std::string & chemin) {
	GestionnaireCreation * expertCreation = new SommetCOR(this->fenetre);
	
	std::ifstream fichierLaby(chemin);
	char elementsLabyrinthe[32][32];

	FormeEcran * forme;

	for (int i = 31; i >= 0; i--) {
		for (int j = 31; j >= 0; j--) {
			fichierLaby >> elementsLabyrinthe[i][j];
			forme = expertCreation->gerer(elementsLabyrinthe[i][j], Vecteur2D(j, i));
			if (forme != nullptr)
				this->resultat->push_back(*forme);
		}
	}
	
	/*std::string labyStr(
		(std::istreambuf_iterator<char>(fichierLaby)),
		(std::istreambuf_iterator<char>()));
	labyStr.erase(remove(labyStr.begin(), labyStr.end(), ' '), labyStr.end());*/
	
	fichierLaby.close();
	return this->resultat;
}
