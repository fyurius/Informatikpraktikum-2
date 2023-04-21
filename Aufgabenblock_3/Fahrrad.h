/*
 * Fahrrad.h
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */
#pragma once

#include "Fahrzeug.h"
#include "Weg.h"

#include <cmath> // Noetig fuer double dspeed = std::pow(0.9, (int)p_dGesamtStrecke / 20);

class Fahrrad: public Fahrzeug {

public:

	// Konstruktor
	Fahrrad(std::string name);
	Fahrrad(std::string sName, double dMaxGeschwindigkeit);

	// Auf diese Klasse angepasste Methoden
	virtual double dGeschwindigkeit() const override;
	virtual void vZeichnen(const Weg& wWeg) const override;

	// I/O Methoden
	virtual void vAusgeben(std::ostream& o) const override;
	void vEinlesen(std::istream& i);

	// Ueberladener Vergleichsoperator
	Fahrrad& operator=(const Fahrrad& vehicle3);

	// Copy - Konstruktor wird geloescht, damit keine inkorrekten Zuweisungen erfolgen koennen
	Fahrrad(const Fahrrad&) = delete;
};
