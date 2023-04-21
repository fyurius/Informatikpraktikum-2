/*
 * Verhalten.cpp
 *
 *  Created on: 16.11.2022
 *      Author: finle
 */

#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"


// Konstruktor
Verhalten::Verhalten(Weg &wParamWeg)
	: p_wParameterWeg(wParamWeg)
{
}

// Bekommt spaeter Funktionalitaet
double Verhalten::dStrecke(Fahrzeug& aFzg,double dZeitintervall)
{
}

// Getter fuer Tempolimit
double Verhalten::getTempolimitWeg()
{
	return p_wParameterWeg.getTempolimit();
}
