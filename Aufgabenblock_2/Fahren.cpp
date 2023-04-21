/*
 * Fahren.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

// Ruft Konstruktor der Vaterklasse auf
Fahren::Fahren(Weg& wWeg)
	: Verhalten::Verhalten(wWeg)
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitintervall)
{
	double dVerbleibendeStrecke = p_wParameterWeg.getLaenge() - aFzg.getAbschnittStrecke();

	std::cout << "Strecke: "<< dVerbleibendeStrecke << " Von: " << aFzg.getName() << std::endl;		// Nur zum Test

	if(dVerbleibendeStrecke <= 0.000001)		// Ein kleiner Fehler wird zugelassen (Epsilon Genauigkeit)
	{
		throw Streckenende(aFzg, p_wParameterWeg); // Ausnahme, wenn Weg zuende
	}
	dVerbleibendeStrecke = dVerbleibendeStrecke < aFzg.dGeschwindigkeit() * dZeitintervall ? dVerbleibendeStrecke : aFzg.dGeschwindigkeit() * dZeitintervall;
	// Wenn die verbleibende Strecke kleiner ist als die berechnete, so wird diese zurückgegeben, wenn sie größer ist die berechnete

	return dVerbleibendeStrecke;
}
