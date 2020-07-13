/**
* \file IsPowerSlowVisitor.h
*
* \author Reid Shinabarker
*
* Slow power concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
//#include "PowerSlow.h"

/** Slow power concrete visitor */
class CIsPowerSlowVisitor :
	public CItemVisitor
{
public:

	virtual void VisitPowerSlow(CPowerSlow* slow) override;

	/** Tells the visitor that this is an Slow power item
	* \returns True if the item is an Slow power item */
	bool IsPowerSlow() { return mIsPowerSlow; }

	/** Tells the visitor if the power is active
	* \returns True if the power is active */
	bool IsActive() { return mIsActive; }

private:
	/// Bool for if this is a slow power item or not
	bool mIsPowerSlow = false;

	/// Bool for if the power is active or not
	bool mIsActive = false;
};