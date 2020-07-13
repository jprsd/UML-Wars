/**
* \file IsPowerItemVisitor.h
*
* \author Isaac Mayers
*
* Power Item concrete visitor class.
*/


#pragma once
#include "ItemVisitor.h"
#include "PowerItem.h"

/** Power Item concrete visitor */
class CIsPowerItemVisitor :
	public CItemVisitor
{
public:
	
	virtual void VisitPowerItem(CPowerItem* poweritem) override;

	/// Tells the visitor that this is a poweritem
	/// \returns True if the item is a power */
	bool IsPowerItem() { return mIsPowerItem; }

private:
	/// Bool for if this is a poweritem or not
bool mIsPowerItem = false;
};

