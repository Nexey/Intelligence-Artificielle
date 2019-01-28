#pragma once
#include "../ChargeurCOR.h"
#include <fstream>
#include <algorithm>

template<class T>
class ChargeurLabyrintheCOR :
	public ChargeurCOR<T> {
public:
	ChargeurLabyrintheCOR(GestionnaireChargement<T> * suivant = NULL) : ChargeurCOR<T>(suivant) { this->extension = "txt"; }

	std::vector<T> * construit(const std::string & chemin);

	virtual ~ChargeurLabyrintheCOR() {}
};

template<class T>
inline std::vector<T>* ChargeurLabyrintheCOR<T>::construit(const std::string & chemin) {
	std::ifstream fichierLaby(chemin);
	char elementsLabyrinthe[32][32];

	for (int i = 1; i < 31; i++) {
		for (int j = 2; j < 30; j++) {
			fichierLaby >> elementsLabyrinthe[i][j];
			if(elementsLabyrinthe[i][j] == '1' || elementsLabyrinthe[i][j] == '2')
				this->resultat->push_back(T(j, i));
		}
	}
	
	/*std::string labyStr(
		(std::istreambuf_iterator<char>(fichierLaby)),
		(std::istreambuf_iterator<char>()));
	labyStr.erase(remove(labyStr.begin(), labyStr.end(), ' '), labyStr.end());*/

	//std::cout << labyStr << std::endl;
	fichierLaby.close();
	return this->resultat;
}
