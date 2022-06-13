/*
rigpp_types.h
This is ONLY headers of rigpp_math.hpp. Keep it in sync or you'll get crashes and types mismatch.

*/
#pragma	once

#include <memory>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Vector
{
public:
	double x;
	double y;
	double z;

	Vector() : x(0), y(0), z(0) {}
	Vector(double x, double y, double z) : x(x), y(y), z(z) {}
};

class Matrix
{
public:
	double x[4][4];
	Matrix()
	{
		memset(x, 0, sizeof(double) * 16);
		x[0][0] = 1;
		x[1][1] = 1;
		x[2][2] = 1;
		x[3][3] = 1;
	}	
};

class Quat
{
public:
	Vector v;
	double w;

	Quat() : w(1) { };
	Quat(double x, double y, double z, double w) : v(x, y, z), w(w) {}
	Quat(const Vector& v, double w) : v(v), w(w) {}

};

class NurbsCurve
{
public:
	vector<Vector> cvs;
	vector<float> knots;
	unsigned int degree;
};
