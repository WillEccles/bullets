#ifndef VECTOR3_H
#define VECTOR3_H

class vector3 {
	private:
		// x, y, z (z being "up")
		long double components[3] = {0.0l, 0.0l, 0.0l};
	public:
		vector3(long double x, long double y, long double z) {
			components[0] = x;
			components[1] = y;
			components[2] = z;
		};
		vector3() {};
		
		/* Getters/Setters */
		void setX(long double x) { components[0] = x; };
		void setY(long double y) { components[1] = y; };
		void setZ(long double z) { components[2] = z; };
		const long double getX() const { return components[0]; };
		const long double getY() const { return components[1]; };
		const long double getZ() const { return components[2]; };

		/* Vector Operators */
		vector3& operator= (const vector3& rhs) {
			if (this == &rhs) return *this; // check to make sure it's not beign self-assigned
			components[0] = rhs.getX();
			components[1] = rhs.getY();
			components[2] = rhs.getZ();
			return *this;
		};
		vector3& operator+=(const vector3& rhs) {
			components[0] += rhs.getX();
			components[1] += rhs.getY();
			components[2] += rhs.getZ();
			return *this;
		};
		vector3& operator-=(const vector3& rhs) {
			components[0] -= rhs.getX();
			components[1] -= rhs.getY();
			components[2] -= rhs.getZ();
			return *this;
		};
		const vector3 operator+ (const vector3& rhs) const {
			vector3 result = *this; // copy this
			result += rhs;
			return result;
		};
		const vector3 operator- (const vector3& rhs) const {
			vector3 result = *this; // copy self
			result -= rhs;
			return result;
		};
};

#endif
