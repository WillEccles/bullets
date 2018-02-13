#include "vector3.h"
#include "conversions.h"
#include <iostream>
#include <fstream>
#include <chrono>

/**
 * Notes:
 * - positive X is away from the shooter, 0 is at the muzzle
 * - positive Y is going from right to left of the shooter
 * - positive Z is straight up
 * - use all metric units if possible
 * - all scope adjustments are relative, meaning that the scope is zeroed before adjustments are made
 * - 0.1 mil adjustment means about 1cm at 100m, so if zeroed at 100m, an adjustment of +0.5mil accounts for a 5cm drop at a given range >100m
 */

using namespace std::chrono; // for clocking every second (this is not necessary, since you can do all the math at once, but that's okay)
typedef vector3 force; // so that we can refer to them as forces, rather than vectors

struct settings {
	long double distance = 100.0l; // this is set in meters, straight along the X axis
	long double angle = 0.0l; // angle of elevation, set in mrads (1 radian = 180/pi, 1 mrad = 1/1000 of a radian)
	long double scope_mount_angle = 0.0l; // measured in mils, likely 0
	long double zero_distance = 100.0l; // measured in meters
	long double wind_correction = 0.0l; // measured in mils
	long double drop_correction = 0.0l; // measured in mils
	long double altitude_shooter = 0.0l; // altitude of the shooter in meters (0 being sea level)
	long double altitude_target = 0.0l; // altitude of the center of the target, also meters from sea level
	long double target_height = 0.61l; // height of the target in meters (assumed rectangular target)
	long double target_width = 0.4l; // width of target in meters (size of target is used to determine if the shot hit
	long double bullet_mass = grainsToGrams(200.0l) * KG_PER_GRAM; // mass of the bullet, measured in kilograms (this can be converted with grainsToGrams() for this purpose)
	long double vel_bullet = 1005.0l; // muzzle velocity of the bullet in m/s
	long double humidity = 0.25l; // relative humidity of the air (0.0 to 1.0)
	long double temperature = 30.0l; // temperature of the air (degrees C)
	long double coef_ballistic = 1.0l; // 1.0 is essentially a perfect coefficient, so drag makes no difference
	long double wind_y = 0.0l; // wind on the Y axis
	long double wind_x = 0.0l; // wind on the X axis
	long double wind_z = 0.0l; // wind on the Z axis
} sim_settings;

void simulate() {
	// this is where we do the stuff
	// just print the state of the bullet at every whole second after leaving the muzzle (and if there's a fractional number of seconds at the end, list that too
	long double dist_target = sim_settings.distance;
	int second = 1;
	while (dist_target >= 0.0l) {
		
	}
}

int main(void) {
	/* TODO:
	 * 1. read input somehow, not sure yet
	 * 2. setup simulation
	 * 3. run simulation
	 * 4. spit out results
	 */
	simulate();
};
