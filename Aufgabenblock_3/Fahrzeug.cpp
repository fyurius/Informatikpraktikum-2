/*
 * Fahrzeug.cpp
 *
 *  Created on: 18.10.2022
 *      Author: finle
 */

#include "Fahrzeug.h"
#include "Weg.h"
#include "Verhalten.h"
#include "Parken.h"
#include "Fahren.h"
#include "Fahrausnahme.h"
#include "Streckenende.h"
#include "Losfahren.h"

//Einfacherer Konstruktor (Nicht mehr wirklich genutzt)
Fahrzeug::Fahrzeug()
	:Simulationsobjekt(""), p_dMaxGeschwindigkeit(0)
{
	std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde mit dem 2. Konstruktor erzeugt" << std::endl;
	std::cout << "" << std::endl;
}

// Recht einfacher Konstruktor mit Namen Pararmeter
Fahrzeug::Fahrzeug(std::string sParameterName) :
	Simulationsobjekt(sParameterName)
{
	std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde mit dem 1. Konstruktor erzeugt" << std::endl;
	std::cout << "" << std::endl;
}

//Konstruktor, mit Aufruf der Oberklasse (Am meisten genutzt)
Fahrzeug::Fahrzeug(std::string sParameterName, double sMaxGeschwindigkeit)
	: Simulationsobjekt(sParameterName),
	  p_dMaxGeschwindigkeit((sMaxGeschwindigkeit > 0) ? sMaxGeschwindigkeit:(sMaxGeschwindigkeit*-1)) // Nicht negativ
{
	//std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde erzeugt"<< std::endl; // Nur zum testen
	//std::cout << "" << std::endl;
}

// Dekonstruktor
Fahrzeug::~Fahrzeug()
{
}


// Beschriftet Tabelle korrekt
void Fahrzeug::vKopf()
{
	//std::cout<<"test in fahrzeug kopf"<<std::endl;
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(10) << "ID" << std::setw(20) << "Name" << std::setw(30) << "MaxGeschwindigkeit (km/h)" << std::setw(25) << "Gesamtstrecke [km/h]" << std::setw(35) << "akt. Geschwindigkeit [km]" << std::setw(25) << "Gesamtverbrauch [l]" << std::setw(25) << "akt. Tankinhalt [l]" << std::endl;
	std::cout << std::setfill('-') << std::setw(80) << std::endl;
}


// Ausgabe um gewuenschten Format (ueberladen)
void Fahrzeug::vAusgeben(std::ostream& o) const
{
	//std::cout<<"Test Fahrzeug vAusgeben"<<std::endl;
	Simulationsobjekt::vAusgeben(o);
	o << std::resetiosflags(std::ios::left);
	o << std::setiosflags(std::ios::right)<<std::setw(25) << p_dMaxGeschwindigkeit << std::setw(25) << std::setprecision(5) << p_dGesamtStrecke << std::setw(30) << dGeschwindigkeit();

}

// Berechnen von Werten, noetig fuer Ausgabe und Verwaltung der einzelnen Objekten
void Fahrzeug::vSimulieren()
{
		double dFahrzeit = dGlobaleZeit - p_dZeit; // Fahrtzeit wird bestimmt durch Abfrage der verstrichenen Zeit seit der letzten Abfrage und Summation

		if (dFahrzeit > 0){

			double weg = 0;
			// std::cout << "Bis hier ist okay" << std::endl;
			weg = p_pVerhalten->dStrecke(*this, dFahrzeit);		// Weg wird berechnet und dabei werden Ausnahmen geworfen

			p_dZeit = dGlobaleZeit; // Zeitflag um mit der globalen Zeit abgleichen zu koennen
			p_dGesamtZeit += dFahrzeit; // Summation der einzelnen Zeitabschnitte zur Gesamtzeit
			p_dGesamtStrecke += weg; // Summation der einzelnen Streckenabschnitte zur Gesamtstrecke
			p_dAbschnittStrecke += weg; 	// Summation, wenn noch weg zurueckgelegt wurde
	}
}

bool Fahrzeug::bUeberholenGueltig() const
{
	//Hier wird false als Deafult gesetzt, da nicht jedes Fahrzeug beruecksichtigt wird
	return false;
}

// Standard, wenn nicht anders, dann Tanken nicht moeglich
double Fahrzeug::dTanken(double dMenge)
{
    return 0;
}

void Fahrzeug::vEinlesen(std::istream& i)	// Recht analog zu vAusgabe
{
	Simulationsobjekt::vEinlesen(i);
	i >> this->p_dMaxGeschwindigkeit;
}

void Fahrzeug::vZeichnen(const Weg& wWeg) const		// Wird in den Unterklassen jeweils ueberschrieben
{
}

// Getter fuer Zeit
double Fahrzeug::getZeit() const
{
	return p_dZeit;
}

// Getter fuer zurueckgelegeten Weg im letzten Abschnitt
double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

void Fahrzeug::setAbschnittStrecke(double pStrecke)
{
	p_dAbschnittStrecke = pStrecke;
}

// Getter fuer gesamten Weg
double Fahrzeug::getGesamtStrecke() const
{
	return p_dGesamtStrecke;
}

// Gibt Geschwindigkeit zurueck fuer Berechnungen
double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}


// Neue Instanz von Verhalten als p_pVerhalten erzeugen und in Fahrzeug speichern
// Was passiert mit der alten Instanz? -> unique Pointer wird also geloescht
void Fahrzeug::vNeueStrecke(Weg& wWeg)
{
	p_pVerhalten = std::make_unique<Fahren> (wWeg);
	this->p_dAbschnittStrecke = 0;	// Ist ja ein neuer Abschnitt
	p_dZeit = dGlobaleZeit;

}

// Neue Instanz von Verhalten als p_pVerhalten erzeugen und in Fahrzeug speichern
void Fahrzeug::vNeueStrecke(Weg& wWeg, double dStartzeit)
{
	if (dStartzeit >= dGlobaleZeit)
	{
	p_pVerhalten = std::make_unique<Parken>(wWeg, dStartzeit);
	p_dAbschnittStrecke = 0;	// Ist ja ein neuer Abschnitt
}

}


// Ueberladen des Gleich - Operators
Fahrzeug&  Fahrzeug::operator=(const Fahrzeug& vehicle3)
{
	//Was muss man bei der ID beachten? --> ID ist eine const Variable -> kann nach Deklaration nicht mehr bearbeitet werden
	p_dMaxGeschwindigkeit = vehicle3.p_dMaxGeschwindigkeit;

	//Was wuerde passieren, wenn Sie keine eigene Definition fuer den Operator erstellt haben?
	// Wuerde versuchen alle Daten des Objektes zu kopieren
	// -> Objekt mit ID kopiert -> wird durch loeschen des Copy-Konstruktors verhindert
	p_sName = vehicle3.p_sName + "-Kopie";

	// Stammdaten sind hier Parameter, nicht die ID

	return *this;
}

bool Fahrzeug::operator==(const Fahrzeug& fahrzeug)const
{
	return Simulationsobjekt::operator ==(fahrzeug);
}

// Ueberladen des kleiner - Operators, nach Aufgabenstellung
bool Fahrzeug::operator<(const Fahrzeug& verglFarzeug) const
{
	if (this->p_dGesamtStrecke < verglFarzeug.p_dGesamtStrecke)
		{
			return true;
		}

	else
		{
			return false;
		}
}

