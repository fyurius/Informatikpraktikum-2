/*
 * Verhalten.h
 *
 *  Created on: 16.11.2022
 *      Author: finle
 */

#pragma once

class Fahrzeug;
class Weg;

extern double dGlobaleZeit;

#define VERHALTEN_H_

class Verhalten
{
public:

	// Konstruktoren
	Verhalten() = delete;	// Standard ergibt wenig Sinn
	Verhalten (Weg& wParameterWeg);
	~Verhalten() = default;

	// Getter
	double getTempolimitWeg() ;
	Weg& getWeg() const;

	// Ausfuehrende Methoden
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitintervall) = 0;		// Wird spaeter mit Funktion versehen

protected:
	Weg& p_wParameterWeg;

};

