#pragma once
#include "GestionnaireChargement.h"

template<class T>
class ChargeurCOR :
	public GestionnaireChargement<T> {
	GestionnaireChargement<T> * suivant;
protected:
	std::string extension;
	std::vector<T> * resultat;
public:
	ChargeurCOR(GestionnaireChargement<T> * suivant = NULL) : suivant(suivant) {
		resultat = new std::vector<T>();
	}

	virtual ~ChargeurCOR() {}
	
	virtual std::vector<T> * construit(const std::string & chemin) = 0;

	const bool peutCharger(const std::string&) const;
	std::vector<T> * charger(const std::string&);
};

template<class T>
inline const bool ChargeurCOR<T>::peutCharger(const std::string & chemin) const {
	return chemin.substr(chemin.find_last_of(".") + 1) == extension;
}

template<class T>
inline std::vector<T>* ChargeurCOR<T>::charger(const std::string & chemin) {
	if (peutCharger(chemin))
		return construit(chemin);

	if (suivant != NULL)
		return suivant->charger(chemin);

	return NULL;
}