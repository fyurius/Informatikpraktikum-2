/*
 * Fahrzeug.cpp
 *
 *  Created on: 18.10.2022
 *      Author: finle
 */

#include "Fahrzeug.h"


unsigned int Fahrzeug::p_iMaxID = 1;

//Standart Konstruktor (1. Konstruktor)
Fahrzeug::Fahrzeug()
	:p_sName(""), p_iID(p_iMaxID++)
{
	std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde mit dem 1. Konstruktor erzeugt" << std::endl;
	std::cout << "" << std::endl;
}


// 2. Konstruktor
Fahrzeug::Fahrzeug(std::string sParameterName)
	:p_sName(sParameterName), p_iID(p_iMaxID++)
{
	std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde mit dem 2. Konstruktor erzeugt" << std::endl;
	std::cout << "" << std::endl;
}

//3. (meist genutzter) Konstruktor
Fahrzeug::Fahrzeug(std::string sParameterName, double sMaxGeschwindigkeit)
	: p_sName(sParameterName), p_iID(p_iMaxID++),
	  p_dMaxGeschwindigkeit((sMaxGeschwindigkeit > 0) ? sMaxGeschwindigkeit:(sMaxGeschwindigkeit*-1))
{
	std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde mit dem 3. Konstruktor erzeugt" << std::endl;
	std::cout << "" << std::endl;
}

// Dekonstruktor
Fahrzeug::~Fahrzeug()
{
	std::cout << "Name des geloeschten Objektes: " << p_sName << " ObjektID: "  << p_iID << std::endl;
	std::cout << "" << std::endl;
}

// Gibt Geschwindigkeit zurueck fuer Berechnungen
double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

// Beschriftet Tabelle korrekt
void Fahrzeug::vKopf()
{
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(10) << "ID" << std::setw(20) << "Name" << std::setw(30) << "MaxGeschwindigkeit (km/h)" << std::setw(25) << "Gesamtstrecke [km/h]" << std::setw(35) << "akt. Geschwindigkeit [km]" << std::setw(25) << "Gesamtverbrauch [l]" << std::setw(25) << "akt. Tankinhalt [l]" << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}


// Ausgabe um gewuenschten Format (ueberladen)
void Fahrzeug::vAusgeben(std::ostream& o) const
{
	std::cout << "" << std::endl;
	o << std::resetiosflags(std::ios::left);
	o << std::setiosflags(std::ios::right) << std::setw(10) << p_iID << std::setw(20) << p_sName << std::setw(25) << p_dMaxGeschwindigkeit << std::setw(25) << std::setprecision(5) << p_dGesamtStrecke << std::setw(30) << dGeschwindigkeit();

}

// Berechnen von Werten, noetig fuer Ausgabe und Verwaltung der einzelnen Objekten
void Fahrzeug::vSimulieren()
{
	if (dGlobaleZeit > p_dZeit)
	{
		double dFahrzeit = dGlobaleZeit - p_dZeit; // Fahrtzeit wird bestimmt durch Abfrage der verstrichenen Zeit seit der letzten Abfrage und Summation
		double dNeueStrecke = dFahrzeit * dGeschwindigkeit(); // s = v*t
		p_dGesamtStrecke += dNeueStrecke; // Summation der einzelnen Streckenabschnitte zur Gesamtstrecke
		p_dGesamtZeit += dFahrzeit; // Summation der einzelnen Zeitabschnitte zur Gesamtzeit
		p_dZeit = dGlobaleZeit; // Zeitflag um mit der globalen Zeit abgleichen zu koennen
	}
}

// Standard, wenn nicht anders, dann Tanken nicht moeglich
double Fahrzeug::dTanken(double dMenge)
{
    return 0;
}

// Get - Methode fuer Namen
std::string Fahrzeug::sGetName() const
{
	return p_sName;
}



//Ueberladen




// Ueberladen des Ausgabe - Operators
std::ostream& operator<<(std::ostream& o, const Fahrzeug& vehicle1)
{
	std::cout << "" << std::endl;
	vehicle1.vAusgeben(o);
	std::cout << "" << std::endl;
	return o;
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

// Ueberladen des Kleiner - Operators, nach Aufgabenstellung
bool Fahrzeug::operator<(const Fahrzeug& vehicle2) const
{
	if (this->p_dGesamtStrecke < vehicle2.p_dGesamtStrecke)
	{
		return true;
	}

	else
	{
		return false;
	}
}

