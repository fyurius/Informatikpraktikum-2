/*
 * Streckenende.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Streckenende.h"
#include "PKW.h"
#include "Kreuzung.h"


// Konstruktor
Streckenende::Streckenende(Fahrzeug& aFzg, Weg& wWeg)
	: Fahrausnahme(aFzg, wWeg)
{
}

// Angepasst
void Streckenende::vBearbeiten()
{
	for (auto it = p_aWeg.p_pFahrzeuge.begin(); it != p_aWeg.p_pFahrzeuge.end(); it++)		// Einmal ueber alles
	{
		//std::cout<<" Test vor Streckenende"<<std::endl;

		if ((*it).get() == &p_aFahrzeug && *it != nullptr) //Zeiger auf Zeiger / get() wegen nllptr
		{
			//std::cout<<" Test vor Streckenende Bedingung ist erfüllt"<<std::endl;

			if (p_aWeg.getKreuzung().lock()->getTankstelle() != 0)
			{
				p_aWeg.getKreuzung().lock()->vTanken(**it); //Tanken des Fahrzeuges.
			}

			p_aWeg.p_pFahrzeuge.erase(it);

			if (p_aWeg.getKreuzung().lock()->p_pWege.size() > 2) // 1 Straße => 2 Wege
			{
				//std::cout<<" Test Ausgabe"<<std::endl;

				Weg& streetEin = p_aWeg.getKreuzung().lock()->pZufaelligerWeg(p_aWeg); //neuer Weg

				std::cout << std::resetiosflags(std::ios::left);
				std::cout << std::setw(10) << "ZEIT: " << std::setw(15) << dGlobaleZeit << std::endl;
				std::cout << std::setw(10) << "KREUZUNG: " << std::setw(15) << p_aWeg.getKreuzung().lock()->getName() << "   " << p_aWeg.getKreuzung().lock()->getTankstelle() << std::endl;
				std::cout << std::setw(10) << "WECHSEL: " << std::setw(15) << p_aWeg.getName() << " ---> " << streetEin.getName() << std::endl;
				std::cout << std::setw(10) << "FAHRZEUG: " << std::setw(15) << it->get()->getName() << std::setw(15) << it->get()->dGeschwindigkeit() << " km/h" << std::endl;

				streetEin.vAnnahme(move(*it)); // Wird hier fahrend auf den Weg gesetzt
			}

			else {
				std::cout << std::resetiosflags(std::ios::left);
				std::cout << std::setw(10) << "ZEIT: " << std::setw(15) << dGlobaleZeit << std::endl;
				std::cout << std::setw(10) << "KREUZUNG: " << std::setw(15) << p_aWeg.getKreuzung().lock()->getName() << "   " << p_aWeg.getKreuzung().lock()->getTankstelle() << std::endl;
				std::cout << std::setw(10) << "WECHSEL: " << std::setw(15) << p_aWeg.getName() << " ---> " << p_aWeg.getRueckweg()->getName() << std::endl;
				std::cout << std::setw(10) << "FAHRZEUG: " << std::setw(15) << it->get()->getName() << std::setw(15) << it->get()->dGeschwindigkeit() << " km/h" << std::endl;

				p_aWeg.getRueckweg()->vAnnahme(move(*it)); // Rueckweg bei Sackgasse
			}


		}
	}
}
