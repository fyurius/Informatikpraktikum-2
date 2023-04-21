/*
 * Weg.h
 *
 *  Created on: 11.11.2022
 *      Author: finle
 */
#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste - Vorlage.h"

#include <list>

#define WEG_H_

class Fahrzeug;

class Weg : public Simulationsobjekt
{
	public:

		// Konstruktoren
		Weg();
		Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);

		// Getter
		double getTempolimit() const;
		double getLaenge() const;

		// Ausgabemethoden
		static void vKopf();
		virtual void vAusgeben(std::ostream& o) const ;

		// Ausfuehrende Methoden
		virtual void vSimulieren() override;
		void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug); // Fahrende Autos
		void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);

		// Nimmt Fahrzeuge vom Weg
		std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);


		// Copy-Konstruktor verbieten
		Weg(Weg&) = delete;

	protected:

		// Fuer Weg benoetigte Variablen
		const double p_dLaenge = 0; 		// in Km
		vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; 		// Aus vertagt_list Vorlage
		const Tempolimit p_eTempolimit;		// Aus Enum Class Tempolimit

};



