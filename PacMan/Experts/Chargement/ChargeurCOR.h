#pragma once
#include "GestionnaireChargement.h"
#include "./Ecran/Fenetre/FenetreEcran.h"

template<class T>
class ChargeurCOR :
	public GestionnaireChargement<T> {
	GestionnaireChargement<T> * suivant;
protected:
	std::string extension;
	T * resultat;

	FenetreEcran * fenetre;
public:
	ChargeurCOR(FenetreEcran * fenetre, const std::string & extension, GestionnaireChargement<T> * suivant = NULL) : fenetre(fenetre), suivant(suivant), extension(extension) {}

	virtual ~ChargeurCOR() {}
	
	virtual T * construit(const std::string & chemin) = 0;

	const bool peutCharger(const std::string&) const;
	T * charger(const std::string&);
};

template<class T>
inline const bool ChargeurCOR<T>::peutCharger(const std::string & chemin) const {
	return chemin.substr(chemin.find_last_of(".") + 1) == extension;
}

template<class T>
inline T * ChargeurCOR<T>::charger(const std::string & chemin) {
	if (peutCharger(chemin))
		return construit(chemin);

	if (suivant != NULL)
		return suivant->charger(chemin);

	return NULL;
}