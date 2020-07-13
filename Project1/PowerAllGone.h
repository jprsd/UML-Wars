/**
 * \file PowerAllGone.h
 *
 * \author Jaideep Prasad
 *
 * All Gone (Nuke) power item class
 */

#pragma once

#include <string>
#include "PowerItem.h"

 /**
  * All Gone power item class
  */
class CPowerAllGone : public CPowerItem
{
public:
	CPowerAllGone(CVector position, CVector velocity, CGame* game);

	virtual void Effect() override;

	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPowerAllGone(this); }
};

