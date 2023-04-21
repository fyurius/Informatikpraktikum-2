/*
 * Losfahren.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Losfahren.h"

// Konstruktor
Losfahren::Losfahren(Fahrzeug& aFzg, Weg& wWeg)
	: Fahrausnahme(aFzg, wWeg)
{
}

// Angepasste geerbte Methode
void Losfahren::vBearbeiten()
{
	//Skript Seite 29 anpassen der Bearbeitungsfunktion durch pAbgabe()
	std::cout << "Das Fahrzeug " << p_aFahrzeug.getName() << " faehrt nun los auf dem Weg " << p_aWeg.getName() << std::endl;
	p_aWeg.vAnnahme(p_aWeg.pAbgabe(p_aFahrzeug));
}

