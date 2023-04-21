/*
 * Simulationsobjekt.h
 *
 *  Created on: 11.11.2022
 *      Author: finle
 */

#pragma once
#include "SimuClient.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <limits> //Noetig fuer  std::numeric_limits<double>::infinity() & std::numeric_limits<int>::max()
#include <stdexcept>		// Exceptionhandling
#include <fstream>

extern double dGlobaleZeit; //Globale Zeit der Simulation

#define SIMULATIONSOBJEKT_H_

class Simulationsobjekt
{
	public:

		// Konstruktoren und Destruktoren
		Simulationsobjekt();
		Simulationsobjekt(std::string sParameterName);
		virtual ~Simulationsobjekt() = 0;

		// Ausgabemthode / Eingabe
		virtual void vAusgeben(std::ostream& o)  const;
		virtual void vEinlesen(std::istream& i);

		// Simulation ohne funktion
		virtual void vSimulieren() = 0;

		// Getter
		double getID()const;
		virtual std::string getName() const;

		// Ueberladener Operator
		bool operator==(const Simulationsobjekt& param) const;

		// Copy - Konstrukor gloescht, wegen Id - Problemen
		Simulationsobjekt(const Simulationsobjekt&) = delete;

	protected:

		// Namen und ID muss jedes Objekt haben
		std::string p_sName;
		int p_iID;
		double p_dZeit = 0;

	private:

		// Benoetigt fuer einzigartige IDs
		static unsigned int p_iMaxID;

};

// Muss auﬂerhalb der Klasse ueberladen werden
std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& ObjektParam);
std::istream& operator>>(std::istream& i, Simulationsobjekt&);
