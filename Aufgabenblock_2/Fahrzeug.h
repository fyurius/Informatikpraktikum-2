/*
 * Fahrzeug.h
 *
 *  Created on: 18.10.2022
 *      Author: finle
 */
#pragma once

#include "Simulationsobjekt.h"

extern double dGlobaleZeit; //Globale Zeit der Simulation
extern double dLimit;

class Weg;
class Verhalten;

class Fahrzeug : public Simulationsobjekt{

public:

	// Konstruktoren und Destruktoren
	Fahrzeug();
	Fahrzeug(std::string sParameterName, double sMaxGeschwindigkeit) ;
	virtual ~Fahrzeug()	;

	//Getter
	virtual double getZeit() const;
	double getAbschnittStrecke() const;
	double getGesamtStrecke() const;

	// Ausgabemethoden
	static void vKopf();
	virtual void vAusgeben(std::ostream& o) const override;
	virtual void vZeichnen(const Weg& wWeg) const;

	//Ausführende Methoden
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = dLimit);
	virtual void vNeueStrecke(Weg& wWeg);
	virtual void vNeueStrecke(Weg& wWeg, double dStartzeit);
	virtual double dGeschwindigkeit() const;

	//Ueberladene Operatoren
	bool operator<(const Fahrzeug& vehicle2) const;
	virtual Fahrzeug& operator=(const Fahrzeug& vehicle3);
	bool operator==(const Fahrzeug& fahrzeug) const;

	// Copy-Konstruktor geloescht
	Fahrzeug(const Fahrzeug&) = delete;

protected:

	// Benoetigte Variablen
	std::string p_sName;
	int p_iID;
	double p_dZeit = 0;
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dAbschnittStrecke = 0;

	// Sammlung der Fahrzeuge
	std::unique_ptr<Verhalten> p_pVerhalten ;

};

