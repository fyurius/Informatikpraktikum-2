/*
 * Losfahren.h
 *
 *  Created on: 20.11.2022
 *      Author: finle
 */
#pragma once

#include "Fahrausnahme.h"

#define LOSFAHREN_H_

class Losfahren: public Fahrausnahme
{
public:
	Losfahren() = delete;	// Standard ergibt wenig Sinn
	Losfahren(Fahrzeug& aFzg, Weg& wWeg);

	virtual void vBearbeiten() override;	// Zweckmaessig angepasst
};


