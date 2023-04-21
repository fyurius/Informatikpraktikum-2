/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 11.11.2022
 *      Author: finle
 */

#include "Simulationsobjekt.h"

unsigned int Simulationsobjekt::p_iMaxID = 1;

// Ganz einfacher Konstruktor
Simulationsobjekt::Simulationsobjekt() :
	p_sName(""), p_iID(p_iMaxID++)
{
	std::cout << "Ein Simulationsobjekt namens: " << p_sName << "und ID#: " << p_iID << " wurde anhand des Standardkonstruktors erstellt" << std::endl;
	std::cout << "" << std::endl;
}

//Konstruktor mit Parameter Name
Simulationsobjekt::Simulationsobjekt(std::string sParameterName)
	:p_sName(sParameterName), p_iID(p_iMaxID++)
{
	std::cout << "Ein Objekt: " << p_sName << " ,mit ID: " << p_iID << " wurde mit dem 2. Konstruktor erzeugt" << std::endl;
	std::cout << "" << std::endl;
}

// Destruktor
Simulationsobjekt::~Simulationsobjekt()
{
	std::cout << "Name des geloeschten Objektes: " << p_sName << " ObjektID: "  << p_iID << std::endl;
	std::cout << "" << std::endl;
}

// Wird spaeter mit Funktion versehen
void Simulationsobjekt::vSimulieren(){
}

// Standardausgabe ohne besondere Parameter
void Simulationsobjekt::vAusgeben(std::ostream& o) const
{
	//std::cout<<"Test SimObjekt vAusgeben"<<std::endl;
	o << std::resetiosflags(std::ios::left);
	o << std::setiosflags(std::ios::right) << std::setw(10) << p_iID << std::setw(20) << p_sName ;

}

// Recht analg zur Ausgabe
void Simulationsobjekt::vEinlesen(std::istream& i)
{
	if (p_sName != "") //Wenn der Name nicht leer ist --> da wurde schon was gespeichert
	{
		throw std::runtime_error("Der Name ist schon definiert!");  //dann wird das ausgegeben
	}
	i >> this->p_sName; //sonst wird der eingelesene Name gespeichert
}


// Getter fuer ID
double Simulationsobjekt::getID() const
{
	return p_iID;
}

// Get - Methode fuer Namen
std::string Simulationsobjekt::getName() const
{
	return p_sName;
}

// Ueberladener Vergleichsoperator
bool Simulationsobjekt::operator==(const Simulationsobjekt& param) const
		{
			return this->p_iID == param.p_iID;
		}

// Ueberladen des Ausgabe - Operators
std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& ObjektParam)
{
	std::cout << "" << std::endl;
	ObjektParam.vAusgeben(o);
	std::cout << "" << std::endl;
	return o;
}

std::istream& operator>>(std::istream& i, Simulationsobjekt& SimObjekt)
{
	SimObjekt.vEinlesen(i);
	return i;
}
