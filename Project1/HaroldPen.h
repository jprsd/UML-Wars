/**
 * \file HaroldPen.h
 *
 * \author David Hefty
 * \author Jaideep Prasad
 *
 * Class for the HaroldPen item
 */

#pragma once

#include <string>
#include "Item.h"
#include "Vector.h"
#include "ItemVisitor.h"

/// Pen object
class CHaroldPen :
	public CItem
{
public:
	/// Default constructor (disabled)
	CHaroldPen() = delete;

	/// Copy constructor (disabled)
	CHaroldPen(const CHaroldPen&) = delete;

	CHaroldPen(CVector position, CVector velocity, CGame* game);

	virtual void Draw(Gdiplus::Graphics* graphics, CVector position) override;
	virtual void Update(double elapsedTime) override;

	/// Set angle for player rotation
	/// \param angle The new angle
	void SetAngle(double angle) { mAngle = angle; }

	/// Unattach pen from Harold
	void UnAttach() { mIsAttached = false; mFiredAngle = mAngle; }
	
	/// Gets state of pen attached to Harold
	/// \returns true if attached
	bool GetAttachedState() { return mIsAttached; }

	void ResetPen();

	virtual void Accept(CItemVisitor* visitor) override;

	/// Resets pen velocity and position on origin
	virtual void Effect() override 
	{
		CItem::SetVelocity(CVector(0, 0)); 
		CItem::SetLocation(CVector(1000, -1000));
	}

	/// Getter for pen dimentions
	/// \returns pen position as a vector
	virtual CVector GetDimensions() const override
	{
		return CVector((double)mHaroldPenImage->GetWidth(),
			(double)mHaroldPenImage->GetHeight());
	}

private:
	/// Whether or not the pen is attached to Harold
	bool mIsAttached;
	/// Time pen has been traveling
	double mTravelTime;
	/// Image filename for the pen
	std::unique_ptr<Gdiplus::Bitmap> mHaroldPenImage;
	/// Angle of the pen
	double mAngle = 25.0f;
	/// Angle pen is fired at
	double mFiredAngle = 25.0f;
};