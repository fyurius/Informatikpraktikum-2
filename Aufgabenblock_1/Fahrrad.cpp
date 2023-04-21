/*
 * Fahrrad.cpp
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */

#include "Fahrrad.h"
#include <cmath>

// Konstruktor fuer Fahrraeder
Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit)
	: Fahrzeug(sName, dMaxGeschwindigkeit)
{
}

//Funktion um reale Geschwindigkeit darzustellen
double Fahrrad::dGeschwindigkeit() const
{

	/*
	if (p_dGesamtStrecke >= 20)
	{
		double dspeed = std::pow(0.9, (int)p_dGesamtStrecke / 20); //aktuelle Geschwindigkeit = geschwindigkeit * (0,9)^(Gesamtstrecke/20km)
		if (dspeed >= 12)
		{
			return dspeed;
		}

		// Minimum von 12 kmh muss aufrechtgehalten werden
		else
		{
			return 12;
		}
	}

	// Es wurden noch keine 20 Km gefahren
	else
	{
		return p_dMaxGeschwindigkeit;
	}
	*/

    int i20kmAbschnitte = (int)(p_dGesamtStrecke / 20);

    double dSpeed = pow(0.9, i20kmAbschnitte) * p_dMaxGeschwindigkeit;

    if(dSpeed < 12)
    {
        dSpeed = 12;
    }
    return dSpeed;

}

Fahrrad& Fahrrad::operator=(const Fahrrad& vehicle3)
{
	p_dGesamtStrecke = 0;
	p_dZeit = 0;
	p_dGesamtZeit = 0;
	Fahrzeug::operator = (vehicle3);

	return *this;

}
