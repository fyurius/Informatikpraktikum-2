/*
 * main.cpp
 *
 *  Created on: 24.10.2022
 *      Author: finle
 */
#include "Simulation.h"
#include "Simulationsobjekt.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include "Kreuzung.h"
#include "SimuClient.h"
#include "vertagt_liste - Vorlage.h"
#include "Verhalten.h"


#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include <iostream>

double dGlobaleZeit = 0.0;
double dLimit = std::numeric_limits<double>::infinity();

static std::ranlux24 device(0);				// Ranlux 24 generator
std::uniform_int_distribution<int> dist(0,9);	// Gleichverteilung von Integern

Simulation test;

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
						std::cout << "Mit wie viel Litern soll das Fahrzeug " << Fahrzeugvector2[i]->getName() << " betankt werden?";
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
		std::cout << Fahrzeugvector3[4]->getName() << " ist weiter gefahren als " << Fahrzeugvector3[3]->getName() << "." << std::endl;
		std::cout << "" << std::endl;
	}
	else if (*Fahrzeugvector3[4] < *Fahrzeugvector3[3])
	{
		std::cout << Fahrzeugvector3[3]->getName() << " ist weiter gefahren als " << Fahrzeugvector3[4]->getName() << "." << std::endl;
		std::cout << "" << std::endl;
	}
	else // Muss ja so
	{
		std::cout << Fahrzeugvector3[3]->getName() << "&" << Fahrzeugvector3[4]->getName() << "sind genauso weit gefahren." << "." << std::endl;
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

	std::cout << "" << std::endl;

}

void vAufgabe_4()
{
	/*
	Weg thatsnotambigous("Test", 100, Tempolimit::Innerorts);
	Weg::vKopf();
	std :: cout << thatsnotambigous;
	*/
	}

void vAufgabe_5()
{
	/*
	double dTakt = 0.25;

	Weg weg("Test", 100, Tempolimit::Innerorts);
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(std::make_unique<PKW>("Audi", 242, 8, 90));
	fahrzeuge.push_back(std::make_unique<PKW>("Porsche", 450, 18, 90));
	fahrzeuge.push_back(std::make_unique<Fahrrad>("Klapperding", 5));
	Weg::vKopf();
	weg.vAnnahme(move(fahrzeuge[0]), 3);
	weg.vAnnahme(move(fahrzeuge[1]));
	weg.vAnnahme(move(fahrzeuge[2]));

	for (; dGlobaleZeit < 10; dGlobaleZeit += dTakt){
	weg.vSimulieren();
	}
	*/
}

void vAufgabe_6()
{
	/*
	// Erstellen aller noetigen Objekte

	Weg rechteSp("RechteSpur", 500, Tempolimit::Innerorts);
	Weg linkeSp("LinkeSpur", 500, Tempolimit::Innerorts);


	linkeSp.vAnnahme(std::make_unique<PKW>("MeinAudi", 400, 1, 100),1);
	linkeSp.vAnnahme(std::make_unique<PKW>("LukasBMW", 200, 3, 100));
	//rechteSp.vAnnahme(move(std::make_unique<PKW>("Porsche", 130, 10, 100)));
	rechteSp.vAnnahme(move(std::make_unique<Fahrrad>("JuliansRennrad", 75)));

	bInitialisiereGrafik(800,500);
	int Koordinaten[4] = {700,250,100,250};
	bZeichneStrasse("LinkeSpur", "RechteSpur", 500, 2, Koordinaten);

	double dTakt = 0.25;

	// Simulation
	for (; dGlobaleZeit <40; dGlobaleZeit += dTakt){

		//vSetzteZeit(dGlobaleZeit);
		rechteSp.vSimulieren();
		linkeSp.vSimulieren();
		vSetzeZeit(dGlobaleZeit);
		//vSleep(400);
		std::cout<<linkeSp<<std::endl;
		}
	Weg::vKopf();
	linkeSp.vAusgeben(std::cout);

	*/
}

