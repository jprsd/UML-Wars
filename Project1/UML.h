/**
 * \file UML.h
 *
 * \author team Sarson 
 *
 * Class for the actual UML object
 */

#pragma once
#include "pch.h"
#include <memory>
#include <vector>
#include "Item.h"
#include "UMLAttribute.h"
#include "Vector.h"

/// Base class for UML objects
class CUML :
	public CItem
{
private:
	/// number of attributes on the object
	int mNumberOfAttributes;

	/// pointer to the object for the name assigned to this uml item
	std::shared_ptr<CUMLAttribute> mName;
	
	/// vector of 0-3 attributes associated with this uml object
	std::vector<std::shared_ptr<CUMLAttribute> > mAttributes;

	/// vector of 0-3 operations associated with this uml object
	std::vector<std::shared_ptr<CUMLAttribute> > mOperations;

	/// width of the uml object
	double mWidth = -1;

	/// height of the uml object
	double mHeight = -1;

public:
	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitUML(this); }

	virtual void Update(double elapsedTime) override;

	virtual void Draw(Gdiplus::Graphics* graphics, CVector position) override;

	/// Getter for the dimensions of the UML object
	/// \returns the current dimensions
	virtual CVector GetDimensions() const override
	{
		return CVector(mWidth, mHeight);
	}

	/// Updates the object for things that effect it
	virtual void Effect() override 
	{ 
		CItem::SetVelocity(CVector(0, 0));
		mDisplayLocation = CItem::GetPosition();
	}

	/// Getter for mDeleted variable
	/// \returns mDeleted value
	bool IsDeleted() const { return mDeleted; }

protected:

	/// constructor
	/// \param name Name attribute
	/// \param attributes List of attributes for the object
	/// \param operations List of operations for the object
	/// \param position Starting position of the object
	/// \param velocity Starting velocity of the object
	/// \param game The game object
	CUML(std::shared_ptr<CUMLAttribute> name, std::vector<std::shared_ptr<CUMLAttribute> > attributes, 
		std::vector<std::shared_ptr<CUMLAttribute> > operations, CVector position, CVector velocity, CGame* game);

	/// bool for if the object has been hit by the pen
	bool mHit = false;
	/// bool for if the object is deleted
	bool mDeleted = false;
	/// time object has been on screen
	double mTimeDisplayed = 0;
	/// location of the object
	CVector mDisplayLocation;

};

