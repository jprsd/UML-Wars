/**
 * \file Vector.h
 *
 * \author Charles Owen
 *
 * Simple 2D vector class
 */

#pragma once

/**
 * \brief Simple 2D vector class
 *
 * This class implements vector operations and operator overloading
 * to simplify the use of 2d vectors in a C++ program.
 */
class CVector
{
public:
	CVector(double x, double y);
	CVector();
	~CVector();

	CVector operator*(double d) const;

	CVector & operator+=(const CVector & a);

	CVector & operator*=(double d);

	CVector & operator/=(double d);

	/// Get the X value
	/// \returns X
	double X() const { return mX; }

	/// Get the Y value
	/// \returns Y
	double Y() const { return mY; }

	/// Set the vector
	/// \param x X value
	/// \param y Y value
	void Set(double x, double y) { mX = x; mY = y; }

	/// Set the vector from another vector
	/// \param x Other vector
	void Set(const CVector &x) { mX = x.mX; mY = x.mY; }

	/// Set the X component of the vector
	/// \param x X value
	void SetX(double x) { mX = x; }

	/// Set the Y component of the vector
	/// \param y Y value
	void SetY(double y) { mY = y; }

	double Length() const;

	double Distance(const CVector & other) const;

	CVector & Normalize();

private:
	/// X component of vector
	double mX;

	/// Y component of vector
	double mY;
};

CVector operator+(const CVector & a, const CVector & b);
CVector operator-(const CVector & a, const CVector & b);
CVector operator/(const CVector & a, double d);
