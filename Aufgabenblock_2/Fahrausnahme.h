/*
 * Fahrausnahme.h
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */
#pragma once

#include "Weg.h"
#include "Fahrzeug.h"

#include <exception>

#define FAHRAUSNAHME_H_

class Fahrausnahme : public std::exception
{
public:

	// Standardkonstruktor entfernt, da er nicht verwendet werden soll
	Fahrausnahme() = delete;
	Fahrausnahme(Fahrzeug& aFzg, Weg& wWeg);

	virtual void vBearbeiten() = 0;		// Abstrakte Methode

protected:			// Werden in den Unterklassen noch gebraucht
	Fahrzeug& p_aFahrzeug ;
	Weg& p_aWeg;
};


