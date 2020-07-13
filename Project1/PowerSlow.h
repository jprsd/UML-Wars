/**
 * \file PowerSlow.h
 *
 * \author Isaac Mayers
 * \author Jaideep Prasad
 *
 * Slow power item class
 */
#pragma once

#include <string>
#include "PowerItem.h"

/// Slow power-up class
class CPowerSlow :
	public CPowerItem
{
public:
	CPowerSlow(CVector position, CVector velocity, CGame* game);

	virtual void Effect() override;

	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPowerSlow(this); }

	virtual void Update(double elapsedTime) override;
};

