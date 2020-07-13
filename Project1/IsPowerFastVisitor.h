/**
* \file IsPowerFastVisitor.h
*
* \author Reid Shinabarker
*
* Fast power concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
//#include "PowerFast.h"

/** Fast power concrete visitor */
class CIsPowerFastVisitor :
	public CItemVisitor
{
public:

	virtual void VisitPowerFast(CPowerFast* fast) override;

	/** Tells the visitor that this is an Fast power item
	* \returns True if the item is an Fast power item */
	bool IsPowerFast() { return mIsPowerFast; }

	/** Tells the visitor if the power is active
	* \returns True if the power is active */
	bool IsActive() { return mIsActive; }

private:
	/// Bool for if this is a fast power item or not
	bool mIsPowerFast = false;

	/// Bool for if the power is active
	bool mIsActive = false;
};