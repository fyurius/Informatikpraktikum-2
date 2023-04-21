/*
 * PKW.h
 *
 *  Created on: 01.11.2022
 *      Author: finle
 */


#pragma once
#include "Fahrzeug.h"
#include <limits> //Noetig fuer p_dTankinhalt = std::numeric_limits<double>::infinity();


class PKW: public Fahrzeug {

public:

	// Konstruktor und Destruktor
	PKW(std::string sName, double dMaxSpeed, double dVerbrauch, double dTankvolumen = 55);
	virtual ~PKW();


	// An PKW angepasste Fahrzeug Methoden
	double dTanken(double dMenge = dLimit) override;
	void vSimulieren() override;
	void vAusgeben(std::ostream& o) const override;

	// Ueberladener Operator
	PKW& operator=(const PKW& vehicle3);


	PKW(const PKW&) = delete;

private:

	// Variablen die nur fuer PKWs gebraucht werden
    double p_dVerbrauch = 0; //Oel-Verbrauch in Liter/100km
    double p_dTankvolumen = 0; //Tankvolumen in Liter
    double p_dTankinhalt = 0; //in Liter

};