void vAufgabe_6a()
{
	vertagt::VListe<int> liste;

	for(int i = 0; i<10; i++)
	{
		liste.push_back(dist(device)); // benutzt die true random generator Funktionalitaet aus <random>
	}
	liste.vAktualisieren();

	std::cout << "Liste mit allen Elementen: " << std::endl;

	for(auto schablone : liste)
	{
		std::cout << schablone << std::endl;
	}

	auto it = liste.begin();
	while (it != liste.end())
	{
		if(*it > 5)
		{
			liste.erase(it);
		}
		it++;
	}

	std::cout << "Liste ohne Elemente groesser 5: " << std::endl;

	for(auto schablone : liste)
		{
			std::cout << schablone << std::endl;
		}

	liste.vAktualisieren();

	std::cout << "Liste ohne Elemente groesser 5 & Liste wurde aktualisiert: " << std::endl;

	for(auto schablone : liste)
			{
				std::cout << schablone << std::endl;
			}

	liste.push_front(4);
	liste.push_back(9);

	std::cout << "Liste ohne Elemente groesser 5 & Liste wurde aktualisiert & zwei Zahlen eingefuegt: " << std::endl;

	for(auto schablone : liste)
			{
					std::cout << schablone << std::endl; 				//Die wurde ja garnicht aktualisiert also pointless
			}
}

void vAufgabe_7()
{
	bInitialisiereGrafik(1000, 600); //Ausgabefenster

	// Erstellen von Kreuzungen zum Test
	double TS1 = 0.0; //Tankstellen
	double TS2 = 100;
	double TS3 = 100;
	double TS4 = 0.0;
	std::shared_ptr<Kreuzung> Kr1 = std::make_shared<Kreuzung>("Kr1", TS1);
	std::shared_ptr<Kreuzung> Kr2 = std::make_shared<Kreuzung>("Kr2", TS2);
	std::shared_ptr<Kreuzung> Kr3 = std::make_shared<Kreuzung>("Kr3", TS3);
	std::shared_ptr<Kreuzung> Kr4 = std::make_shared<Kreuzung>("Kr4", TS4);

	//Erstellen von Straßen zum Test
	Weg W12("W12", 40, Tempolimit::Innerorts, true, Kr2);
	Weg W21("W21", 40, Tempolimit::Innerorts, true, Kr1);
	int iStr1Koordinaten[4] = {680, 40, 680, 300};
	Weg W23a("W23a", 115, Tempolimit::Autobahn, false, Kr3);
	Weg W32a("W32a", 115, Tempolimit::Autobahn, false, Kr2);
	int iStr2Koordinaten[12] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	Weg W23b("W23b", 40, Tempolimit::Innerorts, true, Kr3);
	Weg W32b("W32b", 40, Tempolimit::Innerorts, true, Kr2);
	int iStr3Koordinaten[4] = {680, 300, 680, 570};
	Weg W24("W24", 55, Tempolimit::Innerorts, true, Kr4);
	Weg W42("W42", 55, Tempolimit::Innerorts, true, Kr2);
	int iStr4Koordinaten[4] = { 680, 300, 320, 300};
	Weg W34("W34", 85, Tempolimit::Autobahn, false, Kr4);
	Weg W43("W43", 85, Tempolimit::Autobahn, false, Kr3);
	int iStr5Koordinaten[10] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	Weg W44a("W44a", 130, Tempolimit::Landstrasse, false, Kr4);
	Weg W44b("W44b", 130, Tempolimit::Landstrasse, false, Kr4);
	int iStr6Koordinaten[14] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};


	//Verbinden von Kreuzungen ueber die Straßen
	Kr1->vVerbinde("W12", "W21", 40, Kr1, Kr2, Tempolimit::Innerorts, true);
	Kr2->vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Tempolimit::Innerorts, true);
	Kr1->vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Tempolimit::Autobahn, false);
	Kr2->vVerbinde("W24", "W42", 55, Kr2, Kr4, Tempolimit::Innerorts, true);
	Kr1->vVerbinde("W34", "W43", 85, Kr3, Kr4, Tempolimit::Autobahn, false);
	Kr1->vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Tempolimit::Landstrasse, false);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	bZeichneStrasse(W12.getName(), W21.getName(), W12.getLaenge(), 2, iStr1Koordinaten);
	bZeichneStrasse(W23a.getName(), W32a.getName(), W23a.getLaenge(), 6, iStr2Koordinaten);
	bZeichneStrasse(W23b.getName(), W32b.getName(), W23b.getLaenge(), 2, iStr3Koordinaten);
	bZeichneStrasse(W24.getName(), W42.getName(), W42.getLaenge(), 2, iStr4Koordinaten);
	bZeichneStrasse(W34.getName(), W43.getName(), W34.getLaenge(), 5, iStr5Koordinaten);
	bZeichneStrasse(W44a.getName(), W44b.getName(), W44b.getLaenge(), 7, iStr6Koordinaten);

	// Fahrzeuge
	std::unique_ptr<PKW> meinAudi = std::make_unique<PKW>("Audi", 120, 30, 60);
	std::unique_ptr<PKW> typischerBMW = std::make_unique<PKW>("Volvo", 60, 30, 60);
	std::unique_ptr<PKW> Fiat500 = std::make_unique<PKW>("BMW", 30, 30, 60);
	std::unique_ptr<Fahrrad> JuliansWheels= std::make_unique<Fahrrad>("CityBike", 25);

	//-------------------------------------------------------------------------------
	//--------------------------Verhehrssystem-Simulation----------------------------
	//-------------------------------------------------------------------------------

	Kr1->vAnnahme(move(meinAudi), 0);
	Kr1->vAnnahme(move(typischerBMW), 0);
	Kr1->vAnnahme(move(Fiat500 ), 0);
	Kr1->vAnnahme(move(JuliansWheels), 0);

	double dTakt = 0.25; //Takt in 15 minuten

	for (; dGlobaleZeit < 20; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit);
		if (dGlobaleZeit == 3.50)
		{
			Kr1->vAnnahme(std::make_unique<PKW>("Honda", 60, 30, 60), 3.50);
		}

		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();

		//vSleep(2000);
	}
}
void vAufgabe_8()
{
		std::unique_ptr<PKW> meinAudi = std::make_unique<PKW>("");
		std::unique_ptr<Fahrrad> JuliansBike = std::make_unique<Fahrrad>("");
		std::shared_ptr<Kreuzung> testKreuzung = std::make_shared<Kreuzung>("");



		std::ifstream infile("VO.dat");
		infile.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit); // Fehlerbits

		try {
			infile >> *meinAudi >> *JuliansBike >> *testKreuzung;
		}
		catch (std::runtime_error e)
		{
			std::cout << e.what() << std::endl; // Ausgabe des Fehlers
			return;
		}



		//Ausgabe der Fahrzeuge
		meinAudi->vKopf();
		meinAudi->vAusgeben(std::cout);
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
		JuliansBike->vAusgeben(std::cout);
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;

		//Ausgabe der Kreuzung
		testKreuzung->vKopf();
		testKreuzung->vAusgeben(std::cout);
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;


}

