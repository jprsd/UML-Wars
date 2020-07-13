/**
* \file IsPowerRapidFireVisitor.h
*
* \author Reid Shinabarker
*
* RapidFire power concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
//#include "PowerRapidFire.h"

/** RapidFire power concrete visitor */
class CIsPowerRapidFireVisitor :
	public CItemVisitor
{
public:

	virtual void VisitPowerRapidFire(CPowerRapidFire* rapidfire) override;

	/** Tells the visitor that this is an RapidFire power item
	* \returns True if the item is an RapidFire power item */
	bool IsPowerRapidFire() { return mIsPowerRapidFire; }

	/** Tells the visitor if the power is active
	* \returns True if the power is active */
	bool IsActive() { return mIsActive; }

private:
	/// Bool for if this is a rapid fire item or not
	bool mIsPowerRapidFire = false;

	/// Bool for if the power is active or not
	bool mIsActive = false;
};