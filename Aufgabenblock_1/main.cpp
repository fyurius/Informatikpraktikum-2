/*
 * main.cpp
 *
 *  Created on: 24.10.2022
 *      Author: finle
 */
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

double dGlobaleZeit = 0.0;
double dLimit = std::numeric_limits<double>::infinity();

void vAufgabe_1(){
	/*
	//dynamisch erzeugte Fahrzeuge
	Fahrzeug* Mercedes;
	Mercedes = new Fahrzeug ("Mercedes");

	std::unique_ptr<Fahrzeug> Volvo;
	Volvo = std::make_unique<Fahrzeug>();

	std::unique_ptr<Fahrzeug> Fiat;
	Fiat = std::make_unique<Fahrzeug>();

	std::shared_ptr<Fahrzeug> Renault;
	Renault = std::make_shared<Fahrzeug>();


	//statisch erzeugte Fahrzeuge
	Fahrzeug Audi;
	Fahrzeug Porsche("Porsche");

	std::shared_ptr<Fahrzeug> Nissan;
	//Nissan = std::make_shared<Fahrzeug>(Porsche);
	std::cout<<Nissan.use_count()<<std::endl;
	std::shared_ptr<Fahrzeug> VW = Nissan;
	std::cout<<Nissan.use_count()<<std::endl;

	// Vectoren fuer unique and shared Pointers

	std::vector<std::unique_ptr<Fahrzeug>> Autohaus;
	Autohaus.push_back(move(Volvo));
	Autohaus.clear();

	std::vector<std::shared_ptr<Fahrzeug>> Lauf;
	Lauf.push_back(Nissan);
	Lauf.push_back(move(VW));

	std::cout<<Nissan.use_count()<<std::endl;

	// Loeschen des Vectors
	Lauf.clear();
	*/
}

void vAufgabe_1a()
{

	std::vector<std::unique_ptr<Fahrzeug>> Fahrzeugvector1a;

	// Erstellen von 3 Fahrzeugen und einfuegen in designierten Vector
	for (int i = 0; i < 3; i++)
	{
		std::string sName;
		double dSpeed;
		std::cout << "Name des " << i + 1 << ". Fahrzeugs eingeben:  " << std::endl << std::endl;
		std::cout << "Name: ";
		std::cin >> sName;
		std::cout << "Maximalgeschwindigkeit: ";
		std::cin >> dSpeed;
		std::cout << "" << std::endl;
		Fahrzeugvector1a.push_back(move(std::make_unique<Fahrzeug>(sName, dSpeed)));
		std::cout << "" << std::endl;
	}

	double dIntervall = 0.25; // 1/4h Intervall

	// Simulation in 1/4h Intervallen
	for (; dGlobaleZeit < 1.25; dGlobaleZeit += dIntervall) // Legt fest, wie lange simuliert wird
	{
		Fahrzeugvector1a[0]->vKopf();
		std::cout << "" << std::endl;

		for (int i = 0; i < 3; i++)							// Aufruf der Simulation fuer jedes Objekt
		{
			Fahrzeugvector1a[i]->vSimulieren();
			std::cout << *Fahrzeugvector1a[i];
			std::cout << "" << std::endl;
		}
	}
}

