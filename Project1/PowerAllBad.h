/**
 * \file PowerAllBad.h
 *
 * \author Jaideep Prasad
 *
 * All Bad power item class
 */

#pragma once

#include <string>
#include "PowerItem.h"

/**
 * All Bad power item class that removes all good UMLs from the screen
 */
class CPowerAllBad : public CPowerItem
{
public:
	CPowerAllBad(CVector position, CVector velocity, CGame* game);

	virtual void Effect() override;

	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPowerAllBad(this); }
};

