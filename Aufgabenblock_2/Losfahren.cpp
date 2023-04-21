/*
 * Losfahren.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Losfahren.h"

extern double dGlobaleZeit;

// Konstruktor
Losfahren::Losfahren(Fahrzeug& aFzg, Weg& wWeg)
	: Fahrausnahme(aFzg, wWeg)
{
}

// Angepasste geerbte Methode
void Losfahren::vBearbeiten()
{
	std::cout << "Das Fahrzeug " << p_aFahrzeug.getName() << " faehrt nun los auf dem Weg " << p_aWeg.getName() << std::endl;
	p_aFahrzeug.vNeueStrecke(p_aWeg);

}

