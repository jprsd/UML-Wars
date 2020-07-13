/**
 * \file PowerRapidFire.h
 *
 * \author Jaideep Prasad
 *
 * Rapid fire power item class
 */

#pragma once

#include <string>
#include "PowerItem.h"

 /**
  * Rapid fire power item class
  */
class CPowerRapidFire : public CPowerItem
{
public:
	CPowerRapidFire(CVector position, CVector velocity, CGame* game);

	virtual void Effect() override;

	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPowerRapidFire(this); }

	virtual void Update(double elapsedTime) override;
};

