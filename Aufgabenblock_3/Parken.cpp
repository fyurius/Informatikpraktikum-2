/*
 * Parken.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"
#include "Weg.h"

extern double dGlobaleZeit;		// Wird fuer Abgleich mit Startzeit gebraucht

// Konstruktor
Parken::Parken(Weg& wWeg, double dStartzeitpunkt)
	: Verhalten::Verhalten(wWeg), p_dStartzeitpunkt(dStartzeitpunkt)
{
}


// An Parken angepasste vererbte Methode
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if(p_dStartzeitpunkt < dGlobaleZeit+0.000001)
	{
		std::cout << "Startzeit: " << p_dStartzeitpunkt << " Aktuelle Zeit: " << dGlobaleZeit << std::endl;
		throw Losfahren(aFzg, p_wParameterWeg);		// Wurf der Ausnahme bei Beginn der Fahrt
	}

	return 0.0; // Wenn es noch parkt wird 0.0 zurueckgegeben
}
