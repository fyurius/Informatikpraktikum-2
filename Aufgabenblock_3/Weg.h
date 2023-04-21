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
class Verhalten;
class Kreuzung;


class Weg : public Simulationsobjekt
{
	public:

		// Konstruktoren
		Weg();
		Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true, std::shared_ptr<Kreuzung> pKreuzung = nullptr);

		// Getter / Setter
		double getTempolimit() const;
		double getLaenge() const;
		bool getUeberholverbot();
		double getSchranke();
		void setSchranke(double);
		std::weak_ptr<Kreuzung> getKreuzung() const;
		void setRueckweg(std::shared_ptr<Weg> rueckweg);
		std::shared_ptr<Weg> getRueckweg() const;

		// I/O Methoden
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


		vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; 		// Aus vertagt_list Vorlage

	private:

		// Fuer Weg benoetigte Variablen
		const double p_dLaenge = 0; 		// in Km
		const Tempolimit p_eTempolimit;		// Aus Enum Class Tempolimit
		const bool p_bUeberholverbot;
		double dSchranke=0;
		const std::weak_ptr<Kreuzung> p_pKreuzung;
		std::weak_ptr<Weg> p_pRueckweg; 		// Hiervon wird nichts abgeleitet -> weak pointer / wird nacher geaendert

};



