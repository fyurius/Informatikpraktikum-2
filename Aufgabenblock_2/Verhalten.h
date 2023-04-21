/*
 * Verhalten.h
 *
 *  Created on: 16.11.2022
 *      Author: finle
 */

#pragma once

class Fahrzeug;
class Weg;

#define VERHALTEN_H_

class Verhalten
{
public:
	Verhalten() = delete;	// Standard ergibt wenig Sinn
	Verhalten (Weg& wParameterWeg);
	~Verhalten() = default;

	// Getter
	double getTempolimitWeg() ;

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitintervall) = 0;		// Wird spaeter mit Funktion versehen (abstrakte Klasse)

protected:
	Weg& p_wParameterWeg;

};

