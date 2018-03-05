#ifndef CONV_H
#define CONV_H

#include <cmath>
#include "vector3.h"

const long double MG_PER_GRAIN = 64.79891l;
const long double MG_PER_GRAM = 1000l;
const long double KG_PER_GRAM = 0.001l;

const long double GAS_CONSTANT_DRY_AIR = 287.058l; // J/(kg*K)
const long double MOLAR_MASS_DRY_AIR = 0.0289644l; // kg/mol
const long double MOLAR_MASS_WATER_VAPOR = 0.018016l; // kg/mol
const long double UNIV_GAS_CONSTANT = 8.31447l; // J/(K*mol)
const long double GAS_CONSTANT_WATER_VAPOR = 461.495l; // J/(kg*K)

const long double G = 9.80665l; // m/s^2
const vector3 GRAV_VEC(0.0l, 0.0l, -(G));

const long double PI = acos(-1.0l);

long double grainsToGrams(long double grains) {
	return (grains * MG_PER_GRAIN) / MG_PER_GRAM;
}

long double cToK(long double celcius) {
	return celcius + 273.15;
}

// get the pressure (Pa) at a given altitude H in meters from sea level
long double pressureAtAltitude(long double H) {
	return (101.325l * pow((1.0l - (0.0065l * H)/(288.15l)), (G * MOLAR_MASS_DRY_AIR)/(UNIV_GAS_CONSTANT * 0.0065l))) * 0.001l;
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

// get the coefficient of drag
// BC = ballistic coefficient
// M = mass
// A = area of circle
long double dragCoefficient(long double BC, long double M, long double A) {
	return M/(A*BC);
}

// get the force of drag
// p = density of air
// A = frontal area
// u = speed of bullet
// CD = coefficient of drag
long double dragForce(long double p, long double A, long double u, long double CD) {
	return 0.5l * p * A * u * u * CD;
}

// get the angle of elevation given a range of zero, a speed, and the altitude of the target and the shooter
// R = range in meters
// AS = altitude of the shooter in meters
// AT = altitude of the target in meters
// V = the speed of the bullet
long double elevationAngle(long double R, long double AS, long double AT, long double V) {
	if (R == 0.0l) return 0.0l;
	long double alt_t = AT-AS; // adjust so that the shooter is at 0,0
	long double alt_s = 0.0l;
	long double v_2 = pow(V, 2.0l); // do powers first for efficiency
	long double v_4 = pow(V, 4.0l);
	long double num_sqrt = sqrt(v_4 - G*(G*R + 2.0l*alt_t*v_2)); // do this only once
	long double r_plus = atan((v_2 + num_sqrt)/(G*R));
	long double r_minus = atan((v_2 - num_sqrt)/(G*R));
	// one of these angles is the right one, it may be positive or negative
	// first check if they're both NaN in which case there is no way for it to work because the projectile can't get there
	if (isnan(r_plus) && isnan(r_minus))
		return nanl("");
	else if (isnan(r_plus))
		return r_minus;
	else
		return r_plus;
}

// Displacement in X over a given interval (in meters)
// V_i = initial velocity of the bullet in the current time interval
// t = length of the time interval (seconds)
// B_c = ballistic coefficient (kg/m^2)
// p = air pressure (kg/m^3)
// V_b = bullet velocity (m/s)
// V_w = wind velocity in X direction (m/s)
// d = diameter of bullet (m)
// m = mass of bullet (kg)
long double D_x(long double V_i, long double t, long double B_c, long double p, long double V_b, long double V_w, long double d, long double m) {
	return (V_i * t) - (((1.0l/(4.0l*B_c)) * p * (pow(V_b, 2.0l) - ((abs(V_w)/V_w) * pow(V_w, 2.0l) * (B_c * PI * pow(d/2.0l, 2.0l) / m)))) * pow(t, 2.0l));
}
// get the final velocity in X direction after the time interval (used as the initial one in C_x)
long double V_fx(long double V_i, long double t, long double B_c, long double p, long double V_b, long double V_w, long double d, long double m) {
	return V_i - (((1.0l/(4.0l*B_c)) * p * (pow(V_b, 2.0l) - ((abs(V_w)/V_w) * pow(V_w, 2.0l) * (B_c * PI * pow(d/2.0l, 2.0l) / m)))) * t);
}

#endif
