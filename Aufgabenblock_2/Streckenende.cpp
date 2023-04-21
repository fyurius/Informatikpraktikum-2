/*
 * Streckenende.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Streckenende.h"


// Konstruktor
Streckenende::Streckenende(Fahrzeug& aFzg, Weg& wWeg)
	: Fahrausnahme(aFzg, wWeg)
{
}

// Angepasst
void Streckenende::vBearbeiten()
{
	std::cout << "Das Fahrzeug " << p_aFahrzeug.getName() << " hat das Ende des Weges " << p_aWeg.getName() << " erreicht." << std::endl;
	std::unique_ptr<Fahrzeug> pFahrzeug = p_aWeg.pAbgabe(p_aFahrzeug);
	p_aWeg.vAnnahme(move(pFahrzeug));
}
