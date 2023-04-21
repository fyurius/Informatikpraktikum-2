/*
 * Parken.h
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */
#pragma once

#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"

#define PARKEN_H_

class Parken: public Verhalten
{
public:
	Parken() = delete; // Standard ergibt wenig Sinn
	Parken(Weg& wWeg, double dStartzeitpunkt);

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;		// Zweckmaessig angepasst

private:
	double p_dStartzeitpunkt;		// Verzoegert Losfahren

};


