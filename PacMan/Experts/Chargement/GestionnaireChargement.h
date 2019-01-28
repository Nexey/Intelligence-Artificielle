#pragma once
#include <vector>
#include "../../Exceptions/Erreur.h"

template<class T>
class GestionnaireChargement {
public:
	virtual std::vector<T> * charger(const std::string&) = 0;
};