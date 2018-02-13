#ifndef CONV_H
#define CONV_H

#include <cmath>

const long double MG_PER_GRAIN = 64.79891l;
const long double MG_PER_GRAM = 1000l;
const long double KG_PER_GRAM = 0.001l;

const long double GAS_CONSTANT_DRY_AIR = 287.058l; // J/(kg*K)
const long double MOLAR_MASS_DRY_AIR = 0.0289644l; // kg/mol
const long double MOLAR_MASS_WATER_VAPOR = 0.018016l; // kg/mol
const long double UNIV_GAS_CONSTANT = 8.31447l; // J/(K*mol)
const long double GAS_CONSTANT_WATER_VAPOR = 461.495l; // J/(kg*K)

const long double GRAVITY = 9.80665l; // m/s^2

long double grainsToGrams(long double grains) {
	return (grains * MG_PER_GRAIN) / MG_PER_GRAM;
}

long double cToK(long double celcius) {
	return celcius + 273.15;
}

// get the pressure (Pa) at a given altitude H in meters from sea level
long double pressureAtAltitude(long double H) {
	return (101.325l * pow((1.0l - (0.0065l * H)/(288.15l)), (GRAVITY * MOLAR_MASS_DRY_AIR)/(UNIV_GAS_CONSTANT * 0.0065l))) * 0.001l;
}

// gets the density of the air in kg/m^3 for a given relative humidity
// RH = relative humidity (100% = 1.0, 0% = 0.0)
// T = air temperature in degrees C
// P = observed absolute pressure (i.e. pressure from altimeter) in Pa (NOT kPa)
long double airDensity(long double RH, long double T, long double P) {
	long double T_K = cToK(T);
	// saturation vapor pressure (comes out in hPa, so divide by 100 at the end to get Pa)
	long double P_sat = (6.1078l * pow(10, (17.27l * T_K)/(T_K + 237.3)))/100;
	// vapor pressure of water in Pa
	long double P_v = RH * P_sat;
	// partial pressure of dry air
	long double P_d = P - P_v;
	long double density = ((P_d * MOLAR_MASS_DRY_AIR) + (P_v * MOLAR_MASS_WATER_VAPOR))/(UNIV_GAS_CONSTANT * T_K);
	return density;
}

#endif
