/**
 * \file PowerAllGood.h
 *
 * \author Jaideep Prasad
 *
 * All Good power item class
 */

#pragma once

#include <string>
#include "PowerItem.h"

 /**
  * All Good power item class
  */
class CPowerAllGood : public CPowerItem
{
public:
	CPowerAllGood(CVector position, CVector velocity, CGame* game);

	virtual void Effect() override;

	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPowerAllGood(this); }
};

