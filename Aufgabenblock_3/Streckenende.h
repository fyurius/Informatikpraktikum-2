/*
 * Streckenende.h
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */
#pragma once

#include "Fahrausnahme.h"

#define STRECKENENDE_H_

class Streckenende: public Fahrausnahme
{
public:
	Streckenende() = delete;	// Standard ergibt wenig Sinn
	Streckenende(Fahrzeug& aFzg, Weg& wWeg);

	void vBearbeiten() override;	// Angepasst
};

