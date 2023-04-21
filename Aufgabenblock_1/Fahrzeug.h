/*
 * Fahrzeug.h
 *
 *  Created on: 18.10.2022
 *      Author: finle
 */
#pragma once
#include <string>
#include <iostream>
#include <iomanip>

#include <limits> //Noetig fuer p_dTankinhalt = std::numeric_limits<double>::infinity();


extern double dGlobaleZeit; //Globale Zeit der Simulation
extern double dLimit;


class Fahrzeug {

public:
	// Konstruktoren und Destruktoren
	Fahrzeug();
	Fahrzeug(std::string sParameterName);
	Fahrzeug(std::string sParameterName, double sMaxGeschwindigkeit);
	virtual ~Fahrzeug();

	// Klasseneigene Methoden
	static void vKopf();
	std::string sGetName() const;

	//Methoden die vererbt werden
	virtual void vSimulieren();
	virtual double dGeschwindigkeit() const;
	virtual double dTanken(double dMenge = dLimit);
	virtual void vAusgeben(std::ostream& o) const;

	//Ueberladene Operatoren
	bool operator<(const Fahrzeug& vehicle2) const;
	virtual Fahrzeug& operator=(const Fahrzeug& vehicle3);

	// Copy-Konstruktor geloescht
	Fahrzeug(const Fahrzeug&) = delete;

private:

	// Benoetigt fuer einzigartige IDs
	static unsigned int p_iMaxID;

protected:

	// Benoetigte Variablen
	std::string p_sName;
	int p_iID;
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dZeit = 0;

};

// Muss außerhalb der Klasse ueberladen werden
std::ostream& operator<<(std::ostream& o, const Fahrzeug& vehicle1);
