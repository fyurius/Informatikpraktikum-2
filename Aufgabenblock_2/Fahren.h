/*
 * Fahren.h
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#pragma once

#include "Fahrzeug.h"
#include "Weg.h"
#include "Verhalten.h"

#define FAHREN_H_

class Fahren: public Verhalten
{
public:

	// Standardkonstruktor wird nicht gebraucht
	Fahren(Weg& wWeg);

	// Angepasste Methode dStrecke um Fahrverhalten darzustellen
	double dStrecke(Fahrzeug& aFzg, double dZeitintervall) override;
};

