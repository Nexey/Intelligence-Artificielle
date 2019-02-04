#pragma once
#include <vector>
#include "./Exceptions/Erreur.h"

template<class T>
class GestionnaireChargement {
public:
	virtual T * charger(const std::string&) = 0;
};