void vAufgabe_9()
{
	// Einlesen der externen Datei
	std::ifstream infile("Simu.dat");
	Simulation simu;
	simu.vEinlesen(infile);

	double dDauer;
	std::cout << "Geben Sie bitte die Simulationsdauer [h] ein: " << std::endl;
	std::cin >> dDauer;
	double dTakt;
	std::cout << "Geben Sie bitte den Zeitschritt [h] ein: " << std::endl;
	std::cin >> dTakt;

	// Simulation ueber gewaehlte Zeit
	for (; dGlobaleZeit < dDauer; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit);
		simu.vSimulieren(dDauer, dTakt);
	}

}


void vAufgabe_9a()
{
	// Einlesen der externen Datei
	std::ifstream infile("SimuDisplay.dat");
	Simulation simu;
	simu.vEinlesen(infile, true);

	double dDauer;
	std::cout << "Geben Sie bitte die Simulationsdauer [h] ein: " << std::endl;
	std::cin >> dDauer;
	double dTakt;
	std::cout << "Geben Sie bitte den Zeritschritt [h] ein: " << std::endl;
	std::cin >> dTakt;

	// Simulation ueber gewaehlte Zeit
	for (; dGlobaleZeit < dDauer; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit);
		simu.vSimulieren(dDauer, dTakt);
	}
}

int main (){

	vAufgabe_9a();

}
