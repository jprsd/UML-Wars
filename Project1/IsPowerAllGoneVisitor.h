/**
* \file IsPowerAllGoneVisitor.h
*
* \author Reid Shinabarker
*
* AllGone power concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
//#include "PowerAllGone.h"

/** AllGone power concrete visitor */
class CIsPowerAllGoneVisitor :
	public CItemVisitor
{
public:

	virtual void VisitPowerAllGone(CPowerAllGone* allgone) override;

	/** Tells the visitor that this is an AllGone power item
	* \returns True if the item is an AllGone power item */
	bool IsPowerAllGone() { return mIsPowerAllGone; }

private:
	/// Bool for if this is a pen item or not
	bool mIsPowerAllGone = false;
};