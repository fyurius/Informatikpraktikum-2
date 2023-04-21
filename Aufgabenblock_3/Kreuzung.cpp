#include "Kreuzung.h"
#include "Weg.h"
#include <cmath>
#include <random>


Kreuzung::Kreuzung(std::string sName, double dTankstelle):
	Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{
}

// Verbinden von 2 Kreuzungen, shared Pointer hier wieder wichtig
void Kreuzung::vVerbinde(std::string sHin, std::string sRueck, double dLaenge, std::shared_ptr<Kreuzung> kStart, std::shared_ptr<Kreuzung> kZiel, Tempolimit eLimit, bool p_bUeberholverbot)
{
	//Erstellung des Hin- und Rueckwegs
	std::shared_ptr<Weg> Hinweg = std::make_shared<Weg>(sHin, dLaenge, eLimit, p_bUeberholverbot, kZiel);
	std::shared_ptr<Weg> Rueckweg = std::make_shared<Weg>(sRueck, dLaenge, eLimit, p_bUeberholverbot, kStart);

	//Die Wege sind als shared ptr deklarieret, denn von denen werden ihre
	//individuellen "Rueckwege" abgeleitet und bekannt gemacht.

	Hinweg->setRueckweg(Rueckweg); //Hinweg und Rueckweg sind ja immer auf einer Strecke
	Rueckweg->setRueckweg(Hinweg);
	kStart->p_pWege.push_back(move(Hinweg)); //Einfuegen der Wege in die jeweiligen Kreuzungen
	kZiel->p_pWege.push_back(move(Rueckweg));
}

// Auftanken der Fahrzeuge an den Kreuzungen
void Kreuzung::vTanken(Fahrzeug& vehicle)
{
	if (this->p_dTankstelle == 0)
	{
		return;
	}

	else if (this->p_dTankstelle < 0)
	{
		this->p_dTankstelle = 0.0;
	}

	else {
		double dTankbareMenge = vehicle.dTanken(); //PKW wird getankt, die getankte Menge wird eine Variable gespeichert..
		this->p_dTankstelle = this->p_dTankstelle - dTankbareMenge;  //und von der Tankstelle der Krezung abgezogen.
	}
}

// Simulation einer Kreuzung mit allen angeschlossenen Wege
void Kreuzung::vSimulieren()
{
	for (auto& wegSchablone : p_pWege)
	{
		wegSchablone->vSimulieren();
	}
}

// Wie der Name sagt
Weg& Kreuzung::pZufaelligerWeg(Weg& street)
{
	int index = this->p_pWege.size(); 			// Random erzeugen
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, index);
	int i = dist(device);

	auto it = this->p_pWege.begin();
	std::advance(it, i - 1); 		// Nun an der richtigen Stelle

	if (this->p_pWege.size() > 2) //  1 Straße -> 2 Wege
	{
		if (*it == street.getRueckweg())		// Sonst kein Wechsel
		{
			return this->pZufaelligerWeg(street);
		}

		return **it;
	}
}

// Parkende Annahme eines Fahrzeugs (weil Startzeit)
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> aFzg, double dStartZeit)
{
	this->vTanken(*aFzg); //PKW wird getankt.
	this->p_pWege.begin()->get()->vAnnahme(move(aFzg), dStartZeit);
}

void Kreuzung::vKopf()
{
	Fahrzeug::vKopf();
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(30) << "|   Tankstelle-Benzininhalt [L]" << std::setw(25) << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

}

// Ausgabemethode fuer die Kreuzung
void Kreuzung::vAusgeben(std::ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	o << std::resetiosflags(std::ios::right);
	o << p_dTankstelle << std::setw(25);
}

// Einlesemethode fuer die Kreuzung
void Kreuzung::vEinlesen(std::istream& i)
{
	Simulationsobjekt::vEinlesen(i);
	i >> this->p_dTankstelle;
}


// Getter fuer Benzinmenge
double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}

// Getter fuer Namen
std::string Kreuzung::getName() const
{
	return p_sName;
}



