/*
 * Fahrrad.cpp
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */

#include "Fahrrad.h"
#include "Simuclient.h"

// Konstruktor fuer Fahrraeder
Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit)
	: Fahrzeug(sName, dMaxGeschwindigkeit)
{
}

//Funktion um reale Geschwindigkeit darzustellen
double Fahrrad::dGeschwindigkeit() const
{
    int i20kmAbschnitte = (int)(p_dGesamtStrecke / 20);	// 20Km Marke
    double dSpeed = pow(0.9, i20kmAbschnitte) * p_dMaxGeschwindigkeit;		// Geschwindigkeitsanpassung

    if(dSpeed < 12)		// Minimum muss aufrecht erhalten werden
    {
        dSpeed = 12;
    }
    return dSpeed;

}

void Fahrrad::vAusgeben(std::ostream& o) const		// Ueberladene Ausagbe
{
    Fahrzeug::vAusgeben(o);
}

void Fahrrad::vZeichnen(const Weg& wWeg) const		// Zeichenfunktion fuer Darstellung in der Simulation
{
	bZeichneFahrrad(this->getName(), wWeg.getName(), this->p_dAbschnittStrecke / wWeg.getLaenge() , dGeschwindigkeit());
}

Fahrrad& Fahrrad::operator=(const Fahrrad& vehicle3)	// Da der Copy - Konstruktor geloescht ist, erfolgt hier eine Zuweisung, welche
{														// ID - Fehler verhindert
	p_dGesamtStrecke = 0;
	p_dZeit = 0;
	p_dGesamtZeit = 0;
	Fahrzeug::operator = (vehicle3);

	return *this;

}