void vAufgabe_2()
{
	int iFahrrad; //Anzahl der Fahrraeder, eingegeben vom Benutzer
	int iPKW; //Anzahl der PKWs, eingegeben vom Benutzer

	std::vector<std::unique_ptr<Fahrzeug>> Fahrzeugvector2;

	std::cout << "Wie viele Fahrraeder sollen erzeugt werden? ";
	std::cin >> iFahrrad;
	std::cout << "" << std::endl;

	// Gewuenschte Anzahl an Fahrraedern wird erstellt, bestueckt und hinzugefuegt
	for (int i = 1; i <= iFahrrad; i++)
	{
		std::string sName;
		double dSpeed;

		std::cout << "Bitte geben Sie die Daten des " << i << " Fahrrads:" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Name: ";
		std::cin >> sName;
		std::cout << "Geschwindigkeit: ";
		std::cin >> dSpeed;
		Fahrzeugvector2.push_back(move(std::make_unique<Fahrzeug>(sName, dSpeed)));

	}

	// Warum sollte man keine Objekte vom Typ Fahrzeug speichern?
	// -> Fahrzeug ist die Basisklasse, nutzbare Objekte sind allerdings stets von den Unterklassen
	// Warum kann man PKWs und Fahrraeder in einem gemeinsamen Vektor speichern?
	// Beide vom selben "Typ, also beide von derselben Klasse abgeleitet
	// -> Koennen somit in einen einzigen Vektor

	// Analog zu Fahrraedern weiter oben
	std::cout << "Wie viele PKWs wollen Sie eingeben? ";
	std::cin >> iPKW;
	std::cout << "" << std::endl;

	//
	for (int i = 1; i <= iPKW; i++)
	{
		std::string sName;
		double dSpeed;
		double dVerbrauch;
		double dTankvolumen;

		std::cout << "Bitte geben Sie die Daten des " << i << " PKW:" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Name: ";
		std::cin >> sName;
		std::cout << "Geschwindigkeit: ";
		std::cin >> dSpeed;
		std::cout << "Oelverbrauch (in L/100km): ";
		std::cin >> dVerbrauch;
		std::cout << "Ist das Tankvolumen bekannt? (j/n) \n";
		std::string sAntwort;
		std::cin >> sAntwort;
		if (sAntwort == "j")
		{
			std::cout << "Tankvolumen (in Liter): ";
			std::cin >> dTankvolumen;
			Fahrzeugvector2.push_back(move(std::make_unique<PKW>(sName, dSpeed, dVerbrauch,
				dTankvolumen)));
			std::cout << "" << std::endl;
		}

		else
		{
			Fahrzeugvector2.push_back(move(std::make_unique<PKW>(sName, dSpeed, dVerbrauch)));
			std::cout << "" << std::endl;
		}
	}

	// Start der Simulation der Objekte
	double dTakt = 0.5; //Takt in 30 Minuten
	bool bTankstatus = false; // Ueberpruefen des Tankstatus

	for (; dGlobaleZeit < 4.7; dGlobaleZeit += dTakt)	// Steuert wie lange Simuliert wird
	{

		Fahrzeugvector2[0]->vKopf();
		std::cout << "" << std::endl;

		for (int i = 0; i < Fahrzeugvector2.size(); i++) // Simulation fuer alle Objekte im Vektor
		{
			Fahrzeugvector2[i]->vSimulieren();
			std::cout << (*Fahrzeugvector2[i]); // Ueberladene Ausgabe
		}

		if (dGlobaleZeit >= 3.0 && bTankstatus == false) // Nach 3 Stunden muss getankt werden (Aufgabenstellung)
		{
			std::cout << "3 Stunden sind um, sollen die PKWs neu getankt werden? (j/n) \n";
			std::string sAntwort1;
			std::cin >> sAntwort1;
			if (sAntwort1 == "j")
			{
				std::string sAntwort2;
				std::cout << "Wollen Sie alle PKWs betanken? (j/n) \n";
				std::cin >> sAntwort2;
				if (sAntwort2 == "j")
				{
					for (int i = 0; i < Fahrzeugvector2.size(); i++)
					{
						std::cout << "Mit wie viel Litern soll das Fahrzeug " << Fahrzeugvector2[i]->sGetName() << " betankt werden?";
						double dOelmenge = 0;
						std::cin >> dOelmenge;
						Fahrzeugvector2[i]->dTanken(dOelmenge);
					}

					bTankstatus = true; // PKW ist nun mindestens einmal betankt worden
				}
			}
		}
		std::cout << "" << std::endl;
	}
}

void vAufgabe_3()
{
	std::vector<std::unique_ptr<Fahrzeug>> Fahrzeugvector3;

	// Objekte vom Typ Fahrrad
	Fahrzeugvector3.push_back(move(std::make_unique<Fahrrad>("Fahrrad in schnell", 35)));
	Fahrzeugvector3.push_back(move(std::make_unique<Fahrrad>("Normales Fahrrad", 20)));
	Fahrzeugvector3.push_back(move(std::make_unique<Fahrrad>("Kaputtes Fahrrad", 0)));


	// Objekte vom Typ PKW
	Fahrzeugvector3.push_back(move(std::make_unique<PKW>("Audi", 60, 13, 60)));
	Fahrzeugvector3.push_back(move(std::make_unique<PKW>("Porsche", 80, 15, 70)));


	double dTakt = 0.25; // 15 Minuten Takt

	// Simulation mit den vorher erstellten Objekten
	for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt) // Hier 5 Simulationsschritte
	{
		Fahrzeugvector3[0]->vKopf();	// Beginn der Ausgabetabelle
		std::cout << "" << std::endl;

		for (int i = 0; i < 5; i++)		// Simulation und Ausgabe der einzelnen Objekte im Vektor
		{
			Fahrzeugvector3[i]->vSimulieren();
			std::cout << *Fahrzeugvector3[i];
			std::cout << "" << std::endl;
		}
		std::cout << "" << std::endl;
	}

	// Test der Operatoren, die ueberladen werden sollten

	// Test des < Operartors mit der Fahrtzeit anhand der beiden PKWs
	if (*Fahrzeugvector3[3] < *Fahrzeugvector3[4])
	{
		std::cout << Fahrzeugvector3[4]->sGetName() << " ist weiter gefahren als " << Fahrzeugvector3[3]->sGetName() << "." << std::endl;
		std::cout << "" << std::endl;
	}
	else if (*Fahrzeugvector3[4] < *Fahrzeugvector3[3])
	{
		std::cout << Fahrzeugvector3[3]->sGetName() << " ist weiter gefahren als " << Fahrzeugvector3[4]->sGetName() << "." << std::endl;
		std::cout << "" << std::endl;
	}
	else // Muss ja so
	{
		std::cout << Fahrzeugvector3[3]->sGetName() << "&" << Fahrzeugvector3[4]->sGetName() << "sind genauso weit gefahren." << "." << std::endl;
		std::cout << "" << std::endl;
	}

	// Test des = Operators mit zwei Objekten vom Typ Fahrrad

	std::unique_ptr<Fahrzeug> dummy;
	dummy = std::make_unique<Fahrzeug>();
	*dummy = *Fahrzeugvector3[2];
	*Fahrzeugvector3[1] = *dummy;


	//*Fahrzeugvector3[2] = *Fahrzeugvector3[1]; // Stammdaten werden uebernommen

	// Test der Ausgabe
	Fahrzeugvector3[0]->vKopf();
	std::cout << (*Fahrzeugvector3[0]);
	std::cout << (*Fahrzeugvector3[1]);
	std::cout << (*Fahrzeugvector3[2]);
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
}


int main (){

	//vAufgabe_2();

}
