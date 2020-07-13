/**
 * \file Harold.h
 *
 * \author Isaac Mayers
 * \author Jaideep Prasad
 *
 * Class for the character, Harold
 */


#pragma once

class CGame;
 /**
  * Harold class
  */
class CHarold
{
public:
	CHarold();

	/// Copy constructor (disabled)
	CHarold(const CHarold&) = delete;

	virtual ~CHarold();
	/** The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/// Get Angle of Harold
	/// \returns angle
	double GetAngle() const { return mAngle; }

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(double x, double y) { mX = x; mY = y;}

	/// Set angle for player rotation
	/// \param angle The new angle
	void SetAngle(double angle) { mAngle = angle; }

	void Draw(Gdiplus::Graphics* graphics, double x, double y);
private:
	// Harold's location in the Game
	double  mX = 0;     ///< X location for the center of Harold
	double  mY = 0;     ///< Y location for the center of Harold
	double mAngle = 0;	///< Angle for Harold
	std::unique_ptr<Gdiplus::Bitmap> mHaroldImage; ///< Harold's image to use.
};

