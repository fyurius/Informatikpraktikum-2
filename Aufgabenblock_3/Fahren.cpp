/*
 * Fahren.cpp
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"


double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitintervall)
{
	Weg& parWeg = this->getWeg(); //Kopie des Weges mit der gearbeitet werden kann

		double dStreckeMax = dZeitintervall * aFzg.dGeschwindigkeit(); //Berechnen der maximal fahrbaren Strecke dieses Aufrufes
		double dRestStrecke = parWeg.getSchranke() - aFzg.getAbschnittStrecke(); 	//Umsetzen des Ueberholverbotes erfolgt hier durch die Schranke

		if (dStreckeMax > dRestStrecke)
		{
			if (dRestStrecke > 0)		//Ist also nicht am Streckenende und es gibt noch fahrbare Strecke
			{
				return dRestStrecke;
			}

			std::cout << aFzg.getName() << " ist am Ende des Weges." << std::endl;
			throw Streckenende(aFzg, parWeg); // Hier nur noch Error Handling noetig
		}

		return dStreckeMax;	// Es kann die komplette Strecke gefahren werden
}
