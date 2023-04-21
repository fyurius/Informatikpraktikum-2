#include "Simulation.h"

// Einfacher Konstruktor
Simulation::Simulation()
{
}

// Einlesen aus einer externen Datei
void Simulation::vEinlesen(std::istream& e, bool bMitgrafik)
{
	//std::cout<<"Test einlesen in Simulation"<<std::endl;

	int iZeile = 0;		// Zeilenindex
	e.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit);

	if (bMitgrafik)
	{
		bInitialisiereGrafik(1500, 1500); //Ausgabefenster
	}

	try {

		std::string keyword = "";
		e >> keyword;

		while (!e.eof()) 		// Datei bis zum Ende lesen
		{
			iZeile++;
			if (keyword == "KREUZUNG")
			{
				//Einlesen
				std::string sName = "";
				e >> sName;
				double dTankstelle = 0;
				e >> dTankstelle;

				auto it1 = m.find(sName); // Zeigt aufs richtige Objekt
				if (it1 != m.end())
				{
					throw std::runtime_error("Kreuzung ist schon eingelesen worden!");	// Das objekt existiert also bereits
				}

				else {
					m[sName] = std::make_shared<Kreuzung>(sName, dTankstelle);	// Einfuegen in die Map
				}

				if (bMitgrafik)
				{
					//Einlesen der Koordinaten
					int iX, iY;
					e >> iX;
					e >> iY;
					bZeichneKreuzung(iX, iY);
				}
			}
			else if (keyword == "STRASSE")
			{
				std::string sKrzStart;
				e >> sKrzStart;
				auto it2 = m.find(sKrzStart);		// Analog zu oben, wiederholt sich immer
				if (it2 == m.end())
				{
					throw std::runtime_error("Die Startkreuzung existiert nicht!");
				}
				std::string sKrzZiel;
				e >> sKrzZiel;
				auto it3 = m.find(sKrzZiel);
				if (it3 == m.end())
				{
					throw std::runtime_error("Die Zielkreuzung existiert nicht!");
				}

				//Einlesen der Hin- und Rueckweg
				std::string sHinweg = "";
				e >> sHinweg;
				std::string sRueckweg = "";
				e >> sRueckweg;

				//Einlesen der Strassenlaenge
				int iLaenge = 0;
				e >> iLaenge;

				//Einlesen des Tempolimits
				int iTempolimit = 0;
				e >> iTempolimit;
				Tempolimit Limit = Tempolimit::Autobahn;		// Tempolimit kann man nicht einfach mit << einlesen
				switch (iTempolimit)
				{
				case 1:
					Limit = Tempolimit::Innerorts;
					break;
				case 2:
					Limit = Tempolimit::Landstrasse;
					break;
				case 3:
					Limit = Tempolimit::Autobahn;
					break;
				default:
					throw std::runtime_error("Undefiniertes Tempolimit!");
				}

				//Einlesen des Ueberholverbots
				int iVerbot = 1;
				e >> iVerbot;
				bool bVerbot = true;
				switch (iVerbot)
				{
				case 0:
					bVerbot = false;
					break;
				case 1:
					bVerbot = true;
					break;
				default:
					throw std::runtime_error("Undefinierte Eingabe zu Ueberholverbot!");
				}

				it2->second->vVerbinde(sHinweg, sRueckweg, (double) iLaenge, m[sKrzStart], m[sKrzZiel], Limit, bVerbot);
				if (bMitgrafik)
				{
					//Einlesen der Daten
					int iPaare;
					e >> iPaare;
					int iKoordinaten[20]; // Von mir gewaehlte Grenze
					for (int i = 0; i < iPaare * 2; i++)
					{
						e >> iKoordinaten[i];
					}
					bZeichneStrasse(sHinweg, sRueckweg, iLaenge, iPaare, iKoordinaten);
				}
			}

			else if (keyword == "PKW")
			{
			    //das Einlesen erfolgt analog zu oben.
				std::string sName = "";
				e >> sName;
				double dGeschwindigkeit = 0;
				e >> dGeschwindigkeit;
				double dVerbrauch = 0;
				e >> dVerbrauch;
				double dTankvolumen = 55;
				e >> dTankvolumen;
				std::string sStartKrz = "";
				e >> sStartKrz;
				double dStartzeit = 0;
				e >> dStartzeit;

				auto it4 = m.find(sStartKrz);
				if (it4 == m.end()) //wenn Kreuzung nicht gefunden
				{
					throw std::runtime_error("Die Startkreuzung existiert nicht!");
				}

				else {
					std::unique_ptr<PKW> car = std::make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen);	// Erzeugen und einfuegen
					m[sStartKrz]->vAnnahme(move(car), dStartzeit);
				}
			}

			else if (keyword == "FAHRRAD") {

			     //Einlesen wie oben

			     std::string sName = "";
			     e >> sName;
				 double dGeshwindigkeit = 0;
				 e >> dGeshwindigkeit;
				 std::string sStartKrz = "";
				 e >> sStartKrz;
				 double dStartzeit = 0;
				 e >> dStartzeit;
				 auto it5 = m.find(sStartKrz);		// Wie oben
				 if (it5 == m.end())
				 {
					 throw std::runtime_error("Die Startkreuzung existiert nicht!");
				 }
				 else {
					 std::unique_ptr<Fahrrad> bike = std::make_unique<Fahrrad>(sName, dGeshwindigkeit);		// Erstellen und Einfuegen
					 m[sStartKrz]->vAnnahme(move(bike), dStartzeit);
				 }
            }

			else {
				throw std::runtime_error("Undefiniertes Keyword!");
			}

			e >> keyword; // naechste Zeile
		}
	}

	catch(std::runtime_error error)
	{
		// Bearbeiten der einzelnen Bits
        if (e.bad())
		{
			std::cout << "Datei kann nicht geoeffnet werden." << std::endl;
			std::cout << "" << std::endl;
			return;
		}

		else if (e.fail())
		{
			std::cout << "Vorgangfehler (z.B Formatfehler)!" << std::endl;
			std::cout << "Fehler in Zeilennummer: " << iZeile << std::endl;
			std::cout << "" << std::endl;
			return;
		}

		else if (e.eof())
		{
			std::cout << "Datei ist leer oder Dateiende ist erreicht worden." << std::endl;
			std::cout << "" << std::endl;
			return;
		}

		std::cout << error.what() << std::endl; 	// Ausgabe des Fehlers
		std::cout << "Fehler in Zeilennummer: " << iZeile << std::endl;
		std::cout << "" << std::endl;
		return; // terminate bei Error
	}
}

// Simulation aller Elemente der map
void Simulation::vSimulieren(double dDauer, double dTakt)
{
	for (; dGlobaleZeit < dDauer; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit);
		for (auto it = m.begin(); it != m.end(); it++)
		{
			it->second->vSimulieren(); // Zweiter Element der Map (x,y) -> simuliere y
			//vSleep(500);
		}
	}
}
