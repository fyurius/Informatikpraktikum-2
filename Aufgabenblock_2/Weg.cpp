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

// Einfacher Konstruktor (Wenig benutzt)
Weg::Weg()
	: Simulationsobjekt::Simulationsobjekt(""), p_dLaenge(0), p_eTempolimit(Tempolimit::Autobahn)
{
}

// Konstruktor mit Parameter (Meistens benutzt)
Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit)
	: Simulationsobjekt::Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempolimit)
	  {
	  }

// Simulationsmethode fuer Wege
void Weg::vSimulieren(){

	p_pFahrzeuge.vAktualisieren();		// Damit die Liste auch stimmt

	for (auto& pFahrzeug : p_pFahrzeuge)		// Iterieren ueber alle Elemente
	    {

		//std:: cout << pFahrzeug->dGeschwindigkeit() << pFahrzeug->getName() << std::endl;		// Nur zum testen
		//std::cout << pFahrzeug->getName() << std::endl;

		try{
			pFahrzeug->vSimulieren();		// Simulieren der einzelnen Fahrzeuge
			pFahrzeug->vZeichnen(*this); // Zeichnen nach jeder Simulation
		}
		catch(Fahrausnahme& e)	// Beide werden gefangen, weil beide mit vBearbeiten wissen was sie tun muessen
		{
			e.vBearbeiten();	// Ausnahmen werden bearbeitet
		}

	    }

	p_pFahrzeuge.vAktualisieren();		// Damit die Liste auch stimmt

}

// Angepasste Ausgabemethode
void Weg::vAusgeben(std::ostream& o) const{
	Simulationsobjekt::vAusgeben(o);
	o << std::setw(15) << p_dLaenge <<std::setw(10) << "( ";
	for (auto& pFahrzeug : p_pFahrzeuge)
		    {
		        o  << "  " << pFahrzeug->getName()<< "  "  ;
		    }
	o << " )" << std::endl;
	for (auto& p : p_pFahrzeuge){
		std::cout << *p; // Ausgeben der einzelnen Fahrzeuge ueber Pointer, muss hier geschehen, da von ausserhalb nicht zugaenglich
		o << std::resetiosflags(std::ios::left);
		o << std::setiosflags(std::ios::left);
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
	std::cout << pFahrzeug->getName() << " wird fahrend auf " << p_sName << " gesetzt." << std::endl;
	pFahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(pFahrzeug));

}

// // Annahme fuer parkende Fahrzeuge (vorne)
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit)
{
	std::cout << pFahrzeug->getName() << " wird parkend auf " << p_sName << " gesetzt. Seine Wartezeit betraegt " << dStartzeit << " h" << std::endl;
	pFahrzeug->vNeueStrecke(*this, dStartzeit);
	p_pFahrzeuge.push_front(move(pFahrzeug));

}

// Wenn Fahrzeuge vom Weg genommen werden sollen
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg)
{

	auto it = p_pFahrzeuge.begin();
	while(it != p_pFahrzeuge.end()){
		if(**it == aFzg){
			auto pFahrzeug = move(*it);
			p_pFahrzeuge.erase(it);
			return move(pFahrzeug);
		}
		it++;
	}
	return nullptr;
}

