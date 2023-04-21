/*
 * Weg.cpp
 *
 *  Created on: 11.11.2022
 *      Author: finle
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Parken.h"
#include "Fahren.h"
#include "Fahrausnahme.h"
#include "Streckenende.h"
#include "Losfahren.h"
#include "Kreuzung.h"

// Einfacher Konstruktor (Wenig benutzt)
Weg::Weg()
	: Simulationsobjekt::Simulationsobjekt(""), p_dLaenge(0), p_eTempolimit(Tempolimit::Autobahn), p_bUeberholverbot(true)
{
}

// Konstruktor mit Parameter (Meistens benutzt)
Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot, std::shared_ptr<Kreuzung> pKreuzung)
	: Simulationsobjekt::Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempolimit), p_bUeberholverbot(bUeberholverbot), p_pKreuzung(pKreuzung)
	  {
	  }

// Simulationsmethode fuer Wege
void Weg::vSimulieren(){

	p_pFahrzeuge.vAktualisieren();

	setSchranke(this->getLaenge());

		for (auto &schablone :  p_pFahrzeuge)		// Iteration ueber alle Elemente
		{
			try
			{
				schablone->vSimulieren(); //simulieren aller Fahrzeuge.

				if (p_bUeberholverbot == true)		// Check Ueberholverbot
				{
					if (schablone->bUeberholenGueltig() == false)		// Check Tank
					{
						if (schablone->getAbschnittStrecke() > 0)	 // Check fahrend vs parkend
						{
							setSchranke(schablone->getAbschnittStrecke());		// Ueberholverbot
						}
					}
				}

				schablone->vZeichnen(*this);
			}
			catch (Fahrausnahme& x)
			{
				x.vBearbeiten();  				// Error Handling bei geworfener Ausnahme
			}
		}

		p_pFahrzeuge.vAktualisieren();

}



// Angepasste Ausgabemethode
void Weg::vAusgeben(std::ostream& o) const{
	Simulationsobjekt::vAusgeben(o);
	o << std::setw(20) << p_dLaenge << "( ";
	for (auto& pFahrzeug : p_pFahrzeuge)
		    {
		        o << std::setw(20) << pFahrzeug->getName() << ", ";
		    }
	o << " )" << std::endl;
	for (auto& p : p_pFahrzeuge){
		std::cout << *p; // Ausgeben der einzelnen Fahrzeuge ueber Pointer, muss hier geschehen, da von ausserhalb nicht zugaenglich
	}
}

// Getter fuer Tempolimit
double Weg::getTempolimit() const
{
	return (double) p_eTempolimit;
}

// Getter fuer Weglaenge
double Weg::getLaenge() const
{
	return p_dLaenge;
}
bool Weg::getUeberholverbot()
{
	return p_bUeberholverbot;
}

// Getter fuer Schranke mit Checks
double Weg::getSchranke()
{
		if (p_bUeberholverbot == true)
		{
			return dSchranke;
		}

		return p_dLaenge; // Kein Ueberholverbot
}

// Setter fuer Schranke
void Weg::setSchranke(double dNewSchranke)
{
    dSchranke = dNewSchranke;
}

// Setter fuer Schranke
void Weg::setRueckweg(std::shared_ptr<Weg> rueckweg)
{
	p_pRueckweg = rueckweg;
}

// Getter fuer Kreuzungen
std::weak_ptr<Kreuzung> Weg::getKreuzung() const
{
	return p_pKreuzung.lock();
}

// Getter fuer den Reuckweg
std::shared_ptr<Weg> Weg::getRueckweg() const
{
	return this->p_pRueckweg.lock();
}



// Beschriftet Tabelle korrekt
void Weg::vKopf()
{
    std::string h1 = "ID " , h2 = "| Name" , h3 = "| Laenge" , h4 = "| Fahrzeuge";
    std::string seperator = "--------------------------------------------------------\n";
    std::cout     << "\n"
                << std::left << std::setw(3) << h1
                << std::setw(13) << h2
                << std::setw(14) << h3
                << std::setw(12) << h4 << "\n"
                << seperator;
}

// Annahme fuer fahrende Fahrzeuge (hinten)
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug)
{
	//std::cout << pFahrzeug->getName() << " wird fahrend auf " << p_sName << " gesetzt." << std::endl;
	pFahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(pFahrzeug));

}

// // Annahme fuer parkende Fahrzeuge (vorne)
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit)
{
	//std::cout << pFahrzeug->getName() << " wird parkend auf " << p_sName << " gesetzt. Seine Wartezeit betraegt " << dStartzeit << " h" << std::endl;
	pFahrzeug->vNeueStrecke(*this, dStartzeit);
	p_pFahrzeuge.push_front(move(pFahrzeug));

}

// Wenn Fahrzeuge vom Weg genommen werden sollen
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg)
{

	std::unique_ptr<Fahrzeug> dummy;
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
		{
			if ((*it).get() == &aFzg) // Get() wegen nllptr
			{
				p_pFahrzeuge.erase(it);
				dummy = move(*it);
				return dummy;
			}
		}
}

