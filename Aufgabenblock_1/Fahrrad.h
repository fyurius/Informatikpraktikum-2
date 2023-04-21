/*
 * Fahrrad.h
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */
#pragma once
#include "Fahrzeug.h"
#include <cmath> // Noetig fuer double dspeed = std::pow(0.9, (int)p_dGesamtStrecke / 20);

class Fahrrad: public Fahrzeug {

public:

	// Konstruktor
	Fahrrad(std::string sName, double dMaxGeschwindigkeit);

	// Auf diese Klasse angepasste Methoden
	double dGeschwindigkeit() const override;

	Fahrrad& operator=(const Fahrrad& vehicle3);

	Fahrrad(const Fahrrad&) = delete;
};
