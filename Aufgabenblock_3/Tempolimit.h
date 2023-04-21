/*
 * Tempolimit.h
 *
 *  Created on: 15.11.2022
 *      Author: finle
 */
#pragma once

#include <limits>
#include <string>

#define TEMPOLIMIT_H_

enum class Tempolimit {Innerorts = 50,Landstrasse = 100,Autobahn = std::numeric_limits<int>::max()};


