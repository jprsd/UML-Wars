/**
 * \file PowerItem.h
 *
 * \author Isaac Mayers
 * \author Jaideep Prasad
 *
 * Class for the powerup, PowerItem
 */


#pragma once
#include <string>
#include <memory>
#include "Item.h"
#include "ItemVisitor.h"
#include "Vector.h"

/// Describes PowerItem class
class CPowerItem :
	public CItem
{
public:
	/// Default constructor (disabled)
	CPowerItem() = delete;

	/// Copy constructor (disabled)
	CPowerItem(const CItem&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics, CVector position) override;
	virtual void Update(double elapsedTime) override;

	/// Basic Destructor
	~CPowerItem() {};

	/// Accept Visitor
	/// \param visitor Visitor that is being accepted
	virtual void Accept(CItemVisitor* visitor) {}

	/// Getter for dimensions of the item
	/// \returns a vector of the poweritem dimensions
	virtual CVector GetDimensions() const override 
	{ 
		return CVector((double)mPowerItemImage->GetWidth(),
			(double)mPowerItemImage->GetHeight());
	}

	/// Removes the poweritem from the screen
	virtual void Effect() override 
	{ 
		CItem::SetLocation(CVector(-100, -1000));
		CItem::SetVelocity(CVector(0, 0));
	}

	/// Getter for if the power item is active
	/// \returns true if active
	bool IsActive() const { return mIsActive; }

protected:
	CPowerItem(CVector position, CVector velocity, CGame* game,
		std::wstring PowerItemImageName);
	/// Tracks if the poweritem is active
	bool mIsActive = false;
	/// Time the poweritem has been active
	double mTimeActive = 0;

private:
	/// Pointer to power item image
	std::unique_ptr<Gdiplus::Bitmap> mPowerItemImage;
};

