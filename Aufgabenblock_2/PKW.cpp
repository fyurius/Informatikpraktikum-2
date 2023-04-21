/*
 * PKW.cpp
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */

#include "PKW.h"
#include "Verhalten.h"
#include "SimuClient.h"

// Fahrzeug Konstruktor an PKW angepasst
PKW::PKW(std::string sName, double sMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen)
	: Fahrzeug(sName, sMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen),
	  p_dTankinhalt(dTankvolumen/2)
{
}

// Fahrzeug Methode ueberladen um PKW betanken zu koennen
double PKW::dTanken(double dMenge)
{
    double dMaxTankbar = p_dTankvolumen - p_dTankinhalt;	// Variable fuer tatsaechlich getankte Menge

    if(dMenge < dMaxTankbar)	// Tankvolumen nicht ueberschritten
    {
        p_dTankinhalt += dMenge;
    }
    else if(dMenge + p_dTankinhalt > dMaxTankbar)	// Tankvolumen ueberschritten
    {
        p_dTankinhalt = dMaxTankbar + p_dTankinhalt;
        std::cout<<"Es wurde getankt"<<std::endl;
    }

    return dMenge;
}

double PKW::dGeschwindigkeit() const
{

	if (this->p_dMaxGeschwindigkeit > this->p_pVerhalten->getTempolimitWeg())	// Wenn die Geschwindigkeit des Autos groeßer ist als erlaubt
	{
		return this->p_pVerhalten->getTempolimitWeg();		// Anpassung der Geschwindigkeit
	}
	return this->p_dMaxGeschwindigkeit;		// Sonst darf das Auto so schnell fahren wie es kann
}

// Getter fuer Tankinhalt
double PKW::dGetTankinhalt() const
{
	return p_dTankinhalt;
}

// PKWs haben besondere Parameter waehrend der Simulation
void PKW::vSimulieren()
{
    // Überprüft ob Tank leer ist
    if(p_dTankinhalt > 0)
    {
    	double dTempGesamtStrecke = p_dGesamtStrecke;

    	// Aufruf der Methode zur Fahrzeugsimulation
    	Fahrzeug::vSimulieren();

        // Berechnet Verbrauch im nächsten Simulationsschritt
        double dVerbrauchteMenge = (p_dGesamtStrecke - dTempGesamtStrecke) * p_dVerbrauch / 100;
        // Aktualisiert Tankinhalt
        p_dTankinhalt -= dVerbrauchteMenge;
        // Keine negativen Tankinhalte zulassen
        if(p_dTankinhalt < 0)
        {
            p_dTankinhalt = 0;
        }

    }
    else
    {
        p_dTankinhalt = 0;
        // Letzte Simulationszeit wird angepasst
        p_dZeit = dGlobaleZeit;
        // Gesamte siumlierte Zeit des Objekts wird aktualisiert
        p_dGesamtZeit += (dGlobaleZeit-p_dGesamtZeit);
    }
}


// Ausgabe muss beim PKW auch Verbrauch beinhalten
void PKW::vAusgeben(std::ostream& o) const
{
    Fahrzeug::vAusgeben(o);
    o << std::setw(20) << p_dVerbrauch * p_dGesamtStrecke/100 << std::setw(25) << p_dTankinhalt;
}

// Zeichen - Methode fuer die Simulation
void PKW::vZeichnen(const Weg& wWeg) const
{
	//std::cout << "Wurde gezeichnet" << std::endl;		// Nur zum testen

	bZeichnePKW(this->getName(), wWeg.getName(), this->p_dAbschnittStrecke / wWeg.getLaenge(), dGeschwindigkeit(), this->p_dTankinhalt); // Abschnitt/Gesamt wird rel. Strecke
}


// Ueberladen muss beim PKW die klasseneigenen Parameter beruecksichtigen
PKW& PKW::operator=(const PKW& vehicle3)
{
	p_dTankvolumen = vehicle3.p_dTankvolumen;
	p_dTankinhalt = vehicle3.p_dTankinhalt;
	p_dVerbrauch = vehicle3.p_dVerbrauch;
	p_dGesamtStrecke = 0;
	p_dZeit = 0;
	p_dGesamtZeit = 0;
	Fahrzeug::operator = (vehicle3);

	return *this;
}

// Destruktor, nicht unbedingt noetig
PKW::~PKW() {
}
