/**
* \file IsPowerAllBadVisitor.h
*
* \author Reid Shinabarker
*
* AllBad power concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
//#include "PowerAllBad.h"

/** AllBad power concrete visitor */
class CIsPowerAllBadVisitor :
	public CItemVisitor
{
public:

	virtual void VisitPowerAllBad(CPowerAllBad* allbad) override;

	/** Tells the visitor that this is an AllBad power item
	* \returns True if the item is an AllBad power item */
	bool IsPowerAllBad() { return mIsPowerAllBad; }

private:
	/// Bool for if this is a pen item or not
	bool mIsPowerAllBad = false;
};