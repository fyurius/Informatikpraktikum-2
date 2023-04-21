#pragma once
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "vertagt_liste - Vorlage.h"

#include <list>

class Weg;

class Kreuzung :
    public Simulationsobjekt
{
public:

	//Konstruktor
    Kreuzung(std::string sName, double dTankstelle = 0);

    //  Ausfuehrende Methoden
    void vAnnahme(std::unique_ptr<Fahrzeug> vehicle, double dZeit);
    void vTanken(Fahrzeug& vehicle);
    void vVerbinde(std::string sHin, std::string sRueck, double dLaenge, std::shared_ptr<Kreuzung> kStart, std::shared_ptr<Kreuzung> kZiel, Tempolimit eLimit = Tempolimit::Autobahn, bool p_bUeberholverbot = true);
    void vSimulieren();

    // I/O Methoden
    void vKopf();
    void vAusgeben(std::ostream& o) const override;
    void vEinlesen(std::istream& i);

    // Getter
    double getTankstelle() const;
    std::string getName() const;
    Weg& pZufaelligerWeg(Weg& street);

    std::list<std::shared_ptr<Weg>> p_pWege; // public wegen Streckenende.cpp / Shared Pointer weil mehrere Wege auf eine Kreuzung zeigen duerfen

private:
    double p_dTankstelle;
    std::string sName;
};

