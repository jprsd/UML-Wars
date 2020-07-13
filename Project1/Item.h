/**
 * \file Item.h
 *
 * \author David Hefty
 *
 * Basic parent Item class
 */

#pragma once

#include <string>
#include <memory>
#include "Vector.h"
#include "ItemVisitor.h"

class CGame;

 /**
  * \brief Basic parent Item class
  *
  * This class implements the base for all other item classes. Provides
  * position, location, and ways to set them
  */
class CItem
{
public:
	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem&) = delete;

	CItem(CVector position, CVector velocity, CGame* game);

	/// Basic Destructor
	virtual ~CItem() {};

	virtual void SetLocation(CVector position);
	virtual void SetVelocity(CVector velocity);

	/** The location of the item
	* \returns position Item's position as a vector in pixels */
	CVector GetPosition() const { return mPosition; }
	
	/** The velocity of the item
	* \returns velocity Item's velocity as a vector in pixels */
	CVector GetVelocity() const { return mVelocity; }

	/// Virtual getter for dimensions of item
	/// \returns CVector of position
	virtual CVector GetDimensions() const = 0;

	virtual void Effect() = 0; ///< Item effect when hit with pen

	/** 
	 * \brief Meant to display the graphic for the object using gdiplus
	 * \param graphics Gdiplus object for drawing
	 * \param position Position to draw
	 *
	 * Pure Virtual Draw since it can't be drawn as a basic Item
	 */
	virtual void Draw(Gdiplus::Graphics* graphics, CVector position) = 0;

	virtual void Update(double elapsedTime);

	/// Virtual function for accepting a visitor
	/// \param visitor Visitor to accept
	virtual void Accept(CItemVisitor* visitor) = 0;

	/// Sets the angle of the item
	/// \param angle Angle to be used
	virtual void SetAngle(double angle) {}
	
	/// Sets the item velocity multiplier
	/// \param multiplier The new multiplier (default value is 1)
	void SetVelocityMultiplier(double multiplier = 1) { mVelocityMultiplier = multiplier; }

	/// Getter for the velocity multiplier
	/// \returns the multiplier
	double GetVelocityMultiplier() const { return mVelocityMultiplier; }

	/// Getter for the attached game object
	/// \returns the game object
	CGame* GetGame() { return mGame; }

private:
	/// The game the item exists in
	CGame* mGame;

	/// Current position of the item on the screen
	CVector mPosition;
	/// Current velocity of the item in pixels/sec
	CVector mVelocity;
	/// Velocity multiplier for the item. Default is 1.
	double mVelocityMultiplier = 1;
	

};

