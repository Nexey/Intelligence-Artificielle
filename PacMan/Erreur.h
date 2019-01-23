/**
classe Erreur
*/
#pragma once

#include <string>
#include <iostream>
#include <exception>

	class Erreur : public std::exception {
	public:
		std::string message;
		Erreur() : message("Erreur !") {}
		Erreur(const std::string & messageErreur) : Erreur() { this->message += " " + messageErreur; }
		Erreur(const char * messageErreur) : Erreur((std::string)messageErreur) {}

		/**
		 * lance une exception si d est vide
		 * */

		inline static void testeNonVide(const void *d, const char * message);

		operator std::string() const { return this->message; }

		virtual const char* what() const noexcept { return ((std::string)(*this)).c_str(); }
	};

	inline std::ostream & operator << (std::ostream & os, const Erreur & erreur) { return os << (std::string)erreur; }

	/**
	 * lance une exception si d est vide
	 * */

	inline /*static*/ void Erreur::testeNonVide(const void *d, const char * message) {
#ifdef DEBUG
		if (!d) throw Erreur(message);
#endif
	}