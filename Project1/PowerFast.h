/**
 * \file PowerFast.h
 *
 * \author Isaac Mayers
 * \author Jaideep Prasad
 *
 * Fast power item class
 */
#pragma once

#include <string>
#include "PowerItem.h"


/// Fast power-up class
class CPowerFast :
	public CPowerItem
{
public:
	CPowerFast(CVector position, CVector velocity, CGame* game);

	virtual void Effect() override;

	/// Accepts a visitor
	/// \param visitor The visitor that is accessing this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPowerFast(this); }

	virtual void Update(double elapsedTime) override;
};

