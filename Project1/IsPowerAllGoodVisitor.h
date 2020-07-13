/**
* \file IsPowerAllGoodVisitor.h
*
* \author Reid Shinabarker
*
* AllGood power concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
//#include "PowerAllGood.h"

/** AllGood power concrete visitor */
class CIsPowerAllGoodVisitor :
	public CItemVisitor
{
public:

	virtual void VisitPowerAllGood(CPowerAllGood* allgood) override;

	/** Tells the visitor that this is an AllGood power item
	* \returns True if the item is an AllGood power item */
	bool IsPowerAllGood() { return mIsPowerAllGood; }

private:
	/// Bool for if this is a pen item or not
	bool mIsPowerAllGood = false;
};