#pragma once

#include <map>

#include <iostream>
#include <fstream>
#include "Fahrrad.h"
#include "PKW.h"
#include "Kreuzung.h"
#include "SimuClient.h"



class Simulation
{
	public:
		// Konstruktor (War glaube ich nur zum testen)
		Simulation();

		// Ausfuehrende Methode
		void vSimulieren(double, double);

		// I/O Methode
		void vEinlesen(std::istream&, bool bMitgrafik = false);

		std::map<std::string, std::shared_ptr<Kreuzung>> m;
};

