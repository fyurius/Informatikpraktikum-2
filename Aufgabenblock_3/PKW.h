/*
 * PKW.h
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */

#pragma once

#include "Fahrzeug.h"
#include "Weg.h"

class Verhalten;

class PKW: public Fahrzeug {

public:

	// Konstruktor und Destruktor
	PKW(std::string name);
	PKW(std::string sName, double sMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);
	virtual ~PKW();


	// An PKW angepasste Fahrzeug Methoden
	virtual double dTanken(double dMenge = dLimit) override;
	virtual double dGeschwindigkeit() const override;
	double dGetTankinhalt() const;

	// Check Funktion fuer Ueberholverbot
	bool bUeberholenGueltig() const override;

	// I/O Methoden
	virtual void vZeichnen(const Weg& wWeg) const override;
	virtual void vSimulieren() override;
	virtual void vAusgeben(std::ostream& o) const override;
	void vEinlesen(std::istream& i);

	// Ueberladener Operator
	PKW& operator=(const PKW& vehicle3);

	// Copy - Konstruktor wird geloescht wegen ID - Problemen
	PKW(const PKW&) = delete;

private:

	// Variablen die nur fuer PKWs gebraucht werden
    double p_dVerbrauch = 0; //Oel-Verbrauch in Liter/100km
    double p_dTankvolumen = 0; //Tankvolumen in Liter
    double p_dTankinhalt = 0; //in Liter

};
